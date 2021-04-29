//
//  main.cpp
//  hello-world
//
//  Created by Andy Mina on 4/27/21.
//

#include <iostream>
#include <string>
#include "raylib.h"
#include "Global.h"
#include "Piece.h"
#include "Board.h"

using std::cout; using std::endl;
using std::to_string;

int main() {
  // Create the window
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris");
  // Set FPS
  SetTargetFPS(FPS);
  // Set frame variable
  int frames = 0;
  // Create the board
  Board board(ROWS, COLS);
  // Create a piece
  Piece active(O_BLOCK, 1);
  
  // Game loop
  while (!WindowShouldClose()) {
    // --- BEGIN UPDATE PHASE
    
    // Increase frame counter
    frames++;
    // If enough frames have passed, the block should fall
    active.fall(frames);
    // Take user input for the block
    active.update();
    
    // --- END UPDATE PHASE
    
    // --- BEGIN DRAW PHASE ---
    BeginDrawing();
    
    // Clear the canvas
    ClearBackground(BLACK);
    // Draw the active piece
    active.draw();
    // Draw the set blocks
    board.drawBlocks();
    // Draw the Tetris grid on the top layer.
    board.drawGrid();
    
    EndDrawing();
    // --- END DRAW PHASE ---
  }
}
