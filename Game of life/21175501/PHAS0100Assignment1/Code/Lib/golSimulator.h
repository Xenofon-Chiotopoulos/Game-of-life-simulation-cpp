#ifndef GOLSIMULATOR_H
#define GOLSIMULATOR_H
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <random>
#include <fstream>

class Simulator {
    /*=============================================================================

    The simulator class uses the DataStucture class to store a DataStructure 
    class and uses the TakeStep function to evolve the object following the 
    rules of Conway's game of life.

    =============================================================================*/
    public:
        Simulator();
        Simulator(int& row, int& col);
        Simulator(int& row, int& col, int& AliveCells);
        Simulator(std::string& Path);
        ~Simulator();
        void TakeStep();
        void PrintGrid();
        void setObj(DataStructure obj);
        bool isEmpty();
        char GetCell(int& GetCol, int& GetRow);
        void SetCell(int& SetCol, int& SetRow, const bool& status);
        DataStructure getObj();
        std::vector<std::vector<char>>  getGrid_();
        std::vector<std::vector<char>>  getGridPlusOne();
    private:    
        std::vector<std::vector<char>> gridPlusOne;
        DataStructure myObj;
};
#endif