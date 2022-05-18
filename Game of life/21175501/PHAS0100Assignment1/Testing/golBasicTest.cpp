/*=============================================================================

  PHAS0100ASSIGNMENT1: PHAS0100 Assignment 1 Game of Life Simulation.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "catch.hpp"
#include "golCatchMain.h"
#include "golMyFunctions.h"
#include "golDataStructure.h"
#include "golSimulator.h"
#include <iostream>
#include <vector>

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TEST_CASE( "Testing DataStructure() function" ) {
  DataStructure myObj;
  Simulator obj;
  std::vector<std::vector<char>> grid1 = myObj.getGrid();
  std::vector<std::vector<char>> grid2 = obj.getGridPlusOne();
  REQUIRE( grid1.size() == 0);
  REQUIRE( grid2.size() == 0);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TEST_CASE( "Testing DataStructure(int& row, int& col) and Simulator(int& row, int& col) function" ) {
  int col = 4, col1 = 300;
  int row = 5, row1 = 10000;
  int negative = -1;
  DataStructure myObj(row,col);
  std::vector<std::vector<char>> grid = myObj.getGrid();
  DataStructure myObj1(row1,col1);
  std::vector<std::vector<char>> grid1 = myObj1.getGrid();

  REQUIRE_THROWS_WITH( DataStructure(negative,col),"Cannot input negative values as column or row size");
  REQUIRE_THROWS_WITH( DataStructure(row,negative),"Cannot input negative values as column or row size");

  REQUIRE_THROWS_WITH( Simulator(negative,col),"Cannot input negative values as column or row size");
  REQUIRE_THROWS_WITH( Simulator(row,negative),"Cannot input negative values as column or row size");
  REQUIRE( grid.size() == row);
  REQUIRE( grid[0].size() == col);
  REQUIRE( grid1.size() == row1);
  REQUIRE( grid1[0].size() == col1);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TEST_CASE( "Testing DataStructure::GetCell function and DataStructure::SetCell function" ) {
  int col = 2, row = 2, getRow = 1, getCol = 1, negative = -1, outOfRange = 20;
  bool alive = true;
  DataStructure myObj(row,col);
  myObj.SetCell(getRow,getCol,alive);
  Simulator myObj1(row,col);
  myObj1.SetCell(getRow,getCol,alive);
  char getCell = myObj.GetCell(getRow, getCol);
  std::vector<std::vector<char>> grid = myObj.getGrid(); 
  REQUIRE( grid.size() == row);
  REQUIRE( grid[0].size() == col);
  REQUIRE( grid[getRow][getCol] == 'o');

  REQUIRE_THROWS_WITH( myObj.GetCell(negative,getCol),"input value out of row range");
  REQUIRE_THROWS_WITH( myObj.GetCell(outOfRange,getCol),"input value out of row range");
  REQUIRE_THROWS_WITH( myObj.GetCell(getRow,negative),"input value out of column range");
  REQUIRE_THROWS_WITH( myObj.GetCell(getRow,outOfRange),"input value out of column range");

  REQUIRE_THROWS_WITH( myObj.SetCell(negative,getCol,alive),"input value out of row range");
  REQUIRE_THROWS_WITH( myObj.SetCell(outOfRange,getCol,alive),"input value out of row range");
  REQUIRE_THROWS_WITH( myObj.SetCell(getRow,negative,alive),"input value out of column range");
  REQUIRE_THROWS_WITH( myObj.SetCell(getRow,outOfRange,alive),"input value out of column range");

  REQUIRE_THROWS_WITH( myObj1.GetCell(negative,getCol),"input value out of row range");
  REQUIRE_THROWS_WITH( myObj1.GetCell(outOfRange,getCol),"input value out of row range");
  REQUIRE_THROWS_WITH( myObj1.GetCell(getRow,negative),"input value out of column range");
  REQUIRE_THROWS_WITH( myObj1.GetCell(getRow,outOfRange),"input value out of column range");

  REQUIRE_THROWS_WITH( myObj1.SetCell(negative,getCol,alive),"input value out of row range");
  REQUIRE_THROWS_WITH( myObj1.SetCell(outOfRange,getCol,alive),"input value out of row range");
  REQUIRE_THROWS_WITH( myObj1.SetCell(getRow,negative,alive),"input value out of column range");
  REQUIRE_THROWS_WITH( myObj1.SetCell(getRow,outOfRange,alive),"input value out of column range");
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TEST_CASE( "Testing DataStructure(int& row, int& col, int& AliveCells) and DataStructure(int& row, int& col, int& AliveCells) function" ) {
  int col = 6, col1 = 10;
  int row = 4, row1 = 30;
  int AliveCells = 10, AliveCells1 = 200;
  int negative = -1;
  DataStructure myObj1(row,col,AliveCells);
  DataStructure myObj2(row,col,AliveCells);
  std::vector<std::vector<char>> grid1 = myObj1.getGrid();
  std::vector<std::vector<char>> grid2 = myObj2.getGrid();
  int count = 0;
  for(int i = 0; i < row; i++)
  {
    for(int j = 0; j < col; j++)
    {
      if(grid1[i][j] == 'o')
      count++;
    }
  }
  REQUIRE(count == AliveCells);
  REQUIRE( grid1.size() == row);
  REQUIRE( grid1[0].size() == col);
  REQUIRE( grid1 != grid2);
  REQUIRE( myObj1.getAliveCells() == AliveCells);
  
  DataStructure Obj1(row1,col1,AliveCells1);
  DataStructure Obj2(row1,col1,AliveCells1);
  std::vector<std::vector<char>> grid3 = Obj1.getGrid();
  std::vector<std::vector<char>> grid4 = Obj2.getGrid();
  int count1 = 0;
  for(int i = 0; i < row1; i++)
  {
    for(int j = 0; j < col1; j++)
    {
      if(grid3[i][j] == 'o')
      count1++;
    }
  }
  REQUIRE(count1 == AliveCells1);
  REQUIRE( grid3.size() == row1);
  REQUIRE( grid3[0].size() == col1);
  REQUIRE( grid3 != grid4);
  REQUIRE( Obj1.getAliveCells() == AliveCells1);
  
  REQUIRE_THROWS_WITH( DataStructure(row,negative, AliveCells),"Cannot input negative values as column, row size or number of alive cells");
  REQUIRE_THROWS_WITH( DataStructure(negative,col, AliveCells),"Cannot input negative values as column, row size or number of alive cells");
  REQUIRE_THROWS_WITH( Simulator(row,negative, AliveCells),"Cannot input negative values as column, row size or number of alive cells");
  REQUIRE_THROWS_WITH( Simulator(negative,col, AliveCells),"Cannot input negative values as column, row size or number of alive cells");
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TEST_CASE( "Testing DataStructure(std::string& Path) function" ) {
  std::string oscillators = "/workspaces/21175501/PHAS0100Assignment1/Testing/Data/oscillators.txt";
  std::string thisIsALie = "/workspaces/21175501/PHAS0100Assignment1/Testing/Data/notHere.txt";
  DataStructure myObj(oscillators);
  REQUIRE_NOTHROW(DataStructure(oscillators));
  REQUIRE_THROWS_WITH(DataStructure(thisIsALie),"File path does not exist");
  REQUIRE_THROWS_WITH(Simulator(thisIsALie),"File path does not exist");
}

TEST_CASE("Testing DataStructure::countAliveCells(int& row, int& col) function"){
int col = 2, row = 2, zero = 0, one = 1, negative = -1, outOfRange = 20;
bool alive = true;
DataStructure myObj(row,col);
myObj.SetCell(zero,zero,alive);
myObj.SetCell(zero,one,alive);
REQUIRE(myObj.countAliveCells(one,one) == col);
REQUIRE_THROWS_WITH(myObj.countAliveCells(one, negative), "Cannot input values out of range of col or row");
REQUIRE_THROWS_WITH(myObj.countAliveCells(one, outOfRange), "Cannot input values out of range of col or row");
REQUIRE_THROWS_WITH(myObj.countAliveCells(negative, one), "Cannot input values out of range of col or row");
REQUIRE_THROWS_WITH(myObj.countAliveCells(outOfRange, one), "Cannot input values out of range of col or row");
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
TEST_CASE("Testing DataStructure::isEmpty()"){
  int row = 2, col = 2, isAlive = 0;
  DataStructure obj(row,col);
  Simulator obj1(row,col);
  DataStructure obj2(row,col,isAlive);
  Simulator obj3(row,col,isAlive);
  REQUIRE(obj.isEmpty() == true);
  REQUIRE(obj1.isEmpty() == true);
  REQUIRE(obj2.isEmpty() == true);
  REQUIRE(obj3.isEmpty() == true);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------