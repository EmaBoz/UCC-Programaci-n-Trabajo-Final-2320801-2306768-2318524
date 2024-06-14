#include "Board.h"
#include <iostream>
Board::Board() {
    for (int i = 0; i < MIN_BOARD_SIZE; ++i) {
        for (int j = 0; j < MIN_BOARD_SIZE; ++j) {
            board[i][j] = '-';
        }
    }
}
void Board::print() const {
    std::cout << "  ";
    for (int i = 0; i < MIN_BOARD_SIZE; ++i) {
        std::cout << char('A' + i) << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < MIN_BOARD_SIZE; ++i) {
        std::cout << i + 1 << " ";
        for (int j = 0; j < MIN_BOARD_SIZE; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
bool Board::isHit(int row, int col) {
    if (board[row][col] == 1) {
        board[row][col] = 2;
        return true;
    }
    else {
        return false;
    }
}
bool Board::isGameWon() {
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            if (board[row][col] == 1) {
                return false; // game is not yet won
            }
        }
    }
    return true; // game is won
}
char Board::getPosition(int row, int column) const {
    return board[row][column];
}
void Board::setPosition(int row, int column, char value) {
    board[row][column] = value;
}
bool Board::isCellOccupied(int row, int column) const {
    return board[row][column] != '-';
}
