/**********************************************************************************************
 * TicTacToe - WS2812 Version 1.0
 * by Christoph Khouri <christoph.khouri@gmail.com>
 *
 * Licensed under the MIT License
 **********************************************************************************************/

/*
 * Board logicaly set up as:
 * 1 2 3
 * 4 5 6
 * 7 8 9
 * 
 * Board technically set up as:
 * 8 3 2
 * 7 4 1
 * 6 5 0
 * 
 * 8 ways to win
 * _#1__   _#2__   _#3__   _#4__
 * 1 2 3   1 . .   1 . .   . 2 .
 * . . .   . 5 .   4 . .   . 5 .
 * . . .   . . 9   7 . .   . 8 .
 * 
 * _#5__   _#6__   _#7__   _#8__
 * . . 3   . . 3   . . .   . . .
 * . 5 .   . . 6   4 5 6   . . .
 * 7 . .   . . 9   . . .   7 8 9
 *  
*/
 
#include <Adafruit_NeoPixel.h>
#define LED_PIN   D4
#define LED_COUNT 9
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Define possible colors on the board
uint32_t boardColor[] = {
  strip.Color(  0,   0,   0), // [0] is black (off)
  strip.Color(255,   0,   0), // [1] is red for "X"
  strip.Color(  0,   0, 255), // [2] is blue for "O"
  strip.Color(  0, 255,   0)  // [3] is green for winning color
};

#define BOARD_SIZE 9
#define WINNING_FLASHES 7

int X = 1;
int O = 2;
int winner = 0;     // Placeholder for winner
int turn = X;       // X goes first
int totalMoves = 0; // Number of moves

// Array to store state of board
int board[9];       // 0 - 8 Values: 0=[No move yet], 1=X, 2=O

// Map Logical board to numbering of NeoPixels
int boardMap[] = {0,8,3,2,7,4,1,6,5,0};
int winningStrategy[][3] = {
  {0,0,0}, // Tie game
  {1,2,3},
  {1,5,9},
  {1,4,7},
  {2,5,8},
  {3,5,7},
  {3,6,9},
  {4,5,6},
  {7,8,9}
};

void setup() {
  
  strip.begin();           // INITIALIZE NeoPixel strip object
  strip.show();            
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  
  Serial.begin(9600);
  delay(200);              // Quick nap
  
  startGame();             // Let the games begin
}

void colorWipe(uint32_t color, int wait) {
  
  // From Adfruit strandtest example
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Initialize the board for a new game
void startGame() {
  
  colorWipe(boardColor[1], 10); // Red
  colorWipe(boardColor[2], 10); // Blue
  colorWipe(boardColor[0], 10); // Wipe off with 'black'
  delay(500);

  Serial.println(".....................");
  Serial.println("Shall we play a game?");
  winner = 0;
  turn = 1;
  memset(board,0,sizeof(board));
  totalMoves = 0;
}

// Flash the board for a tie or winning game.
void showWinner(int strategy) {
  
  if (strategy == 0) { // Tie
    Serial.println("Tie game");
  } else {
   if (winner == 1) {
      Serial.println("X is the WINNER!");
    } else {
      Serial.println("O is the WINNER!");
    }
  }
  
  for (int i = 0; i < WINNING_FLASHES; i++) {
    if (strategy == 0) { // Flash entire board for tie game   
      for (int j = 0; j < BOARD_SIZE; j++) {
        strip.setPixelColor(j, boardColor[3]);
      }
    } else { // Just flash the winning spots
      strip.setPixelColor(boardMap[winningStrategy[strategy][0]], boardColor[3]);
      strip.setPixelColor(boardMap[winningStrategy[strategy][1]], boardColor[3]);
      strip.setPixelColor(boardMap[winningStrategy[strategy][2]], boardColor[3]);
    }
    strip.show();
    delay(350);
    
    for(int i = 0; i < BOARD_SIZE; i++) { // Reset the board to it's original layout
      strip.setPixelColor(i, boardColor[board[i]]);
    }
    strip.show();
    delay(150);
  }
}

// Validate the move against the current board
  // and check for a winner or a tie game
void makeMove(int boardPosition) {

  /*
  for(int i = 0; i < 9; i++) {
    Serial.print(board[i]);
  }
  Serial.println();
  */
  
  if (board[boardMap[boardPosition]] == turn) {
    Serial.println("You already have that spot! Go Again.");
    
    return;
    
  } else if (board[boardMap[boardPosition]] == 0) { // Empty spot - Valid move
    board[boardMap[boardPosition]] = turn;
    
    strip.setPixelColor(boardMap[boardPosition], boardColor[turn]);
    strip.show();
  
    totalMoves++;
    Serial.println((String)"Total moves:"+totalMoves);
    
    int winner = checkGame(turn);
    if (winner == -1) { // Game still in progress
      if (turn == X) {
        turn = O;
        Serial.println("O's turn");
      } else {
        turn = X;
        Serial.println("X's turn");
      }
    } else { 
      showWinner(winner);  // Flash board for winner
      startGame();  // Start a new game
    }

    return;
      
  } else {
    Serial.println("Your opponent already has that spot! Try Again.");
    
    return;
    
  }
}

// Check if someone has won the game or there is a tie.
// Return the winning strategy (0 for tie) or -1 if game is still in progress.
int checkGame(int player) {
  
  if (board[boardMap[1]] == player && board[boardMap[2]] == player && board[boardMap[3]] == player) { // 1
    winner = player;
    return 1;
  }
  if (board[boardMap[1]] == player && board[boardMap[5]] == player && board[boardMap[9]] == player) { // 2
    winner = player;
    return 2;
  }  
  if (board[boardMap[1]] == player && board[boardMap[4]] == player && board[boardMap[7]] == player) { // 3
    winner = player;
    return 3;
  }
  
  if (board[boardMap[2]] == player && board[boardMap[5]] == player && board[boardMap[8]] == player) { // 4
    winner = player;
    return 4;
  }
  
  if (board[boardMap[3]] == player && board[boardMap[5]] == player && board[boardMap[7]] == player) { // 5
    winner = player;
    return 5;
  }  
  if (board[boardMap[3]] == player && board[boardMap[6]] == player && board[boardMap[9]] == player) { // 6
    winner = player;
    return 6;
  }
  
  if (board[boardMap[4]] == player && board[boardMap[5]] == player && board[boardMap[6]] == player)  {
    winner = player;
    return 7;
  }
  if (board[boardMap[7]] == player && board[boardMap[8]] == player && board[boardMap[9]] == player)  {
    winner = player;
    return 8;
  }

  if (totalMoves == BOARD_SIZE) {  // Tie game
    return 0;
  }
  
  // No winner
  return -1;
}

void loop() {
  
  int input;
  if (Serial.available() > 0) {    // is a character available?
    input = Serial.read() - '0';   // get the character and convert to int
  
    // check if a valid number was received
    if ((input >= 1) && (input <= BOARD_SIZE)) {
      makeMove(input);
    } else if (input == 0) {
        startGame();  // Start a new game
    } else {
      Serial.println("Invalid move");
    }
  }
}
