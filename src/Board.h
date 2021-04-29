//
//  Board.h
//  Tetris
//
//  Created by Andy Mina on 4/28/21.
//

#ifndef Board_h
#define Board_h

#include <vector>
#include <string>
#include "raylib.h"
#include "Global.h"

using std::vector;
using std::string;

class Board {
private:
  vector<vector<Block>> board;
  /**
   # of rows and cols on the board
  */
  int rows;
  int cols;
  
public:
  Board(const int &rows = ROWS, const int &cols = COLS) {
    this->rows = rows;
    this->cols = cols;
  }
  
  void lock(const Vector2 &coord) {
    
  }
  
  void drawBlocks() {
    // Draw only the blocks that are present
    for (int i = 0; i < this->board.size(); i++)
      for (int j = 0; j < this->board[i].size(); j++)
        this->board[i][j].draw();
  }
  
  // Draws the grid overlay
  void drawGrid() {
    // Draw rows
    for (int i = 0; i < this->rows; i++)
      DrawLine(0, i * BLOCK_SIZE, WINDOW_WIDTH, i * BLOCK_SIZE, WHITE);
    
    // Draw columns
    for (int i = 0; i < this->cols; i++)
      DrawLine(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, WINDOW_HEIGHT, WHITE);
  }
  
  void draw() {
    this->drawBlocks();
    this->drawGrid();
  }
};

#endif /* Board_h */
