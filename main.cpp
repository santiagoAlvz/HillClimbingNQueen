/* 
 * Santiago Álvarez Valdivia
 * December 2th, 2022
 */

#include <iostream>
#include "board.h"

using std::cin;
using std::cout;
using std::endl;

/* NOTE:
 * The complexity of this algorithm uses the so called d, which is the number of times that
 * a new neighbor was selected, a process that happens until the minimum number of collisions
 * is achieved. As Hill Climbing depends on randomness, the number of changes it takes is unknown,
 * and varies with each execution.
 *
 * Worst case, it would have to traverse all N^N combinations, though this is, at least, extremely
 * unlikely, even if possible. Best case scenario, it finds the solution on first try.
 *
 * As a bit of extra information, the exact number of boards used is printed with each execution.
 */

//Solves the N-Queen Problem using Hill Climbing: O(dN²)
int main(){

  int n;
  cout<<"Enter board size (N):"<<endl;
  cin>>n;

  if(n < 4){
    cout<<"There isn't a N-Queen solution for a board that size"<<endl;
    return 1;
  }

  Board mainBoard(n); //O(n)
  Board neighborBoard(n);//O(n)

  //Makes a random placement of queens as a starting board
  neighborBoard.makeRandom(); //O(n)

  bool found = false;
  int cont = 0;

  do{ //O(dN⁴)
    mainBoard = neighborBoard;

    //Obtains the best neighboring board
    neighborBoard = mainBoard.bestNeighbor(); //O(n⁴)

    if(mainBoard == neighborBoard){
      /* If the new board is the same as the last one, we've already achieved a minimum
      number of collisions. Exit the loop*/
      found = true;
      
    } else if(mainBoard.getCollisions() == neighborBoard.getCollisions()){ //O(n²)
      /* If the boards are different, but the collision number hasn't improved, we've reached a plateu
      We'll switch to a random neighbor to escape it*/
      neighborBoard.convertToRandomNeighbor(); //O((1))
    }
    cont++;
    
  } while (!found);

  cout<<mainBoard<<endl;//O(n²)
  cout<<"Amount of queen pairs that attack each other: "<<mainBoard.getCollisions()<<endl;
  cout<<"Steps taken: "<<cont<<endl;
  
  return 0;
}
