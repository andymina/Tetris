//
//  Piece.h
//  Tetris
//
//  Created by Andy Mina on 4/27/21.
//

#ifndef Piece_h
#define Piece_h

#include <vector>
#include <algorithm>
#include <iostream>
#include "raylib.h"

// Define global vars
#define ROWS 20
#define COLUMNS 10
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 800
#define FPS 60
#define BOX_SIZE WINDOW_WIDTH / COLUMNS

using std::vector;
using std::cout;

enum PIECE_TYPE {
  I_BLOCK, O_BLOCK,
  J_BLOCK, L_BLOCK,
  S_BLOCK, Z_BLOCK,
  T_BLOCK
};

class Piece {
private:
  /**
   Each piece is made up of four BOX_SIZE squares arranged in different manners.
   The vector holds all of the top-left corners for each square since squares are drawn
   starting from their top-left corners.
  */
  vector<Vector2> position;
  /**
   The fall speed of the piece in boxes per second (bps). Defaults to 1 bps.
  */
  int fall_speed;
  /**
   Flag variables that indicates if the piece is locked or not.
  */
  bool locked;
  /**
   The color of the piece.
  */
  Color color;
  
  /**
   Translate piece left by 1 * BOX_SIZE.
  */
  void left() {
    // Create a new position to update
    vector<Vector2> updated = this->position;
    // Move each square and check if the coord is in bounds
    for (int i = 0; i < updated.size(); i++) {
      // If the new position would be OOB, return
      if (updated[i].x - BOX_SIZE < 0)
        return;
      // Otherwise update the square to the new position
      updated[i].x -= BOX_SIZE;
    }
    
    // Update this->position
    this->position = updated;
  }
  
  /**
   Translate piece right by 1 * BOX_SIZE.
  */
  void right() {
    // Create a new position to update
    vector<Vector2> updated = this->position;
    // Move each square and check if the coord is in bounds
    for (int i = 0; i < updated.size(); i++) {
      // If the new position would be OOB, return
      if (updated[i].x + BOX_SIZE > WINDOW_WIDTH - BOX_SIZE)
        return;
      // Otherwise update the square to the new position
      updated[i].x += BOX_SIZE;
    }
    
    // Update this->position
    this->position = updated;
  }
  
  /**
    Translate piece down by 1 * BOX_SIZE.
  */
  void down() {
    // Create a new position to update
    vector<Vector2> updated = this->position;
    // Move each square and check if the coord is in bounds
    for (int i = 0; i < updated.size(); i++) {
      // If the new position would be OOB, return
      if (updated[i].y + BOX_SIZE > WINDOW_HEIGHT - BOX_SIZE)
        return;
      // Otherwise update the square to the new position
      updated[i].y += BOX_SIZE;
    }
    
    // Update this->position
    this->position = updated;
  }
  
  /**
   Rotate the piece clockwise. Update width and height.
  */
  void rotateClockwise() {
    // Create a new updated position
    vector<Vector2> updated = this->position;
    // Define the center of rotation
    Vector2 center = updated[1];
    
    // Perform the geometric rotation
    for (Vector2 &coord : updated) {
      // Translate the rotated point so that center is the 'origin'
      coord.x -= center.x;
      coord.y -= center.y;
      
      // Apply the rotation rule
      std::swap(coord.x, coord.y);
      coord.y *= -1;
      
      // Translate it back
      coord.x += center.x;
      coord.y += center.y;
    }
    
    // If the entire rotated is in bounds, update position
    if (this->isInBounds(updated))
      this->position = updated;
  }
  
  /**
   Rotate the piece counter-clockwise. Update width and height.
  */
  void rotateCounterClockwise() {
    // Create a new updated position
    vector<Vector2> updated = this->position;
    // Define the center of rotation
    Vector2 center = updated[1];
    
    // Perform the geometric rotation
    for (Vector2 &coord : updated) {
      // Translate the rotated point so that center is the 'origin'
      coord.x -= center.x;
      coord.y -= center.y;
      
      // Apply the rotation rule
      std::swap(coord.x, coord.y);
      coord.x *= -1;
      
      // Translate it back
      coord.x += center.x;
      coord.y += center.y;
    }
    
    // If the entire rotated is in bounds, update position
    if (this->isInBounds(updated))
      this->position = updated;
  }
  
