//
//  Block.hpp
//  Tetris
//
//  Created by Andy Mina on 5/3/21.
//

#ifndef Block_hpp
#define Block_hpp

#include "raylib.h"
#include <algorithm>
#include <vector>
#include <iostream>

using std::vector;
using std::cout; using std::endl;

class Block {
private:
  // Coords of the box
  Vector2 coords;
  // Color of the box
  Color color;
  
public:
  // Public constructor
  Block(const Vector2 &coords = { -1, -1 }, const Color &color = BLANK);
  
  // Copy assignment
  Block& operator=(const Block &rhs);
  
  // Translations
  bool left(const vector<vector<Block>> &board);
  bool right(const vector<vector<Block>> &board);
  bool down(const vector<vector<Block>> &board);
  
  // Rotations
  bool rotateCW(const Block &b, const vector<vector<Block>> &board);
  bool rotateCCW(const Block &b, const vector<vector<Block>> &board);
  
  // Getters
  const Vector2& getCoords() const;
  const Color& getColor() const;
  
  // Setters
  void setCoords(const Vector2 &coords);
  void setColor(const Color &color);
  
  // Draw
  void draw() const;
};

#endif /* Block_hpp */
