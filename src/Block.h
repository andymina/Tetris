//
//  Block.h
//  Tetris
//
//  Created by Andy Mina on 4/28/21.
//

#ifndef Block_h
#define Block_h

#include "raylib.h"
#include "Global.h"

class Block {
private:
  // Coords of the box
  Vector2 coords;
  // Color of the box
  Color color;
  
public:
  /**
   Public constructor.
   
   @param coords - Coords of the top-left corner of the block.
   @param color - Color the box should be drawn in.
  */
  Block(const Vector2 &coords = { -1, -1 }, const Color &color = BLANK) {
    this->coords = coords;
    this->color = color;
  }
  
  /**
   If the block will be in bounds, translates it 1 space left.
   @return: true if block was moved, false otherwise.
   */
  bool left() {
    if (this->coords.x * BLOCK_SIZE - BLOCK_SIZE >= 0) {
      this->coords.x -= 1;
      return true;
    }
    
    return false;
  }
  
  /**
   If the block will be in bounds, translates it 1 space right.
   @return: true if the block was moved; false otherwise.
  */
  bool right() {
    if (this->coords.x * BLOCK_SIZE < WINDOW_WIDTH - BLOCK_SIZE) {
      this->coords.x += 1;
      return true;
    }
    
    return false;
  }
  
  /**
   If the block will be in bounds, translates it 1 space down.
   @return: true if the block was moved; false otherwise.
  */
  bool down() {
    if (this->coords.y * BLOCK_SIZE < WINDOW_HEIGHT - BLOCK_SIZE) {
      this->coords.y += 1;
      return true;
    }
    
    return false;
  }
  
  /**
   If the block will be in bounds, rotate it clockwise around another block.
   @return: true if the block was rotated; false otherwise.
  */
  bool rotateCW(const Block &b) {
    // Set temp vector to use in calculation
    Vector2 temp = this->coords;
    
    // Translate the rotated point so that center is the 'origin'
    temp.x -= b.coords.x;
    temp.y -= b.coords.y;
    
    // Apply the rotation rule
    std::swap(temp.x, temp.y);
    temp.y *= -1;
    
    // Translate it back
    temp.x += b.coords.x;
    temp.y += b.coords.y;
    
    // If this point is OOB, return false
    if (temp.x < 0 || temp.x > WINDOW_WIDTH - BLOCK_SIZE ||
        temp.y < 0 || temp.y > WINDOW_HEIGHT - BLOCK_SIZE)
      return false;
    // Otherwise, update and return true
    this->coords = temp;
    return true;
  }
  
  /**
   If the block will be in bounds, rotate it counter-clockwise around another block.
   @return: true if the block was rotated; false otherwise.
  */
  bool rotateCCW(const Block &b) {
    // Set temp vector to use in calculation
    Vector2 temp = this->coords;
    
    // Translate the rotated point so that center is the 'origin'
    temp.x -= b.coords.x;
    temp.y -= b.coords.y;
    
    // Apply the rotation rule
    std::swap(temp.x, temp.y);
    temp.x *= -1;
    
    // Translate it back
    temp.x += b.coords.x;
    temp.y += b.coords.y;
    
    // If this point is OOB, return false
    if (temp.x < 0 || temp.x > WINDOW_WIDTH - BLOCK_SIZE ||
        temp.y < 0 || temp.y > WINDOW_HEIGHT - BLOCK_SIZE)
      return false;
    // Otherwise, update and return true
    this->coords = temp;
    return true;
  }
  
  // Draws the block
  void draw() const {
    DrawRectangle(this->coords.x * BLOCK_SIZE, this->coords.y * BLOCK_SIZE,
                  BLOCK_SIZE, BLOCK_SIZE, this->color);
  }
};


#endif /* Block_h */