  /**
   Checks if the entire piece is in bounds. Used in rotation functions.
   @param position The position to be checked
   @return true if in bounds, false otherwise.
  */
  bool isInBounds(const vector<Vector2> &position) {
    // Loop through all of the coords
    for (Vector2 const &coord : position) {
      // return false if coords OOB
      if (coord.x < 0 || coord.x > WINDOW_WIDTH - BOX_SIZE)
        return false;
      if (coord.y > WINDOW_HEIGHT - BOX_SIZE)
        return false;
    }
    // return true if coords are in bounds
    return true;
  }
  
public:
  /**
   Public constructor.
   
   @param type - The type of piece to be created. Can be any of PIECE_TYPE.
   @param fall_speed - Set the fall speed for this piece. Defaults to 1 bps.
  */
  Piece(PIECE_TYPE type, int fall_speed = 1) {
    // Set the starting position for each piece
    switch (type) {
      case I_BLOCK:
        this->position = {
          { 5 * BOX_SIZE, 0 * BOX_SIZE },
          { 5 * BOX_SIZE, 1 * BOX_SIZE },
          { 5 * BOX_SIZE, 2 * BOX_SIZE },
          { 5 * BOX_SIZE, 3 * BOX_SIZE }
        };
        this->color = SKYBLUE;
        break;
        
      case O_BLOCK:
        this->position = {
          { 4 * BOX_SIZE, 0 * BOX_SIZE },
          { 4 * BOX_SIZE, 1 * BOX_SIZE },
          { 5 * BOX_SIZE, 0 * BOX_SIZE },
          { 5 * BOX_SIZE, 1 * BOX_SIZE }
        };
        this->color = YELLOW;
        break;
        
      case J_BLOCK:
        this->position = {
          { 5 * BOX_SIZE, 0 * BOX_SIZE },
          { 5 * BOX_SIZE, 1 * BOX_SIZE },
          { 5 * BOX_SIZE, 2 * BOX_SIZE },
          { 4 * BOX_SIZE, 2 * BOX_SIZE }
        };
        this->color = BLUE;
        break;
        
      case L_BLOCK:
        this->position = {
          { 4 * BOX_SIZE, 0 * BOX_SIZE },
          { 4 * BOX_SIZE, 1 * BOX_SIZE },
          { 4 * BOX_SIZE, 2 * BOX_SIZE },
          { 5 * BOX_SIZE, 2 * BOX_SIZE }
        };
        this->color = ORANGE;
        break;
      
      case S_BLOCK:
        this->position = {
          { 4 * BOX_SIZE, 0 * BOX_SIZE },
          { 4 * BOX_SIZE, 1 * BOX_SIZE },
          { 5 * BOX_SIZE, 1 * BOX_SIZE },
          { 5 * BOX_SIZE, 2 * BOX_SIZE }
        };
        this->color = GREEN;
        break;
      
      case Z_BLOCK:
        this->position = {
          { 5 * BOX_SIZE, 0 * BOX_SIZE },
          { 5 * BOX_SIZE, 1 * BOX_SIZE },
          { 4 * BOX_SIZE, 1 * BOX_SIZE },
          { 4 * BOX_SIZE, 2 * BOX_SIZE }
        };
        this->color = RED;
        break;
        
      case T_BLOCK:
        this->position = {
          { 4 * BOX_SIZE, 0 * BOX_SIZE },
          { 3 * BOX_SIZE, 1 * BOX_SIZE },
          { 4 * BOX_SIZE, 1 * BOX_SIZE },
          { 5 * BOX_SIZE, 1 * BOX_SIZE }
        };
        this->color = PURPLE;
        break;
    }
    // Set fall speed
    this->fall_speed = fall_speed;
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
    // Rotations
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_X)) this->rotateClockwise();
    if (IsKeyPressed(KEY_Z)) this->rotateCounterClockwise();
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
    for (auto const &coord : this->position)
      DrawRectangle(coord.x, coord.y, BOX_SIZE, BOX_SIZE, color);
    
  }
};

#endif /* Piece_h */
