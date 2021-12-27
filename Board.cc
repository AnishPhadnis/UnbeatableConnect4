#include "Board.h"

const string Board::EMPTY_SPOT_CHAR = "   ";
const string Board::PLAYER1_CHAR = " x ";
const string Board::PLAYER2_CHAR = " o ";

Board::Board(): numMoves(0), board{}, numPosFilled{} { }

Board::~Board() { }

bool Board::setBoard(int* b){
  // for(int i = HEIGHT-1; i >= 0; --i){
  //   for(int j = 0; j < WIDTH; ++j){
  //     board[i][j] = b[i][j];
  //   }
  // }
  //copy(&b[0][0], &b[0][0]+WIDTH*HEIGHT, &board[0][0]);
  return true;
}

int Board::getNumMoves() const{ return numMoves; }

bool Board::checkRow(int row) const{
    return (0 <= row) && (row < HEIGHT);
}

bool Board::checkColumn(int col) const {
    return (0 <= col) && (col < WIDTH);
}

bool Board::isValidPos(int col, int row) const {
    return checkColumn(col) && checkRow(row);
}

int Board::getCurrPlayer() const {
    // If an even # of moves, player 1's turn
    return 1 + (numMoves%2);
}

bool Board::canPlay(int col) const {
    if(checkColumn(col)){
        return numPosFilled[col] < HEIGHT;
    }

    return false;
}

void Board::play(int col){
    if(canPlay(col)){
        //board[col][numPosFilled[col]] = getCurrPlayer();
        //board[col][numPosFilled[col]++] = getCurrPlayer();
        board[numPosFilled[col]++][col] = getCurrPlayer();
        numMoves++;
        //numPosFilled[col]++;

    }
}

// Vertical winner wrong because if the board has already been played
// currplayer is wrong from isWinnningMove

bool Board::isVerticalWin(int col, int currPlayer) const{
    if(numPosFilled[col] >= 3){
        return (board[numPosFilled[col] - 1][col] == currPlayer) &&
               (board[numPosFilled[col] - 2][col] == currPlayer) &&
               (board[numPosFilled[col] - 3][col] == currPlayer);

        // Wins can only be below next move
    }

    return false;
}

bool Board::isHorizontalWin(int col, int currPlayer) const{
    int continuousPlayerChar = 0;

    // Furthest left/right place required to check
    int leftBound = (col - 3) >= 0 ? col - 3 : 0;
    int rightBound = (col + 3) < WIDTH ? col + 3 : WIDTH - 1;

    for(int i = leftBound; i <= rightBound; ++i){
        if(i == col){
            continuousPlayerChar++;
            //cout << "Got to col: " << continuousPlayerChar << endl;
            continue;
        }
        if(continuousPlayerChar == 4) return true;

        if(board[numPosFilled[col]][i] == currPlayer){
            continuousPlayerChar++;
            //cout << i << " " << continuousPlayerChar << endl;
        } else {
            continuousPlayerChar = 0; // reset since opponent tile found
        }
    }

    /**cout << leftBound << " to " << rightBound << endl;
    cout << "Found: " << continuousPlayerChar << " Looking for: " << currPlayer << endl; **/

    return continuousPlayerChar >= 4;
}

bool Board::isDiagonalWin(int col, int currPlayer) const{
    int position[2] = {col, numPosFilled[col]};

    // // Count how many continous player tiles in direction from played tile
    int upperLeft = 0; // Northwest
    bool uL = false; // Found opponent tile in upperLeft (uL)?

    int lowerLeft = 0; // Southwest
    bool lL = false;

    int upperRight = 0; // Northeast
    bool uR = false;

    int lowerRight = 0; // Southeast
    bool lR = false;

    for(int i = 1; i < 4; ++i){
        if( isValidPos(position[0] - i, position[1] + i) && !uL){
            if( board[position[0] - i][position[1] + i] == currPlayer ) upperLeft++;
            else uL = true;
        }


        if( isValidPos(position[0] - i, position[1] - i) && !lL){
            if( board[position[0] - i][position[1] - i] == currPlayer ) lowerLeft++;
            else lL = true;
        }

        if( isValidPos(position[0] + i, position[1] + i) && !uR) {
            if( board[position[0] + i][position[1] + i] == currPlayer ) upperRight++;
            else uR = true;
        }

        if( isValidPos(position[0] + i, position[1] - i) && !lR) {
            if( board[position[0] + i][position[1] - i] == currPlayer ) lowerRight++;
            else lR = true;
        }

    }

    return (upperLeft + lowerRight) >= 3 || (lowerLeft + upperRight) >= 3;
}

bool Board::isDraw() const{
    return getNumMoves() == (Board::WIDTH * Board::HEIGHT);
}

bool Board::isWinningMove(int col) const{
    return isVerticalWin(col, getCurrPlayer()) || isHorizontalWin(col, getCurrPlayer()) || isDiagonalWin(col, getCurrPlayer());
}

void Board::printWinner() const{
    cout << "Player " << (getCurrPlayer() % 2) + 1 << " has won!" << endl;
}

void Board::print() const{
    cout << endl;

    for(int i = 0; i < WIDTH; ++i){
        cout << "___";
    }

    cout << endl;

    for(int i = (HEIGHT - 1); i >= 0; --i){
        for(int j = 0; j < WIDTH; ++j){
            if(board[i][j] == 1) cout << PLAYER1_CHAR;
            else if(board[i][j] == 2) cout << PLAYER2_CHAR;
            else cout << EMPTY_SPOT_CHAR;
        }
        cout << endl;
    }

    for(int i = 0; i < WIDTH; ++i){
        cout << "___";
    }

    cout << endl;

    for(int i = 0; i < WIDTH; ++i){
        cout << " " << i << " ";
    }

    cout << endl;
}
