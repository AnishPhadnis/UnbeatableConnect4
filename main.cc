#include "Board.h"
#include "Solver.h"
#include <iostream>

// Make shell script to simulate various cases with program
// Inputs various p1 winning scenarios, p2 winning, etc
// Bot does not block player's wins, just optimizes for its own win

void getInput(Board& b, int& col);

int sample[7][6] = {
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0}
};

int main(){
    Board b;
    Solver solver;
    int input;

    bool isWinner = false;

    //b.setBoard(&sample);

    do {
        b.print();

        if(b.getCurrPlayer() == 1){
            getInput(b, input);
        } else {
            input = solver.solve(b); // Add args to main() to get num players
            cout << "Solved: " << input << endl;
            //getInput(b, input);
        }

        isWinner = b.isWinningMove(input);

        //cout << isWinner ? "win" : "nothin";

        /**if(b.isWinningMove(input)){
            b.play(input);
            break;
        }  **/

        b.play(input);

    } while (!b.isDraw() && !isWinner);


    b.print();
    b.printWinner();

    return 0;
}

void getInput(Board& b, int& col) {
    col = -1;

    while(!b.canPlay(col)){
        cout << "Your play? ";
        cin >> col;
    }

}
