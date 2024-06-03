#ifndef BOARD_H
#define BOARD_H

const int MIN_BOARD_SIZE = 10;

class Board {
private:
    char board[MIN_BOARD_SIZE][MIN_BOARD_SIZE];
public:
    Board();
    void print() const;
    char getPosition(int row, int column) const;
    void setPosition(int row, int column, char value);
    bool isCellOccupied(int row, int column) const;
};

#endif
