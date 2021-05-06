//
//  Block.cpp
//  Tetris
//
//  Created by Andy Mina on 5/3/21.
//

#include "Global.hpp"
#include "Block.hpp"

// --- BEGIN PRIVATE ---

/**
 If the block will be in bounds and the target space is empty,
 translates it 1 space left.
 @return: true if block was moved, false otherwise.
 */
bool Block::left(const vector<vector<Block>> &board) {
  // Get target block
  const Vector2 &target = board[this->coords.y][this->coords.x - 1].getCoords();
  // Move if will be in bounds and target is empty
  if (this->coords.x - 1 >= 0 && target.x == -1) {
    this->coords.x -= 1;
    return true;
  }
  
  return false;
}

/**
 If the block will be in bounds and the target space is empty,
 translates it 1 space right.
 @return: true if the block was moved; false otherwise.
*/
bool Block::right(const vector<vector<Block>> &board) {
  // Get target block
  const Vector2 &target = board[this->coords.y][this->coords.x + 1].getCoords();
  // Move if will be in bounds and target is empty
  if (this->coords.x + 1 <= COLS - 1 && target.x == -1) {
    this->coords.x += 1;
    return true;
  }
  
  return false;
}

/**
 If the block will be in bounds and the target space is empty,
 translates it 1 space down.
 @return: true if the block was moved; false otherwise.
*/
bool Block::down(const vector<vector<Block>> &board) {
  // Get target block
  const Vector2 &target = board[this->coords.y + 1][this->coords.x].getCoords();
  // Move if will be in bounds and target is empty
  if (this->coords.y + 1 <= ROWS - 1 && target.y == -1) {
    this->coords.y += 1;
    return true;
  }
  
  return false;
}

/**
 If the block will be in bounds and the target space is empty,
 rotate this block clockwise around another block.
 @return: true if the block was rotated; false otherwise.
*/
bool Block::rotateCW(const Block &b, const vector<vector<Block>> &board) {
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
  if (temp.x < 0 || temp.x > COLS - 1 ||
      temp.y < 0 || temp.y > ROWS - 1)
    return false;
  
  // Get target space
  const Vector2 &target = board[temp.y][temp.y].getCoords();
  // If target space isn't empty, return false
  if (target.x != -1 && target.y != -1)
    return false;
  // Otherwise, update and return true
  this->coords = temp;
  return true;
}

/**
 If the block will be in bounds and the target space is empty,
 rotate this block counter-clockwise around another block.
 @return: true if the block was rotated; false otherwise.
*/
bool Block::rotateCCW(const Block &b, const vector<vector<Block>> &board) {
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
  if (temp.x < 0 || temp.x > COLS - 1 ||
      temp.y < 0 || temp.y > ROWS - 1)
    return false;
  
  // Get target space
  const Vector2 &target = board[temp.y][temp.x].getCoords();
  if (target.x != -1 && target.y != - 1)
    return false;
  
  // Otherwise, update and return true
  this->coords = temp;
  return true;
}

// --- END PRIVATE ---

// --- BEGIN PUBLIC ---
/**
 Public constructor.
 
 @param coords - Coords of the top-left corner of the block.
 @param color - Color the box should be drawn in.
*/
Block::Block(const Vector2 &coords, const Color &color) {
  // Set coords and color
  this->coords = coords;
  this->color = color;
}

// Copy assignment
Block& Block::operator=(const Block &rhs) {
  if (this != &rhs) {
    this->coords = rhs.coords;
    this->color = rhs.color;
  }
  
  return *this;
}

// Gets the coords
const Vector2& Block::getCoords() const {
  return this->coords;
}

// Gets the color
const Color& Block::getColor() const {
  return this->color;
}

// Sets the coords
void Block::setCoords(const Vector2 &coords) {
  this->coords = coords;
}

// Sets the color
void Block::setColor(const Color &color) {
  this->color = color;
}

// Draws the block
void Block::draw() const {
  DrawRectangle(this->coords.x * BLOCK_SIZE, this->coords.y * BLOCK_SIZE,
                BLOCK_SIZE, BLOCK_SIZE, this->color);
}

// --- END PUBLIC ---
