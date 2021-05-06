//
//  Board.hpp
//  Tetris
//
//  Created by Andy Mina on 5/4/21.
//

#ifndef Board_hpp
#define Board_hpp

#include <vector>
#include <utility>
#include <random>
#include <time.h>
#include "raylib.h"
#include "Global.hpp"
#include "Block.hpp"
#include "Piece.hpp"

using std::vector;
using std::default_random_engine;
using std::uniform_int_distribution;

class Board {
private:
  /**
   Stores the blocks on the board
  */
  vector<vector<Block>> board;
  /**
   The active piece.
  */
  Piece* active;
  /**
   Fall speed of the active piece.
  */
  int fall_speed;
  /**
   Keeps track of how many times the piece has failed to fall.
  */
  int failed_falls;
  /**
   # of rows and cols on the board
  */
  int rows;
  int cols;
  /**
   Generator for random numbers
  */
  default_random_engine generator;
  /**
   Define distribution for random numbers.
  */
  uniform_int_distribution<int> rng;
  
  /**
   Locks the active piece onto the board.
  */
  void lockPiece();
  
  /**
   Sets a new random piece as the active piece and deletes the old one.
  */
  void newPiece();
  
  /**
   If the row is fill, it will be cleared.
   @returns - True if the row was cleared; false otherwise.
  */
  bool checkRow(const int &row_index);
  
  void clearRow(const int &row_index);
  
  void updateBoard();
  
  /**
   Draws all of the blocks on the screen.
  */
  void drawBlocks();
  
  /**
   Draws the grid overlay.
  */
  void drawGrid();

  
public:
  /**
   Public constructor that creates a board.
   
   @param rows - The number of rows on the board. Defaults to Global::ROWS
   @param cols - The number of cols on the board. Defaults to Global::COLS
   @param fall_speed - The fall speed of the blocks to be generated. Defaults to 1 bps.
   */
  Board(const int &rows = ROWS, const int &cols = COLS, const int &fall_speed = 1);
  
  /**
   Allows the piece to be updated by user input. User can use LEFT to move left,
   RIGHT to move right, DOWN to move down, Z to rotate counter-clockwise, and
   X or UP to rotate clockwise.
   */
  void update();
  

  
  /**
   Drops the current piece by fall_speed to simulate gravity.
  */
  void fall(int &frames);
    
  /**
   Draws the board.
  */
  void draw();
};

#endif /* Board_hpp */
