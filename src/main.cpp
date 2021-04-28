//
//  main.cpp
//  hello-world
//
//  Created by Andy Mina on 4/27/21.
//

#include <iostream>
#include <string>
#include "raylib.h"
#include "Piece.h"

// Define global vars
#define ROWS 20
#define COLUMNS 10
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 800
#define FPS 60
#define BOX_SIZE WINDOW_WIDTH / COLUMNS

using std::cout; using std::endl;
using std::to_string;

void DrawGrid() {
  // Draw rows
  for (int i = 0; i < ROWS; i++)
    DrawLine(0, i * BOX_SIZE, WINDOW_WIDTH, i * BOX_SIZE, WHITE);
  
  // Draw columns
  for (int i = 0; i < COLUMNS; i++)
    DrawLine(i * BOX_SIZE, 0, i * BOX_SIZE, WINDOW_HEIGHT, WHITE);
}

int main() {
  // Create the window
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris");
  // Set FPS
  SetTargetFPS(FPS);
  // Set frame variable
  int frames = 0;
  // Create a piece
  Piece active(I_BLOCK, 1);
  
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
    // Draw the Tetris grid on the top layer.
    DrawGrid();
    
    EndDrawing();
    // --- END DRAW PHASE ---
  }
}
