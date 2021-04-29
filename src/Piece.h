//
//  Piece.h
//  Tetris
//
//  Created by Andy Mina on 4/27/21.
//

#ifndef Piece_h
#define Piece_h

#include <vector>
#include <iostream>
#include "raylib.h"
#include "Global.h"
#include "Block.h"

using std::vector;
using std::cout; using std::endl;

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
   Fall speed of the piece in boxes per second (bps). Defaults to 1 bps.
  */
  int fall_speed;
  /**
   Indicates if the piece is locked or not.
  */
  bool locked;
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
  bool left() {
    // Create a copy of the current blocks to be updated
    vector<Block> updated = this->blocks;
    
    // Move each block. If it can't be moved, return false.
    for (Block &b : updated)
      if (!b.left())
        return false;
    
    // Update the current group of blocks and return true
    this->blocks = updated;
    return true;
  }
  
  /**
   Translate piece right by 1 block.
   @return: true if the piece was moved; false otherwise.
  */
  bool right() {
    // Create a copy of the current blocks to be updated
    vector<Block> updated = this->blocks;
    
    // Move each block. If it can't be moved, return false.
    for (Block &b : updated)
      if (!b.right())
        return false;
    
    // Update the current group of blocks and return true
    this->blocks = updated;
    return true;
  }
  
  /**
   Translate piece down by 1 block.
   @return: true if the piece was moved; false otherwise.
  */
  bool down() {
    // Create a copy of the current blocks to be updated
    vector<Block> updated = this->blocks;
    
    // Move each block. If it can't be moved, return false.
    for (Block &b : updated)
      if (!b.down())
        return false;
    
    // Update the current group of blocks and return true
    this->blocks = updated;
    return true;
  }
  
  /**
   Rotate the piece clockwise.
   @return: true if the piece was rotated; false otherwise.
  */
  bool rotateClockwise() {
    // Create a new updated position
    vector<Block> updated = this->blocks;
    // Define the center of rotation
    Block center = updated[1];
    
    // Perform the geometric rotation on every block.
    for (Block &b : updated)
      if (!b.rotateCW(center))
        return false;
    
    return true;
  }
  
  /**
   Rotate the piece counter-clockwise.
   @return: true if the piece was rotated; false otherwise.
  */
  bool rotateCounterClockwise() {
    // Create a new updated position
    vector<Block> updated = this->blocks;
    // Define the center of rotation
    Block center = updated[1];
    
    // Perform the geometric rotation on every block.
    for (Block &b : updated)
      if (!b.rotateCCW(center))
        return false;
    
    return true;
  }
    
public:
  /**
   Public constructor.
   
   @param piece_type - The type of piece to be created. Can be any of PIECE_TYPE.
   @param fall_speed - Set the fall speed for this piece. Defaults to 1 block per second (bps).
  */
  Piece(const PIECE_TYPE &piece_type, const int &fall_speed = 1) {
    // Set the piece type
    this->type = piece_type;
    // Set fall speed
    this->fall_speed = fall_speed;
    
    // Set the starting position for each piece
    switch (piece_type) {
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
  void update() {
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
   Allows the piece to fall. Simulates gravity.
   
   @param frames - the number of the current frame. Used to calculate fall speed.
   */
  void fall(int &frames) {
    // Calculate if the piece should've fallen by now.
    if (frames >= (FPS / this->fall_speed)) {
      frames = 0;
      this->down();
    }
  }
  
  /**
   Draws the piece on the screen at its current position.
  */
  void draw() {
    for (Block const &b : this->blocks)
      b.draw();
  }
};

#endif /* Piece_h */
