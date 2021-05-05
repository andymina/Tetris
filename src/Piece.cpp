//
//  Piece.cpp
//  Tetris
//
//  Created by Andy Mina on 5/4/21.
//

#include "Piece.hpp"

// --- BEGIN PRIVATE ---

/**
 Translate piece left by 1 block.
 @return: true if the piece was moved; false otherwise.
*/
bool Piece::left() {
  // Create a copy of the current blocks to be updated
  vector<Block> updated = this->blocks;
  
  // Move each block. If it can't be moved, return false.
  for (Block &b : updated) {
    if (!b.left(this->board))
      return false;
  }

  // Update the current group of blocks and return true
  this->blocks = updated;
  return true;
}

/**
 Translate piece right by 1 block.
 @return: true if the piece was moved; false otherwise.
*/
bool Piece::right() {
  // Create a copy of the current blocks to be updated
  vector<Block> updated = this->blocks;
  
  // Move each block. If it can't be moved, return false.
  for (Block &b : updated)
    if (!b.right(this->board))
      return false;
  
  // Update the current group of blocks and return true
  this->blocks = updated;
  return true;
}

/**
 Translate piece down by 1 block.
 @return: true if the piece was moved; false otherwise.
*/
bool Piece::down() {
  // Create a copy of the current blocks to be updated
  vector<Block> updated = this->blocks;
  
  // Move each block. If it can't be moved, return false.
  for (Block &b : updated)
    if (!b.down(this->board))
      return false;
  
  // Update the current group of blocks and return true
  this->blocks = updated;
  return true;
}

/**
 Rotate the piece clockwise.
 @return: true if the piece was rotated; false otherwise.
*/
bool Piece::rotateClockwise() {
  // Create a new updated position
  vector<Block> updated = this->blocks;
  // Define the center of rotation
  Block &center = updated[1];
  
  // Perform the geometric rotation on every block.
  for (Block &b : updated)
    if (!b.rotateCW(center, this->board))
      return false;
  
  // Update the blocks
  this->blocks = updated;
  return true;
}

/**
 Rotate the piece counter-clockwise.
 @return: true if the piece was rotated; false otherwise.
*/
bool Piece::rotateCounterClockwise() {
  // Create a new updated position
  vector<Block> updated = this->blocks;
  // Define the center of rotation
  Block &center = updated[1];
  
  // Perform the geometric rotation on every block.
  for (Block &b : updated)
    if (!b.rotateCCW(center, this->board))
      return false;
  
  // Update the blocks
  this->blocks = updated;
  return true;
}

// --- END PRIVATE ---

// --- BEGIN PUBLIC ---

/**
 Public constructor.
 
 @param b - A const ref to the current state of the board. Used in transformations.
*/
Piece::Piece(vector<vector<Block>> &b, const PIECE_TYPE &type): board(b) {
  // Generate a random piece type
  this->type = type;
  
  // Set the starting position for each piece
  switch (this->type) {
    case I_BLOCK:
      this->color = SKYBLUE;
      this->blocks = {
        Block({ 5, 0 }, this->color),
        Block({ 5, 1 }, this->color),
        Block({ 5, 2 }, this->color),
        Block({ 5, 3 }, this->color)
      };
      break;
      
    case O_BLOCK:
      this->color = YELLOW;
      this->blocks = {
        Block({ 4, 0 }, this->color),
        Block({ 4, 1 }, this->color),
        Block({ 5, 0 }, this->color),
        Block({ 5, 1 }, this->color)
      };
      break;
  
    case J_BLOCK:
      this->color = BLUE;
      this->blocks = {
        Block({ 5, 0 }, this->color),
        Block({ 5, 1 }, this->color),
        Block({ 5, 2 }, this->color),
        Block({ 4, 2 }, this->color)
      };
      break;
      
    case L_BLOCK:
      this->color = ORANGE;
      this->blocks = {
        Block({ 4, 0 }, this->color),
        Block({ 4, 1 }, this->color),
        Block({ 4, 2 }, this->color),
        Block({ 5, 2 }, this->color)
      };
      break;
    
    case S_BLOCK:
      this->color = GREEN;
      this->blocks = {
        Block({ 4, 0 }, this->color),
        Block({ 4, 1 }, this->color),
        Block({ 5, 1 }, this->color),
        Block({ 5, 2 }, this->color)
      };
      break;
    
    case Z_BLOCK:
      this->color = RED;
      this->blocks = {
        Block({ 5, 0 }, this->color),
        Block({ 5, 1 }, this->color),
        Block({ 4, 1 }, this->color),
        Block({ 4, 2 }, this->color)
      };
      break;
      
    case T_BLOCK:
      this->color = PURPLE;
      this->blocks = {
        Block({ 4, 0 }, this->color),
        Block({ 3, 1 }, this->color),
        Block({ 4, 1 }, this->color),
        Block({ 5, 1 }, this->color)
      };
      break;
  }
}

/**
 Allows the piece to be updated by user input. User can use LEFT to move left,
 RIGHT to move right, DOWN to move down, Z to rotate counter-clockwise, and
 X or UP to rotate clockwise.
 */
void Piece::update() {
  // Translations
  if (IsKeyPressed(KEY_LEFT)) this->left();
  if (IsKeyPressed(KEY_RIGHT)) this->right();
  if (IsKeyPressed(KEY_DOWN)) this->down();
  // Rotations - O_BLOCKs dont rotate
  if (this->type != O_BLOCK && (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_X)))
    this->rotateClockwise();
  if (this->type != O_BLOCK && IsKeyPressed(KEY_Z))
    this->rotateCounterClockwise();
}

/**
 Allows the piece to fall. Simulates gravity. If the piece has failed to fall,
 more than three times it should be locked.
 
 @return: true if the piece fell, false otherwise
 */
bool Piece::fall() {
  return this->down();
}

/**
 Gets the blocks of this piece
*/
vector<Block> Piece::getBlocks() {
  return this->blocks;
}

/**
 Draws the piece on the screen at its current position.
*/
void Piece::draw() {
  for (Block const &b : this->blocks)
    b.draw();
}
