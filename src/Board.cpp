//
//  Board.cpp
//  Tetris
//
//  Created by Andy Mina on 5/4/21.
//

#include "Board.hpp"

// --- BEGIN PRIVATE ---

/**
 Locks the active piece onto the board and generates a new one.
*/
void Board::lockPiece() {
  // Lock the active piece
  for (Block &b : this->active->getBlocks()) {
    // Grab the coords of the current block
    const Vector2 &coords = b.getCoords();
    // Grab the target block in the board
    Block &target = this->board[coords.y][coords.x];
    // Update the coords of the target block
    target.setCoords(coords);
    target.setColor(b.getColor());
    
    // Clear the row of new block if necessary
    this->checkRow(coords.y);
  }
}

/**
 Sets a new random piece as the active piece and deletes the old one.
*/
void Board::newPiece() {
  // Delete active
  delete this->active;
  // Get new piece
  this->active = new Piece(this->board, PIECE_TYPE(rng(generator)));
}

/**
 If the given row is filled, it will be cleared.
 @returns - True if the row was cleared; false otherwise
*/
bool Board::checkRow(const int &row_index) {
  // Get the row
  vector<Block> &row = this->board[row_index];
  
  // Loop through the row
  for (Block &b : row) {
    // Get the coords of this block
    const Vector2 &coords = b.getCoords();
    
    // If this block is not empty
    if (coords.x == -1 || coords.y == -1)
      return false;
  }
  
  // Clear the row
  this->clearRow(row_index);
  // Update the board
  this->updateBoard();
  return true;
}

/**
 Clears the given row.
*/
void Board::clearRow(const int &row_index) {
  // Delete this row from the board
  this->board.erase(this->board.begin() + row_index);
  // Create a new empty row and insert at top
  this->board.insert(this->board.begin(), vector<Block>(this->cols));
}

/**
 Updates all of the blocks in the board to render at the correct position
 starting from the bottom.
*/
void Board::updateBoard() {
  // Iterate backwards through the vector (bottom up)
  for (int i = this->board.size() - 1; i >= 0; i--) {
    // Iterate forwards through each row (left to right)
    for (int j = 0; j < this->board[i].size(); j++) {
      // Get the coords of this block
      const Vector2 &coords = this->board[i][j].getCoords();
      // Check if the block needs to be updated
      if (coords.x != -1 && coords.y != - 1) {
        // Create new coords
        Vector2 target;
        target.x = j;
        target.y = i;
        // Set the new coords
        this->board[i][j].setCoords(target);
      }
    }
  }
}

/**
 Draws all of the blocks on the screen.
*/
void Board::drawBlocks() {
  // Draw all of the blocks
  for (int i = 0; i < this->rows; i++)
    for (int j = 0; j < this->cols; j++)
      if (this->board[i][j].getCoords().x != -1) // dont draw the empty blocks
        this->board[i][j].draw();
}

/**
 Draws the grid overlay.
*/
void Board::drawGrid() {
  // Draw rows
  for (int i = 0; i < this->rows; i++)
    DrawLine(0, i * BLOCK_SIZE, WINDOW_WIDTH, i * BLOCK_SIZE, WHITE);
  
  // Draw columns
  for (int i = 0; i < this->cols; i++)
    DrawLine(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, WINDOW_HEIGHT, WHITE);
}

// --- END PRIVATE ---

// --- BEGIN PUBLIC ---

/**
 Public constructor that creates a board.
 
 @param rows - The number of rows on the board. Defaults to Global::ROWS
 @param cols - The number of cols on the board. Defaults to Global::COLS
 */
Board::Board(const int &rows, const int &cols, const int &fall_speed) {
  // Set rows and cols
  this->rows = rows;
  this->cols = cols;
  // Create a board
  vector<vector<Block>> board(this->rows, vector<Block>(this->cols));
  // Move the existing board into the data member
  this->board = std::move(board);
  
  // Seed the generator
  this->generator = default_random_engine((int)time(nullptr));
  // Set up RNG
  this->rng = uniform_int_distribution<int>(0, 6);
  // Create a new piece of random type
  this->active = new Piece(this->board, PIECE_TYPE(rng(generator)));
  
  // Set fall speed
  this->fall_speed = fall_speed;
  // Set failed fall counter
  this->failed_falls = 0;
}

/**
 Allows the piece to be updated by user input. User can use LEFT to move left,
 RIGHT to move right, DOWN to move down, Z to rotate counter-clockwise, and
 X or UP to rotate clockwise.
 */
void Board::update() {
  // Update the active piece
  this->active->update();
}

/**
 Increases the fall speed by 1 block per second (bps).
*/
void Board::fall(int &frames) {
  // Calculate if the block shouldve fallen already
  if (frames >= FPS / this->fall_speed) {
    // Reset frame counter
    frames = 0;
    
    // Drop the piece and increment failed falls if needed
    if (!this->active->fall())
      this->failed_falls++;
    
    // Determine if the piece failed to fall more than 3 times
    if (this->failed_falls > 3) {
      // Lock the piece
      this->lockPiece();
      // Set a new piece
      this->newPiece();
      // Reset counter
      this->failed_falls = 0;
    }
  }
}

/**
 Draws the board, grid, and active piece.
*/
void Board::draw() {
  this->drawBlocks();
  this->active->draw();
  this->drawGrid();
}

// --- END PUBLIC ---
