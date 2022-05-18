#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <algorithm>
#include "golDataStructure.h"
#include <stdexcept>
#include <typeinfo>
#include <filesystem>

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DataStructure::DataStructure()
{
    /*=============================================================================

    This is the defult constructor that sets all private member functions to 
    zero value.

    =============================================================================*/
    int defult = 0;
    col_ = defult;
    row_ = defult;
    AliveCells_ = 0;
    std::vector<std::vector<char>> grid(defult,std::vector<char> (defult, '-'));
    grid_ = grid;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DataStructure::DataStructure(int& row, int& col)
{
    /*=============================================================================

    Constructor that creates a grid with row number of rows and col number 
    of columns, this constructor instantiates an object with an empty grid.

    =============================================================================*/
    if(row < 0 || col < 0)
    {
        throw std::invalid_argument("Cannot input negative values as column or row size");
    }
    col_ = col;
    row_ = row;
    std::vector<std::vector<char>> grid(row, std::vector<char> (col, '-'));
    grid_ = grid;
    AliveCells_ = 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DataStructure::DataStructure(int& row, int& col, int& AliveCells)
{
    /*=============================================================================

    Constructor that creates a grid with row number of rows and col number 
    of columns, this constructor instantiates an object with AliveCells number 
    of cells that are alive. The alive cells are set at a random position in 
    the grid. The random number gernerator uses the hardware to obtain 
    each random number.

    =============================================================================*/
    if(row < 0 || col < 0 || AliveCells < 0)
    {
        throw std::invalid_argument("Cannot input negative values as column, row size or number of alive cells");
    }
    col_ = col;
    row_ = row;
    AliveCells_ = AliveCells;
    std::vector<std::vector<char>> grid(row, std::vector<char> (col, '-'));

    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distRow(0, row_-1); 
    std::uniform_int_distribution<> distCol(0, col_-1); 
    
    std::srand((unsigned) time(0));
    for(int i=0; i < AliveCells_; i++)
    {
        int RowInd = distRow(gen);
        int ColInd = distCol(gen);
        //std::cout << RowInd << "  " << AliveCells_ << "  " << ColInd << std::endl;
        if(grid[RowInd][ColInd] == 'o')
        {
            i--;
            continue;
        }
        else
        {
            grid[RowInd][ColInd] = 'o';
        }
    }
    grid_ = grid;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DataStructure::DataStructure(std::string& Path)
{   
    /*=============================================================================

    A constructor that takes one string argument a path to a file containing 
    a grid with alive and dead cells.

    =============================================================================*/
    if(std::filesystem::exists(Path) == 0)
    {
        throw std::invalid_argument("File path does not exist");
    } 
    std::ifstream file(Path);
    std::string line;
    std::vector<std::vector<char>> grid;
    while (std::getline(file, line))
    {
        std::vector<char> row;
        for(char &c : line)
        {
            if(c != '\n')
            {
                if(c != ' ')
                {
                    if(c == '-' || c == 'o')
                    {
                        row.push_back(c);
                    }
                    else
                    {
                        throw std::invalid_argument("File has invalid input");
                    }
                }
            }
        }
        grid.push_back(row);
    }
    grid_ = grid;
    row_ = grid.size();
    col_ = grid[0].size();

    int count = 0;
    for(int i = 0; i < row_; i++)
    {
        for(int j = 0; j < col_; j++)
        {
        if(grid[i][j] == 'o')
        count++;
        }
    }
    AliveCells_ = count;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
DataStructure::~DataStructure()
{
    /*=============================================================================

    Class destructor

    =============================================================================*/
    row_ = 0;
    col_ = 0;
    AliveCells_ = 0;
    std::vector<std::vector<char>> grid_(0,std::vector<char> (0, '-'));

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void DataStructure::PrintGrid()
{
    /*=============================================================================

    Function that prints the instantiated objects grid.

    =============================================================================*/
    for(int i = 0; i<row_; i++)
    {
        for(int j = 0; j<col_; j++)
        {
            std::cout << grid_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
char DataStructure::GetCell(int& GetCol, int& GetRow)
{
    /*=============================================================================

    Function that returns the cells contents of a specified cell.

    =============================================================================*/
    if(GetCol < 0 || GetCol >= col_ )
    {
        throw std::invalid_argument("input value out of row range");
    }
    else if(GetRow < 0 || GetRow >= row_)
    {
        throw std::invalid_argument("input value out of column range");
    }

    if(grid_[GetRow][GetCol] == '-')
    {
        //std::cout << "Dead" << std::endl;
        return '-';
    }
    else
    {
        //std::cout << "This Cell Is Alive" << std::endl;
        return 'o';
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void DataStructure::SetCell(int& SetCol, int& SetRow, const bool& Status)
{
    /*=============================================================================

    Function that sets the cells contents of a specified cell. With a boolean 
    value, where true represents an alive cell and false representing a dead 
    cell. 

    =============================================================================*/
    if(SetCol < 0 || SetCol >= col_ )
    {
        throw std::invalid_argument("input value out of row range");
    }
    else if(SetRow < 0 || SetRow >= row_)
    {
        throw std::invalid_argument("input value out of column range");
    }

    if(SetCol < 0 || SetRow < 0 )
    {
        throw std::invalid_argument("Cannot input negative values as column, row");
    }
    if(Status == true)
    {
        grid_[SetRow][SetCol] = 'o';
    }
    else
    {
        grid_[SetRow][SetCol] = '-';
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int DataStructure::countAliveCells(int& row, int& col)
{
    /*=============================================================================

    Function that calculates the number of alive cells adjecent to the cell 
    specified with row and col inputs.

    =============================================================================*/
    if(row < 0 || col < 0 || row >= row_ || col >= col_)
    {
        throw std::invalid_argument("Cannot input values out of range of col or row");
    }
    const int start = 0;
    const int endCol = col_;
    const int endRow = row_; 
    int neighbouringCells = 0;
    char alive = 'o';

    if(row+1 >= start && row+1 < endRow && col >= start && col < endCol && grid_[row+1][col] == alive)
    {
        ++neighbouringCells;
    }
    if(row-1 >= start && row-1 < endRow && col >= start && col < endCol && grid_[row-1][col] == alive)
    {
        ++neighbouringCells;
    }
    if(row >= start && row < endRow && col+1 >= start && col+1 < endCol && grid_[row][col+1] == alive)
    {
        ++neighbouringCells;
    }
    if(row >= start && row < endRow && col-1 >= start && col-1 < endCol && grid_[row][col-1] == alive)
    {
        ++neighbouringCells;
    }
    if(row+1 >= start && row+1 < endRow && col+1 >= start && col+1 < endCol && grid_[row+1][col+1] == alive)
    {
        ++neighbouringCells;
    }
    if(row+1 >= start && row+1 < endRow && col-1 >= start && col-1 < endCol && grid_[row+1][col-1] == alive)
    {
        ++neighbouringCells;
    }
    if(row-1 >= start && row-1 < endRow && col+1 >= start && col+1 < endCol && grid_[row-1][col+1] == alive)
    {
        ++neighbouringCells;
    }
    if(row-1 >= start && row-1 < endRow && col-1 >= start && col-1 < endCol && grid_[row-1][col-1] == alive)
    {
        ++neighbouringCells;
    }
    return neighbouringCells;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
std::vector<std::vector<char>> DataStructure::getGrid()
{
    /*=============================================================================

    A function that returns the grid of an istantiated object.

    =============================================================================*/
    return grid_;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int DataStructure::getRow()
{
    /*=============================================================================

    A function that returns the row of an istantiated object.

    =============================================================================*/
    return row_;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int DataStructure::getCol()
{
    /*=============================================================================

    A function that returns the column of an istantiated object.

    =============================================================================*/
    return col_;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int DataStructure::getAliveCells()
{
    /*=============================================================================

    A function that returns the number of alive celss of an istantiated object.

    =============================================================================*/
    return AliveCells_;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void DataStructure::setGrid(std::vector<std::vector<char>>& grid)
{
    /*=============================================================================

    A function that can set the value of the private member grid_.

    =============================================================================*/
    grid_ = grid;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool DataStructure::isEmpty()
{
    /*=============================================================================

    Function that checks if the grid of an instantiated object is empty

    =============================================================================*/
    std::vector<std::vector<char>> grid(row_, std::vector<char> (col_, '-'));
    if(grid_ == grid)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------