//
//  Piece.hpp
//  Tetris
//
//  Created by Andy Mina on 5/4/21.
//

#ifndef Piece_hpp
#define Piece_hpp

#include <vector>
#include <random>
#include "raylib.h"
#include "Global.hpp"
#include "Block.hpp"

using std::vector;
using std::cout; using std::endl;
using std::to_string;

// Enums to define which type of piece
enum PIECE_TYPE {
  I_BLOCK, O_BLOCK,
  J_BLOCK, L_BLOCK,
  S_BLOCK, Z_BLOCK,
  T_BLOCK
};

class Piece {
private:
  /**
   Each piece is made up of four <Blocks> arranged in different ways.
   Holds all of the <Blocks> together.
  */
  vector<Block> blocks;
  /**
   The state of the board this piece is being rendered on.
  */
  vector<vector<Block>> &board;
  /**
   Type of piece
  */
  PIECE_TYPE type;
  /**
   The color of the piece.
  */
  Color color;
  
  /**
   Translate piece left by 1 block.
   
   @return: true if the piece was moved; false otherwise.
  */
  bool left();
  
  /**
   Translate piece right by 1 block.
   
   @return: true if the piece was moved; false otherwise.
  */
  bool right();
  
  /**
   Translate piece down by 1 block.
   
   @return: true if the piece was moved; false otherwise.
  */
  bool down();
  
  /**
   Rotate the piece clockwise.
   
   @return: true if the piece was rotated; false otherwise.
  */
  bool rotateClockwise();
  
  /**
   Rotate the piece counter-clockwise.
   
   @return: true if the piece was rotated; false otherwise.
  */
  bool rotateCounterClockwise();
  
public:
  /**
   Public constructor.
  */
  Piece(vector<vector<Block>> &b, const PIECE_TYPE &type);
  
  /**
   Allows the piece to be updated by user input. User can use LEFT to move left,
   RIGHT to move right, DOWN to move down, Z to rotate counter-clockwise, and
   X or UP to rotate clockwise.
   */
  void update();
  
  /**
   Allows the piece to fall. Simulates gravity. If the piece has failed to fall,
   more than three times it should be locked.
   
   @return: true if the piece fell, false otherwise
   */
  bool fall();
  
  /**
   Gets the blocks of this piece
  */
  vector<Block> getBlocks();

  /**
   Draws the piece on the screen at its current position.
  */
  void draw();
};

#endif /* Piece_hpp */
