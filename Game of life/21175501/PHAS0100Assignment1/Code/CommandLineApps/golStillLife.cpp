#include <golMyFunctions.h>
#include <golExceptionMacro.h>
#include "golDataStructure.h"
#include "golSimulator.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <utility>
#include <memory>
#include <filesystem>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void show_usage(std::string name)
{
    /*=============================================================================

    Usage function that is called when --help, -h or nothing is called.
    This function is also called when some wrong inputs are used.
    Shows how to use command line app to user.

    =============================================================================*/
    std::cerr << "Usage Guide for: " << name << "\n" 
              << "This app has two input options\n"
              << "1: " << name << " int Rows int Columns int No._Alive_Cells int No._Generation_steps int No._Inital_test_conditions \n"
              << "2: " << name << " std::string Input_path_file  int No._Generation_steps \n"
              << std::endl;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    /*=============================================================================

    loop that calls the show_usage() function if -h or --help is an input

    =============================================================================*/
    for(int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if((arg == "-h") || (arg == "--help"))
        {
            show_usage(argv[0]);
            return 0;
        }
    }
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    /*=============================================================================

    if loop for 5 input case, where the user can specify the grid size, number 
    of alive cells and the number of initial cases to test.
    It then identifies if a still life has been found and prints it to the console 
    alonge with the initial state it was found in and the iteration it was found in. 

    =============================================================================*/
    if(argc == 6)
    {
        for(int i = 1; i < argc; ++i)
        {
            if(atoi(argv[i]) == 0)
            {
                throw std::invalid_argument("Invalid inputs make sure all input are integers");
            }
        }
        int i, j;
        std::vector<int> vec;
        for(i=1; i < argc; i++)
        {
            int x = std::stoi(argv[i], NULL, 10);
            vec.push_back(x);
        }
        int iter, seed;
        for(seed=0; seed<vec[4]; seed++)
        {
            Simulator obj1(vec[0],vec[1],vec[2]);
            for(iter=0; iter<vec[3]; iter++)
            {
                obj1.TakeStep();
                if(obj1.getGrid_() == obj1.getGridPlusOne() && obj1.isEmpty() == false)
                {
                    std::cout << "Inital state " << seed + 1 << " : " << "\n" << "Still life found on step " << iter+1 << std::endl;
                    obj1.PrintGrid();
                    break;
                }    
            }
        }
    }
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    /*=============================================================================

    if loop that allows the user to call a path to a file which is the read and
    evolved a specified number of steps, until a still life is found.

    =============================================================================*/
    if(argc == 3)
    {
        if(atoi(argv[2]) == 0)
        {
            throw std::invalid_argument("Invalid input make sure second input is an int");
        }
        int i;
        int x = std::stoi(argv[2], NULL, 10);
        int iter;
        std::string Path = argv[1];
        if(std::filesystem::exists(Path) == 0)
        {
            throw std::invalid_argument("File path does not exist");
        } 
        Simulator myObj(Path);
        for(iter=0; iter<x; iter++)
        {
            myObj.TakeStep();
            if(myObj.getGrid_() == myObj.getGridPlusOne())
            {
                std::cout << "Step " << iter+1 << std::endl;
                myObj.PrintGrid();
                break;
            }
        }
    }
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    /*=============================================================================

    if loop that runs when the wrong number of inputs are used and shows 
    usage function.

    =============================================================================*/
    if(argc != 6 && argc != 3)
    {
        std::cout << "Wrong number of inputs provided" << std::endl;
        show_usage(argv[0]);
        return 0;
    }
    return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------