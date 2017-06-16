#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

char board[9] = {};

void clearScreen();
void clearBoard();
bool hasWon(char);
void gameBoard(string);
int game();
char getWinner2();
char getWinner1U();
char getWinner1L();
int lBotMove(int);
int uBotMove(int);
int uBotMove3turn(int);
int uBotMove5turn(int);
int uBotMove7turn(int);
int uBotMove9turn(int);

bool twoPlayers(int, int, int, string);
bool onePlayerUnreal(int, int, int, string);
bool onePlayerLow(int, int, int, string);

int main() {
      cout <<"Greetings!\n\n";

      srand(time(0));
      string Reply = "y", qReply = "n";
      int xWins=0, oWins=0, Ties=0, gameNum = 0, gameMode, onePlayerGameMode;
      bool game;

      while (game) {
            while (qReply == "n") {
                  cout << "Choose the game mode or quit:\nOne player (type 1)\nTwo players (type 2)\nQuit (type 3)\n";
                  cin >> gameMode;
                  while (gameMode != 1 && gameMode != 2 && gameMode != 3) {
                        cout << "Choose the game mode correctly!\nOne player (type 1)\nTwo players (type 2)\nQuit (type 3)\n";
                        cin >> gameMode;
                  }
                  if (gameMode == 3) {
                        cout << "Do you really wish to quit the game? (y/n)\n";
                        cin >> qReply;
                        while (qReply != "y" && qReply != "n") {
                              cout << "Choose correctly!\nDo you really wish to quit the game? (y/n)\n";
                              cin >> gameMode;
                        }
                        if (qReply == "y")
                              return 0;
                        else
                              continue;
                  }
                  if (gameMode == 2) {
                        game = twoPlayers(xWins, oWins, Ties, Reply);
                        continue;
                  }
                  if (gameMode == 1) {
                        clearScreen();
                        cout << "What bot level would you like to play with?\nLow (type 1)\nUnreal (type 2)\nMenu (type 3)\n";
                        cin >> onePlayerGameMode;
                        while (onePlayerGameMode != 2 && onePlayerGameMode!= 1 && onePlayerGameMode!= 3) {
                              cout << "Choose correctly!\nWhat bot level would you like to play with?\nLow (type 1)\nUnreal (type 2)\nMenu (type 3)\n";
                              cin >> onePlayerGameMode;
                        }
                        if (onePlayerGameMode == 1) {
                              game = onePlayerLow(xWins, oWins, Ties, Reply);
                              continue;
                        }
                        else {
                              if (onePlayerGameMode == 2) {
                                    game = onePlayerUnreal(xWins, oWins, Ties, Reply);
                                    continue;
                              }
                              else {
                                    clearScreen();
                                    continue;
                              }
                        }
                  }
            }
      }
      return 0;
}

void clearScreen() {
      char null = 0;
      for (int i = 0; i < 100; i++) {
            cout << null << "\n";
      }
}

void clearBoard() {
    for (int i = 0; i < 9; i++) {
            board[i] = '-';
    }
}

bool hasWon(char player) {
      int wins[8][3] = {{0,1,2}, {3,4,5}, {6,7,8}, {0,3,6}, {1,4,7}, {2,5,8}, {0,4,8}, {2,4,6}};

      for (int i = 0; i < 8; i++) {
            int count = 0;
            for(int j = 0; j < 3; j++) {
                  if (board[wins[i][j]] == player)
                  count++;
            }
            if (count == 3) {
                  return true;
            }
      }
      return false;
}

void gameBoard(string symb) {
      cout << "\n";
      cout << symb << "-" << board[6] << "-|-" << board[7] << "-|-" << board[8] << "- \n";
      cout << symb << "-" << board[3] << "-|-" << board[4] << "-|-" << board[5] << "- \n";
      cout << symb << "-" << board[0] << "-|-" << board[1] << "-|-" << board[2] << "- \n";
}

