#include "Solver.h"

const int Solver::DEPTH = 5;

Solver::Solver(): numExploredPos(0) {
    int counter = 0;
    int center = floor(Board::WIDTH / 2);

    explorePosOrder[counter++] = center;

    for(int i = 1; i < floor(Board::WIDTH / 2) + 1; ++i){
        explorePosOrder[counter++] = center - i;

        if((center + i) < Board::WIDTH){ // Protection against last iteration of loop on even #s
            explorePosOrder[counter++] = center + i;
        }

    }

}

int Solver::getNumExploredPos() const { return numExploredPos; }

//int1 = score, int2 = move
pair<int, int> Solver::negamax(Board& b, int alpha, int beta, int depth) {
    if(depth == 0) return make_pair(numeric_limits<int>::min(), -1);

    numExploredPos++; // Exploring position

    // Draw game = 0 score --> Should never get here
    if(b.getNumMoves() == (Board::WIDTH * Board::HEIGHT)) return make_pair(0, -1); // ** Potential Problem with best move being set to -1

    for(int i = 0; i < Board::WIDTH; ++i){
        if(b.canPlay(explorePosOrder[i]) && b.isWinningMove(explorePosOrder[i])){
            // The fewer moves you can win in, the higher the score
            return make_pair((Board::WIDTH * Board::HEIGHT + 1 - b.getNumMoves()) / 2, explorePosOrder[i]);
        }
    }

    //int bestScore = -(Board::WIDTH * Board::HEIGHT);
    int bestScore = (Board::WIDTH * Board::HEIGHT + 1 - b.getNumMoves()) / 2;
    //int bestScore = (Board::WIDTH * Board::HEIGHT + 1 - b.getNumMoves()) / 2;
    //int score;
    pair<int, int> score = make_pair(numeric_limits<int>::min(), -1);
    int bestMove = explorePosOrder[0];

    if(beta > bestScore){
        beta = bestScore; // More accurate estimate for upperbound
        if(alpha >= beta) // Prune search tree
            return make_pair(beta, -1);
            // When alpha greater than beta, this symbolizes a really good move, such a good move that
            // we don't have to search it further because the minimizing player would obviously never do it
            // We return the max possible score which gets translated into the worst possible score for the
            // other player when we check every position in the next for loop --> score = -1 * negamax(...)
    }

    for(int i = 0; i < Board::WIDTH; ++i){
        if(b.canPlay(explorePosOrder[i])){
            Board b2(b);
            b2.play(explorePosOrder[i]); // Create new board and play this position

            // Our score will be negative of other player's score
            // Their win is our loss
            score = (negamax(b2, -beta, -alpha, depth - 1));
            score.first = -score.first;
            // Our best possible score (alpha) is their worst possible score
            // Negative because opposite scores

            //if(score > bestScore) bestScore = score;
            // Switched ifs ***
            if(score.first > alpha){ // Maximize our score
                alpha = score.first;
                bestMove = score.second;

            }
            if(alpha >= beta) return score; // Another way of saying if alpha >= beta

        }
    }


    return make_pair(alpha, bestMove);
}

int Solver::solve(Board& b){
    numExploredPos = 0;
    int maxScore = numeric_limits<int>::min();
    //int depth = 5;

    // <score, move>
    pair<int, int> score = negamax(b, numeric_limits<int>::min(), numeric_limits<int>::max(), DEPTH);

    //cout << "Play: " << score.second << " with score of " << score.first << endl;

    // If we cannot find any move with a better score with a limited depth approach
    // We can look for the first move we can play in explorePosOrder[]
    if(!b.canPlay(score.second)){
        for(int i = 0; i < Board::WIDTH; ++i){
            if(b.canPlay(explorePosOrder[i])){
                return explorePosOrder[i];
            }
        }
    }

    return score.second;

}


/**
int Solver::negamax(Board& b, int alpha, int beta) {
    numExploredPos++; // Exploring position

    // Draw game = 0 score
    if(b.getNumMoves() == (Board::WIDTH * Board::HEIGHT)) return 0;

    for(int i = 0; i < Board::WIDTH; ++i){
        if(b.canPlay(i) && b.isWinningMove(i)){
            // The fewer moves you can win in, the higher the score
            return (Board::WIDTH * Board::HEIGHT + 1 - b.getNumMoves()) / 2;
        }
    }

    //int bestScore = -(Board::WIDTH * Board::HEIGHT);
    int bestScore = (Board::WIDTH * Board::HEIGHT + 1 - b.getNumMoves()) / 2;
    int score;

    if(bestScore > beta){
        beta = bestScore; // More accurate estimate for upperbound
        if(alpha >= beta) // Prune search tree
            return beta;
            // When alpha greater than beta, this symbolizes a really good move, such a good move that
            // we don't have to search it further because the minimizing player would obviously never do it
            // We return the max possible score which gets translated into the worst possible score for the
            // other player when we check every position in the next for loop --> score = -1 * negamax(...)
    }

    for(int i = 0; i < Board::WIDTH; ++i){
        if(b.canPlay(i)){
            Board b2(b);
            b2.play(i); // Create new board and play this position

            // Our score will be negative of other player's score
            // Their win is our loss
            score = -(negamax(b2, -beta, -alpha));
            // Our best possible score (alpha) is their worst possible score
            // Negative because opposite scores

            //if(score > bestScore) bestScore = score;
            // Switched ifs ***
            if(score > alpha) score = alpha; // Maximize our score
            if(alpha >= beta) return score; // Another way of saying if alpha >= beta

        }
    }


    return alpha;
}

int Solver::solve(Board& b){
    numExploredPos = 0;
    int maxScore = numeric_limits<int>::min();
    int currScore;
    int move;

    for(int i = 0; i < Board::WIDTH; ++i){
        Board b2(b);
        b2.play(i);
        currScore = negamax(b2, numeric_limits<int>::min(), numeric_limits<int>::max());

        if(currScore > maxScore){
            maxScore = currScore;
            move = i;
        }
    }
    return move;
} **/
