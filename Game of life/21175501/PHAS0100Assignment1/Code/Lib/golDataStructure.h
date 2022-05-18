#ifndef GOLDATASTRUCTURE_H
#define GOLDATASTRUCTURE_H
#include <iostream>
#include <vector>
#include <tuple>

class DataStructure {
    /*=============================================================================

    The DataStructure class is made to store the grid for the game of life.
    The class contains 4 constructors which can be called using a different number
    of inputs in the class instatiation.
    The grid is stored as a vector containing vectors of char, with '-' 
    representing a dead cell and 'o' representing an alive cell.
    This class should is used with the Simulator class in golSimulator.h.

    =============================================================================*/
    public:
        DataStructure();
        DataStructure(int& row, int& col);
        DataStructure(int& row, int& col, int& AliveCells);
        DataStructure(std::string& Path);
        ~DataStructure();
        void PrintGrid();
        char GetCell(int& GetCol, int& GetRow);
        void SetCell(int& SetCol, int& SetRow, const bool& status);
        int countAliveCells(int& row, int& col);
        std::vector<std::vector<char>> getGrid();
        int getRow();
        int getCol();
        int getAliveCells();
        void setGrid(std::vector<std::vector<char>>& grid);
        bool isEmpty();
    private:
        int col_;
        int row_;
        int AliveCells_;
        std::vector<std::vector<char>> grid_;
};
#endif 