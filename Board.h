#ifndef BOARD_H
#define BOARD_H

using namespace std;
#include "string.h"
#include <iostream>

class Board{
    public:
        Board();
        ~Board();

        int getNumMoves() const;

        bool checkRow(int row) const;
        bool checkColumn(int col) const;
        bool isValidPos(int col, int row) const;
        int getCurrPlayer() const;
        
        // add const for win checkers
        bool isVerticalWin(int col, int currPlayer) const;
        bool isHorizontalWin(int col, int currPlayer) const;
        bool isDiagonalWin(int col, int currPlayer) const;
        bool isDraw() const;

        bool isWinningMove(int col) const;
        void printWinner() const;

        bool canPlay(int col) const;
        void play(int col);

        void print() const;

        static const int WIDTH = 7;
        static const int HEIGHT = 6;

    private:
        static const string EMPTY_SPOT_CHAR;
        static const string PLAYER1_CHAR;
        static const string PLAYER2_CHAR;

        int board[WIDTH][HEIGHT];
        int numPosFilled[WIDTH];
        
        int numMoves;


};

#endif