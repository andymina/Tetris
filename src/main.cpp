//
//  main.cpp
//  hello-world
//
//  Created by Andy Mina on 4/27/21.
//

#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "Global.hpp"
#include "Board.hpp"

using std::cout; using std::endl;
using std::to_string;

int main() {
  // Create the window
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris");
  // Set FPS
  SetTargetFPS(FPS);
  // Create the board
  Board board(ROWS, COLS);
  // Create frames counter
  int frames = 0;

  // Game loop
  while (!WindowShouldClose()) {
    // --- BEGIN UPDATE PHASE
    
    // Increase frame counter
    frames++;
    // Drop the active if we need to
    board.fall(frames);
    
    // Take user input
    board.update();
    
    // --- END UPDATE PHASE
    
    // --- BEGIN DRAW PHASE ---
    BeginDrawing();
    
    // Clear the canvas
    ClearBackground(BLACK);
    // Draw everything on the board
    board.draw();
    
    EndDrawing();
    // --- END DRAW PHASE ---
  }
}