int game() {
      cout << "\nMenu: \n";
      cout << "-7-|-8-|-9-\n";
      cout << "-4-|-5-|-6-\n";
      cout << "-1-|-2-|-3-\n";
      cout << "\n";
      gameBoard("");
      cout << char(0) << "\nEnter the number of position: ";

      int move;
      cin >> move;
      while(move > 9 || move < 1 || board[move-1]!= '-') {
            cout << "Enter another number of position (from 1 to 9): ";
            cin >> move;
      }
      return move;
}

char getWinner2() {
      int turn = 1;
      while(!hasWon('X') && !hasWon('0')){
            clearScreen();
            int move = game();
            clearScreen();
            if(turn%2 == 1) {
                  board[move-1] = 'X';
                  if(hasWon('X')) {
                        cout << "X, congratulations, you won!\n";
                        return 'X';
                  }
            }
            else {
                  board[move-1] = '0';
                  if (hasWon('0')) {
                        cout << "0, congratulations, you won!\n";
                        return '0';
                  }
            }
            turn++;
            if (turn == 10) {
                  cout << "Draw!\n";
                  return 'D';
            }
      }
}

char getWinner1U() {
      int Turn = 1;
      while(!hasWon('X') && !hasWon('0')){
            clearScreen();
            int move = game();
            clearScreen();
            board[move-1] = 'X';
            if (hasWon('X')) {
                  cout << "Player won!\n";
                  return 'X';
            }
            int botmove = uBotMove(Turn);
            Turn ++;
            if (Turn == 10) {
                  cout << "Draw!\n";
                  return 'D';
            }
            board[botmove-1] = '0';
            if (hasWon('0')) {
                  cout << "Bot won!\n";
                  return '0';
            }
            clearScreen();
            gameBoard("");
            Turn ++;
            if (Turn == 10) {
                  cout << "Draw!\n";
                  return 'D';
            }
      }
}

char getWinner1L() {
      int Turn = 1;
      while(!hasWon('X') && !hasWon('0')){
            clearScreen();
            int move = game();
            clearScreen();
            board[move-1] = 'X';
            if (hasWon('X')) {
                  cout << "Player won!\n";
                  return 'X';
            }
            int botmove = lBotMove(Turn);
            Turn ++;
            if (Turn == 10) {
                  cout << "Draw!\n";
                  return 'D';
            }
            board[botmove-1] = '0';
            if (hasWon('0')) {
                  cout << "Bot won!\n";
                  return '0';
            }
            clearScreen();
            gameBoard("");
            Turn ++;
            if (Turn == 10) {
                  cout << "Draw!\n";
                  return 'D';
            }
      }
}

int lBotMove (int turn_) {
      if (board[0] == '0' && board [1] == '0' && board[2] == '-')
            return 3;
      if (board[0] == '0' && board [1] == '0' && board[2] == '-')
            return 3;
      if (board[0] == '0' && board [2] == '0' && board[1] == '-')
            return 2;
      if (board[1] == '0' && board [2] == '0' && board[0] == '-')
            return 1;
      if (board[6] == '0' && board [7] == '0' && board[8] == '-')
            return 9;
      if (board[6] == '0' && board [8] == '0' && board[7] == '-')
            return 8;
      if (board[7] == '0' && board [8] == '0' && board[6] == '-')
            return 6;
      if (board[0] == '0' && board [3] == '0' && board[6] == '-')
            return 7;
      if (board[0] == '0' && board [6] == '0' && board[3] == '-')
            return 4;
      if (board[3] == '0' && board [6] == '0' && board[0] == '-')
            return 1;
      if (board[2] == '0' && board [5] == '0' && board[8] == '-')
            return 9;
      if (board[5] == '0' && board [8] == '0' && board[2] == '-')
            return 3;
      if (board[2] == '0' && board [8] == '0' && board[5] == '-')
            return 6;
      if (board[1] == '0' && board [4] == '0' && board[7] == '-')
            return 8;
      if (board[4] == '0' && board [7] == '0' && board[1] == '-')
            return 2;
      if (board[3] == '0' && board [4] == '0' && board[5] == '-')
            return 6;
      if (board[5] == '0' && board [4] == '0' && board[3] == '-')
            return 4;
      if (board[0] == '0' && board [4] == '0' && board[8] == '-')
            return 9;
      if (board[9] == '0' && board [4] == '0' && board[0] == '-')
            return 1;
      if (board[2] == '0' && board [4] == '0' && board[6] == '-')
            return 7;
      if (board[6] == '0' && board [4] == '0' && board[2] == '-')
            return 3;
      if (board[1] == '0' && board [7] == '0' && board[4] == '-')
            return 3;
      if (board[0] == '0' && board [8] == '0' && board[4] == '-')
            return 3;
      if (board[6] == '0' && board [2] == '0' && board[4] == '-')
            return 3;
      if (board[3] == '0' && board [5] == '0' && board[4] == '-')
            return 3;
      int randomPos = rand() % 9 + 1;
      while (board[randomPos - 1] != '-') {
            randomPos = rand() % 9 + 1;
      }
      return randomPos;
}

