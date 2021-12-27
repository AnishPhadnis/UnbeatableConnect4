#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include "Board.h"
#include <math.h>
#include <limits>
using namespace std;

class Solver {
    public:
        Solver();

        int getNumExploredPos() const;

        // int negamax(Board& b, int alpha, int beta);
        pair<int, int> negamax(Board& b, int alpha, int beta, int depth);
        int solve(Board& b);


    private:
        static const int DEPTH;
        
        int numExploredPos;
        int explorePosOrder[Board::WIDTH];


};



#endif
