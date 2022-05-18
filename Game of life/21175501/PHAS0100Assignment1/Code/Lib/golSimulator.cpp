#include <iostream>
#include <vector>
#include <tuple>
#include "golDataStructure.h"
#include "golSimulator.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Simulator::Simulator()
{   
    /*=============================================================================

    Defult constructor that sets private member functions to 0 size

    =============================================================================*/
    int defult = 0;
    DataStructure obj(defult,defult);
    std::vector<std::vector<char>> vec = obj.getGrid();
    gridPlusOne = vec;
    myObj = obj;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Simulator::Simulator(int& row, int& col)
{   
    /*=============================================================================

    Constructor that creates a grid with row number of rows and col number 
    of columns, this constructor instantiates an object with an empty grid.
    This is done by calling the respective DataStructure constructor.

    =============================================================================*/
    DataStructure obj(row,col);
    std::vector<std::vector<char>> vec = obj.getGrid();
    gridPlusOne = vec;
    myObj = obj;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Simulator::Simulator(int& row, int& col, int& AliveCells)
{   
    /*=============================================================================

    Constructor that creates a grid with row number of rows and col number 
    of columns, this constructor instantiates an object with AliveCells number 
    of cells that are alive. The alive cells are set at a random position in 
    the grid. The random number gernerator uses the hardware to obtain 
    each random number. This is done by calling the respective DataStructure 
    constructor.

    =============================================================================*/
    DataStructure obj(row,col,AliveCells);
    std::vector<std::vector<char>> vec = obj.getGrid();
    gridPlusOne = vec;
    myObj = obj;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Simulator::Simulator(std::string& Path)
{
    /*=============================================================================

    A constructor that takes one string argument a path to a file containing 
    a grid with alive and dead cells. This is done by calling the 
    respective DataStructure constructor.

    =============================================================================*/
    DataStructure obj(Path);
    std::vector<std::vector<char>> vec = obj.getGrid();
    gridPlusOne = vec;
    myObj = obj;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Simulator::~Simulator()
{
    /*=============================================================================

    Defult destuctor 

    =============================================================================*/

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Simulator::PrintGrid()
{
    /*=============================================================================

    Function that prints the current grid to consle.

    =============================================================================*/
    std::vector<std::vector<char>> printGrid = myObj.getGrid();
    for(int i = 0; i<printGrid.size(); i++)
    {
        for(int j = 0; j<printGrid[0].size(); j++)
        {
            std::cout << printGrid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Simulator::TakeStep()
{
    /*=============================================================================

    A funtion that evolves the DataStuctures object once with respect to the 
    rules of the game of life. Each time this function is called the Datastructure 
    object is evolved by one step.

    =============================================================================*/
    int i, j; 
    char alive = 'o';
    char dead = '-';
    myObj.setGrid(gridPlusOne);
    std::vector<std::vector<char>> grid = myObj.getGrid();
    for(i=0; i<myObj.getRow(); i++)
    {
        for(j=0; j<myObj.getCol(); j++)
        {
            int adjecntCells = myObj.countAliveCells(i,j);
            if(grid[i][j] == alive && (adjecntCells == 2 || adjecntCells == 3))
            {
                gridPlusOne[i][j] = alive;
            }
            else if(grid[i][j] == dead && adjecntCells == 3)
            {
                gridPlusOne[i][j] = alive;
            }
            else
            {
                gridPlusOne[i][j] = dead;
            }
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char Simulator::GetCell(int& GetCol, int& GetRow)
{
    /*=============================================================================

    Function that returns the cells contents of a specified cell.

    =============================================================================*/
    char output = myObj.GetCell(GetCol, GetRow);
    return output;
}   
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Simulator::SetCell(int& SetCol, int& SetRow, const bool& status)
{
    /*=============================================================================

    Function that sets the cells contents of a specified cell. With a boolean 
    value, where true represents an alive cell and false representing a dead 
    cell. 

    =============================================================================*/
    myObj.SetCell(SetCol, SetRow, status);
    
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::vector<std::vector<char>>  Simulator::getGrid_()
{
    /*=============================================================================

    A function that returns the grid of the DataStructure object.

    =============================================================================*/
    std::vector<std::vector<char>> grid_ = myObj.getGrid();
    return grid_;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::vector<std::vector<char>>  Simulator::getGridPlusOne()
{
    /*=============================================================================

    A function that returns the grid of a Simulator object.

    =============================================================================*/
    return gridPlusOne;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Simulator::setObj(DataStructure obj)
{
    /*=============================================================================

    Setting the myObj private member function to a different DataStrucure object

    =============================================================================*/
    myObj = obj;
    std::vector<std::vector<char>> Grid = myObj.getGrid();
    gridPlusOne = Grid;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DataStructure Simulator::getObj()
{
    /*=============================================================================

    Function that returns a DataStructure object.
    =============================================================================*/
    return myObj;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool Simulator::isEmpty()
{
    /*=============================================================================

    Function that checks if the grid of an instantiated object is empty

    =============================================================================*/
    return myObj.isEmpty();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