int uBotMove (int turn_) {
      if (board[4] != 'X' && turn_ == 1)
            return 5;
      if (board[4] == 'X' && turn_ == 1)
            return 1;
      if (board[0] == '0' && board [1] == '0' && board[2] == '-')
            return 3;
      if (board[0] == '0' && board [1] == '0' && board[2] == '-')
            return 3;
      if (board[0] == '0' && board [2] == '0' && board[1] == '-')
            return 2;
      if (board[1] == '0' && board [2] == '0' && board[0] == '-')
            return 1;
      if (board[6] == '0' && board [7] == '0' && board[8] == '-')
            return 9;
      if (board[6] == '0' && board [8] == '0' && board[7] == '-')
            return 8;
      if (board[7] == '0' && board [8] == '0' && board[6] == '-')
            return 6;
      if (board[0] == '0' && board [3] == '0' && board[6] == '-')
            return 7;
      if (board[0] == '0' && board [6] == '0' && board[3] == '-')
            return 4;
      if (board[3] == '0' && board [6] == '0' && board[0] == '-')
            return 1;
      if (board[2] == '0' && board [5] == '0' && board[8] == '-')
            return 9;
      if (board[5] == '0' && board [8] == '0' && board[2] == '-')
            return 3;
      if (board[2] == '0' && board [8] == '0' && board[5] == '-')
            return 6;
      if (board[1] == '0' && board [4] == '0' && board[7] == '-')
            return 8;
      if (board[4] == '0' && board [7] == '0' && board[1] == '-')
            return 2;
      if (board[3] == '0' && board [4] == '0' && board[5] == '-')
            return 6;
      if (board[5] == '0' && board [4] == '0' && board[3] == '-')
            return 4;
      if (board[0] == '0' && board [4] == '0' && board[8] == '-')
            return 9;
      if (board[9] == '0' && board [4] == '0' && board[0] == '-')
            return 1;
      if (board[2] == '0' && board [4] == '0' && board[6] == '-')
            return 7;
      if (board[6] == '0' && board [4] == '0' && board[2] == '-')
            return 3;
      if (board[0] == 'X' && board [2] == 'X' && board[1] == '-')
            return 2;
      if (board[1] == 'X' && board [2] == 'X' && board[0] == '-')
            return 1;
      if (board[6] == 'X' && board [7] == 'X' && board[8] == '-')
            return 9;
      if (board[6] == 'X' && board [8] == 'X' && board[7] == '-')
            return 8;
      if (board[7] == 'X' && board [8] == 'X' && board[6] == '-')
            return 6;
      if (board[0] == 'X' && board [3] == 'X' && board[6] == '-')
            return 7;
      if (board[0] == 'X' && board [6] == 'X' && board[3] == '-')
            return 4;
      if (board[3] == 'X' && board [6] == 'X' && board[0] == '-')
            return 1;
      if (board[2] == 'X' && board [5] == 'X' && board[8] == '-')
            return 9;
      if (board[5] == 'X' && board [8] == 'X' && board[2] == '-')
            return 3;
      if (board[2] == 'X' && board [8] == 'X' && board[5] == '-')
            return 6;
      if (turn_ == 3)
            return uBotMove3turn(turn_);
      if (turn_ == 5)
            return uBotMove5turn(turn_);
      if (turn_ == 7)
            return uBotMove7turn(turn_);
      if (turn_ == 9)
            return uBotMove9turn(turn_);
}

