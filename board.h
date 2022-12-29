#ifndef BOARD_H
#define BOARD_H

#include <vector>

using std::vector;
using std::ostream;

class Board{
  private:
    int n;
    vector<int> state;
  public:
    Board(int);
    void makeRandom();
    bool operator==(Board);
    void operator=(Board);
    Board bestNeighbor();
    int getCollisions();
    void convertToRandomNeighbor();

  //Prints the board, as a matrix: O(n²)
  friend ostream &operator<<(ostream &output, const Board& b){
    for(int i = 0; i < b.n; i++){
      for(int j = 0; j < b.n; j++){
        if(b.state[i] == j){
          output<<"1 ";
        } else {
          output<<"0 ";
        }
      }
      output<<std::endl;
    }
    return output;
  }

};

//Sets the size of the board: O(1)
Board::Board(int n){
  this->n = n;
  state.resize(n);
}

//Puts N-Queens on random columns, one on each row: O(n)
void Board::makeRandom(){
  srand(time(0));
  for(int i = 0; i < n; i++){ //O(n)
    state[i] = rand() % n;
  }
}

//Verifies if two boards have the queens on the same positions: O(n)
bool Board::operator==(Board b){
  for(int i = 0; i < n; i++){
    if(b.state[i] != this->state[i]){
      return false;
    }
  }

  return true;
}

//Assigns the values of a board inside of another one: O(1)
void Board::operator=(Board b){
  this->n = b.n;
  this->state = b.state;
}

//Obtains the best neighbor of the current state: O()
Board Board::bestNeighbor(){ //O(n⁴)
  
  Board opBoard = *this;
  int opCollisions = this->getCollisions();
  int tempCollisions;

  Board neighborBoard = *this;

  for (int i = 0; i < n; i++) { //O(n⁴)
    for (int j = 0; j < n; j++) { //O(n³)

      if(j != state[i]){
        neighborBoard.state[i] = j;
        tempCollisions = neighborBoard.getCollisions(); //O(n²)

        if(tempCollisions <= opCollisions){
          opCollisions = tempCollisions;
          opBoard = neighborBoard;
        }

        neighborBoard.state[i] = this->state[i];
      }
    }
  }

  return opBoard;
}

//Gets the amount of Queen Pairs that are able to attack each other: O(n²)
int Board::getCollisions(){
  int collisions = 0;
  int col, row;

  //For each row, get its queen
  for(int i = 0; i < n; i++){ //O(n²)
    row = i;
    col = state[i];

    //And check for collisions on higher rows
    //Only higher ones are checked to avoid duplicates, i.e. (0-2 and 2-0)
    for(int j = i + 1; j < n; j++){
      
      if (col == state[j]){ //O(1)
        collisions++;
      }else if(j + state[j] == row + col){
        collisions++;
      }else if(j - state[j] == row - col){
        collisions++;
      }
    }
  }

  return collisions;
}

//Moves a random queen to a random column: O(1)
void Board::convertToRandomNeighbor(){
  this->state[rand() % n] = rand() % n;
}

#endif