int uBotMove3turn(int turn) {
      if ( board[0] == 'X' && board[9-1] == '-')
            return 9;
      else {
            if ( board[1] == 'X' && board[8-1] == '-')
                  return 8;
            else {
                  if ( board[2] == 'X' && board[7-1] == '-')
                        return 7;
                  else {
                        if ( board[3] == 'X' && board[6-1] == '-')
                              return 6;
                        else {
                              if ( board[5] == 'X' && board[4-1] == '-')
                                    return 4;
                              else {
                                    if ( board[6] == 'X' && board[3-1] == '-')
                                          return 3;
                                    else {
                                          if ( board[7] == 'X' && board[2-1] == '-')
                                                return 2;
                                          else
                                                if ( board[8] == 'X' && board[7-1] == '-')
                                                      return 7;
                                    }
                              }
                        }
                  }
            }
      }
}

int uBotMove5turn(int turn) {
      if ( board[8] == 'X' && board [3] == 'X' && board[6-1] == '-')
            return 6;
      else {
            if ( board[8] == 'X' && board [3] != 'X' && board[4-1] == '-')
                  return 4;
            else {
                  if ( board[1] == 'X' && board [3] == 'X' && board[6-1] == '-')
                        return 6;
                  else {
                        if ( board[1] == 'X' && board [5] == 'X' && board[4-1] == '-')
                              return 4;
                        else {
                              if ( board[1] == 'X' && board [2] == 'X' && board[7-1] == '-')
                                    return 7;
                              else {
                                    if ( board[1] == 'X' && board [6] == 'X' && board[3-1] == '-')
                                          return 3;
                                    else {
                                          if ( board[1] == 'X' && board [8] == 'X' && board[3-1] == '-')
                                                return 3;
                                          else {
                                                if ( board[2] == 'X' && board [3] == 'X' && board[6-1] == '-')
                                                      return 6;
                                                else {
                                                      if ( board[2] == 'X' && board [3] != 'X' && board[4-1] == '-')
                                                            return 4;
                                                      else {
                                                            if ( board[3] == 'X' && board [1] == 'X' && board[8-1] == '-')
                                                                  return 8;
                                                            else {
                                                                  if ( board[3] == 'X' && board [2] == 'X' && board[7-1] == '-')
                                                                        return 7;
                                                                  else {
                                                                        if ( board[3] == 'X' && board [6] == 'X' && board[3-1] == '-')
                                                                              return 3;
                                                                        else {
                                                                              if ( board[5] == 'X' && board [6] == 'X' && board[3-1] == '-')
                                                                                    return 3;
                                                                              else {
                                                                                    if ( board[5] == 'X' && board [6] != 'X' && board[7-1] == '-')
                                                                                          return 7;
                                                                                    else {
                                                                                          if ( board[6] == 'X' && board [1] == 'X' && board[8-1] == '-')
                                                                                                return 8;
                                                                                          else {
                                                                                                if ( board[6] == 'X' && board [1] != 'X' && board[2-1] == '-')
                                                                                                      return 2;
                                                                                                else {
                                                                                                      if ( board[7] == 'X' && board [2] == 'X' && board[7-1] == '-')
                                                                                                            return 7;
                                                                                                      else {
                                                                                                            if ( board[7] == 'X' && board [2] != 'X' && board[3-1] == '-')
                                                                                                                  return 3;
                                                                                                            else {
                                                                                                                  if ( board[8] == 'X' && board [2] == 'X' && board[7-1] == '-')
                                                                                                                        return 7;
                                                                                                            }
                                                                                                      }
                                                                                                }
                                                                                          }
                                                                                    }
                                                                              }
                                                                        }
                                                                  }
                                                            }
                                                      }
                                                }
                                          }
                                    }
                              }
                        }
                  }
            }
      }
}

int uBotMove7turn(int turn) {
      if ( board[8] == 'X' && board [3] == 'X' && board[1] == 'X' && board[8-1] == '-')
            return 8;
      else {
            if ( board[8] == 'X' && board [3] == 'X' && board[2] == 'X' && board[2-1] == '-')
                  return 2;
            else {
                  if ( board[8] == 'X' && board [3] == 'X' && board[7] == 'X' && board[2-1] == '-')
                        return 2;
                  else {
                        if ( board[8] == 'X' && board [3] == 'X' && board[1] == 'X' && board[8-1] == '-')
                              return 8;
                        else {
                              if ( board[1] == 'X' && board [2] == 'X' && board[3] == 'X' && board[6-1] == '-')
                                    return 6;
                              else {
                                    if ( board[1] == 'X' && board [2] == 'X' && board[5] == 'X' && board[4-1] == '-')
                                          return 4;
                                    else {
                                          if ( board[1] == 'X' && board [3] == 'X' && board[2] == 'X' && board[7-1] == '-')
                                                return 7;
                                          else {
                                                if ( board[1] == 'X' && board [3] == 'X' && board[6] == 'X' && board[3-1] == '-')
                                                      return 3;
                                                else {
                                                      if ( board[1] == 'X' && board [3] == 'X' && board[8] == 'X' && board[3-1] == '-')
                                                            return 3;
                                                      else {
                                                            if ( board[1] == 'X' && board [5] == 'X' && board[6] == 'X' && board[3-1] == '-')
                                                                  return 3;
                                                            else {
                                                                  if ( board[1] == 'X' && board [5] == 'X' && board[6] != 'X' && board[7-1] == '-')
                                                                        return 7;
                                                                  else {
                                                                        if ( board[1] == 'X' && board [6] == 'X' && board[3] == 'X' && board[6-1] == '-')
                                                                              return 6;
                                                                        else {
                                                                              if ( board[1] == 'X' && board [8] == 'X' && board[3] == 'X' && board[6-1] == '-')
                                                                                    return 6;
                                                                              else {
                                                                                    if ( board[1] == 'X' && board [6] == 'X' && board[3] != 'X' && board[4-1] == '-')
                                                                                          return 4;
                                                                                    else {
                                                                                          if ( board[2] == 'X' && board [3] == 'X' && board[1] == 'X' && board[8-1] == '-')
                                                                                                return 8;
                                                                                          else {
                                                                                                if ( board[2] == 'X' && board [3] == 'X' && board[7] == 'X' && board[2-1] == '-')
                                                                                                      return 2;
                                                                                                else {
                                                                                                      if ( board[2] == 'X' && board [3] == 'X' && board[8] == 'X' && board[2-1] == '-')
                                                                                                            return 2;
                                                                                                      else {
                                                                                                            if ( board[3] == 'X' && board [1] == 'X' && board[2] == 'X' && board[7-1] == '-')
                                                                                                                  return 7;
                                                                                                            else {
                                                                                                                  if ( board[3] == 'X' && board [1] == 'X' && board[6] == 'X' && board[2-1] == '-')
                                                                                                                        return 2;
                                                                                                                  else {
                                                                                                                        if ( board[3] == 'X' && board [2] == 'X' && board[1] == 'X' && board[8-1] == '-')
                                                                                                                              return 8;
                                                                                                                        else {
                                                                                                                              if ( board[3] == 'X' && board [2] == 'X' && board[7] == 'X' && board[2-1] == '-')
                                                                                                                                    return 2;
                                                                                                                              else {
                                                                                                                                    if ( board[3] == 'X' && board [2] == 'X' && board[8] == 'X' && board[8-1] == '-')
                                                                                                                                          return 8;
                                                                                                                                    else {
                                                                                                                                          if ( board[3] == 'X' && board [7] == 'X' && board[2] == 'X' && board[7-1] == '-')
                                                                                                                                                return 7;
                                                                                                                                          else {
                                                                                                                                                if ( board[3] == 'X' && board [7] == 'X' && board[2] != 'X' && board[3-1] == '-')
                                                                                                                                                      return 3;
                                                                                                                                                else {
                                                                                                                                                      if ( board[3] == 'X' && board [8] == 'X' && board[1] == 'X' && board[8-1] == '-')
                                                                                                                                                            return 8;
                                                                                                                                                      else {
                                                                                                                                                            if ( board[3] == 'X' && board [8] == 'X' && board[2] == 'X' && board[2-1] == '-')
                                                                                                                                                                  return 2;
                                                                                                                                                            else {
                                                                                                                                                                  if ( board[3] == 'X' && board [8] == 'X' && board[7] == 'X' && board[2-1] == '-')
                                                                                                                                                                        return 2;
                                                                                                                                                                  else {
                                                                                                                                                                        if ( board[5] == 'X' && board [6] == 'X' && board[1] == 'X' && board[8-1] == '-')
                                                                                                                                                                              return 8;
                                                                                                                                                                        else {
                                                                                                                                                                              if ( board[5] == 'X' && board [6] == 'X' && board[1] != 'X' && board[2-1] == '-')
                                                                                                                                                                                    return 2;
                                                                                                                                                                              else {
                                                                                                                                                                                    if ( board[6] == 'X' && board [1] == 'X' && board[3] == 'X' && board[6-1] == '-')
                                                                                                                                                                                          return 6;
                                                                                                                                                                                    else {
                                                                                                                                                                                          if ( board[6] == 'X' && board [1] == 'X' && board[5] == 'X' && board[4-1] == '-')
                                                                                                                                                                                                return 4;
                                                                                                                                                                                          else {
                                                                                                                                                                                                if ( board[6] == 'X' && board [1] == 'X' && board[8] == 'X' && board[6-1] == '-')
                                                                                                                                                                                                      return 6;
                                                                                                                                                                                                else {
                                                                                                                                                                                                      if ( board[7] == 'X' && board [2] == 'X' && board[3] == 'X' && board[6-1] == '-')
                                                                                                                                                                                                            return 6;
                                                                                                                                                                                                      else {
                                                                                                                                                                                                            if ( board[7] == 'X' && board [2] == 'X' && board[5] == 'X' && board[4-1] == '-')
                                                                                                                                                                                                                  return 4;
                                                                                                                                                                                                            else {
                                                                                                                                                                                                                  if ( board[7] == 'X' && board [2] == 'X' && board[8] == 'X' && board[6-1] == '-')
                                                                                                                                                                                                                        return 6;
                                                                                                                                                                                                                  else {
                                                                                                                                                                                                                        if ( board[8] == 'X' && board [3] == 'X' && board[1] == 'X' && board[8-1] == '-')
                                                                                                                                                                                                                              return 8;
                                                                                                                                                                                                                        else {
                                                                                                                                                                                                                              if ( board[8] == 'X' && board [3] == 'X' && board[7] == 'X' && board[2-1] == '-')
                                                                                                                                                                                                                                    return 2;
                                                                                                                                                                                                                              else {
                                                                                                                                                                                                                                    if ( board[8] == 'X' && board [3] == 'X' && board[2] == 'X' && board[8-1] == '-')
                                                                                                                                                                                                                                          return 8;
                                                                                                                                                                                                                                    else {
                                                                                                                                                                                                                                          if ( board[1] == 'X' && board [8] == 'X' && board[2] == 'X' && board[7-1] == '-')
                                                                                                                                                                                                                                                return 7;
                                                                                                                                                                                                                                          else {
                                                                                                                                                                                                                                                if ( board[1] == 'X' && board [8] == 'X' && board[5] == 'X' && board[7-1] == '-')
                                                                                                                                                                                                                                                      return 7;
                                                                                                                                                                                                                                          }
                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                              }
                                                                                                                                                                                                                        }
                                                                                                                                                                                                                  }
                                                                                                                                                                                                            }
                                                                                                                                                                                                      }
                                                                                                                                                                                                }
                                                                                                                                                                                          }
                                                                                                                                                                                    }
                                                                                                                                                                              }
                                                                                                                                                                        }
                                                                                                                                                                  }
                                                                                                                                                            }
                                                                                                                                                      }
                                                                                                                                                }
                                                                                                                                          }
                                                                                                                                    }
                                                                                                                              }
                                                                                                                        }
                                                                                                                  }
                                                                                                            }
                                                                                                      }
                                                                                                }
                                                                                          }
                                                                                    }
                                                                              }
                                                                        }
                                                                  }
                                                            }
                                                      }
                                                }
                                          }
                                    }
                              }
                        }
                  }
            }
      }
}

int uBotMove9turn(int turn) {
      if (board[0] != 'X' && board[1-1] == '-')
            return 1;
      else {
            if (board[1] != 'X' && board[2-1] == '-')
                  return 2;
            else {
                  if (board[2] != 'X' && board[3-1] == '-')
                        return 3;
                  else {
                        if (board[3] != 'X' && board[4-1] == '-')
                              return 4;
                        else {
                              if (board[5] != 'X' && board[6-1] == '-')
                                    return 6;
                              else {
                                    if (board[6] != 'X' && board[7-1] == '-')
                                          return 7;
                                    else {
                                          if (board[7] != 'X' && board[8-1] == '-')
                                                return 8;
                                          else {
                                                if (board[8] != 'X' && board[9-1] == '-')
                                                      return 9;
                                          }
                                    }
                              }
                        }
                  }
            }
      }
}

bool twoPlayers(int x_wins, int o_wins,  int ties, string reply) {
      while (reply == "y") {
            clearBoard();
            char winner = getWinner2();
            gameBoard("\t  ");

            switch (winner) {
            case 'X':
                  x_wins++;
                  break;
            case '0':
                  o_wins++;
                  break;
            case 'D':
                  ties++;
                  break;
            }

            cout << "\n\t*Winer statistic*\nPlayer X: " << x_wins << ". Player 0: " << o_wins << ". Ties: " << ties << "\n\n";
            cout << "\nWould you like to play again? (y/n): ";
            cin  >> reply;
            while (reply != "y" && reply !="n") {
                  cout << "Please, enter a valid reply (y/n):";
                  cin  >> reply;
            }
            clearScreen();
      }
      return true;
}

bool onePlayerUnreal(int x_wins, int o_wins,  int ties, string reply) {
      while (reply == "y") {
            clearBoard();
            char winner = getWinner1U();
            gameBoard("\t  ");

            switch (winner) {
            case 'X':
                  x_wins++;
                  break;
            case '0':
                  o_wins++;
                  break;
            case 'D':
                  ties++;
                  break;
            }

            cout << "\n\t*Winer statistic*\nPlayer (X): " << x_wins << ". Bot (0): " << o_wins << ". Ties: " << ties << "\n\n";
            cout << "\nWould you like to play again? (y/n): ";
            cin  >> reply;
            while (reply != "y" && reply !="n") {
                  cout << "\nPlease, enter a valid reply (y/n):";
                  cin  >> reply;
            }
            clearScreen();
      }
      return true;
}

bool onePlayerLow(int x_wins, int o_wins,  int ties, string reply) {
      while (reply == "y") {
            clearBoard();
            char winner = getWinner1L();
            gameBoard("\t  ");

            switch (winner) {
            case 'X':
                  x_wins++;
                  break;
            case '0':
                  o_wins++;
                  break;
            case 'D':
                  ties++;
                  break;
            }

            cout << "\n\t*Winer statistic*\nPlayer (X): " << x_wins << ". Bot (0): " << o_wins << ". Ties: " << ties << "\n\n";
            cout << "\nWould you like to play again? (y/n): ";
            cin  >> reply;
            while (reply != "y" && reply !="n") {
                  cout << "\nPlease, enter a valid reply (y/n):";
                  cin  >> reply;
            }
            clearScreen();
      }
      return true;
}
