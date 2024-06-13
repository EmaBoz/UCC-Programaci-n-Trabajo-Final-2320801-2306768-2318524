#include "Game.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include "AircraftCarrier.h"
#include "Cruiser.h"
#include "Board.h"
#include "Destroyer.h"
#include "Battleship.h"
Game::Game(const char* player1Name, const char* player2Name) : player1(player1Name), player2(player2Name), turn(1), gameOver(false) {
    initialiseFleet(fleetPlayer1);
    initialiseFleet(fleetPlayer2);
    std::random_shuffle(fleetPlayer1.begin(), fleetPlayer1.end());
    std::random_shuffle(fleetPlayer2.begin(), fleetPlayer2.end());
}

Game::~Game() {
    for (auto& ship : fleetPlayer1) {
        delete ship;
    }
    for (auto& ship : fleetPlayer2) {
        delete ship;
    }
}

void Game::play() {
    while (!gameOver) {
        system("cls");
        std::cout << "Turn of " << (turn == 1 ? player1.getName() : player2.getName()) << std::endl;
        if (turn == 1) {
            player2Board.print();
            playerTurn(player2Board, fleetPlayer2);
        } else {
            player1Board.print();
            playerTurn(player1Board, fleetPlayer1);
        }
        switchTurn();
        checkGameOver();
    }
    std::cout << "Game Over!" << std::endl;
}
void Game::placeShips(Board& board, std::vector<Ship*>& fleet) {
    for (Ship* ship : fleet) {
        int row, column;
        std::cout << "Enter row and column to place " << ship->getLength() << "-unit ship: ";
        std::cin >> row >> column;
        for (int i = 0; i < ship->getLength(); ++i) {
            board.setPosition(row, column + i, 'S');
        }
    }
}
void Game::saveRanking(const char* file) const {
    std::ofstream fout(file);
    if (!fout) {
        std::cerr << "Error opening file to save ranking." << std::endl;
        return;
    }
    for (const auto& score : ranking) {
        fout << score.first << " " << score.second << std::endl;
    }
    fout.close();
    std::cout << "Ranking saved successfully." << std::endl;
}

void Game::initialiseFleet(std::vector<Ship*>& fleet){
    fleet.push_back(new AircraftCarrier());
    fleet.push_back(new Battleship());
    fleet.push_back(new Battleship());
    fleet.push_back(new Cruiser());
    fleet.push_back(new Cruiser());
    fleet.push_back(new Cruiser());
    fleet.push_back(new Destroyer());
    fleet.push_back(new Destroyer());
    fleet.push_back(new Destroyer());
    fleet.push_back(new Destroyer());
}
void Game::playerTurn(Board& enemyBoard, std::vector<Ship*>& enemyFleet) {
    char coordinate[3];
    std::cout << "Enter coordinate to shoot (e.g., A1): ";
    std::cin >> coordinate;
    int row = coordinate[1] - '1';
    int column = std::toupper(coordinate[0]) - 'A';
    if (row >= 0 && row < MIN_BOARD_SIZE && column >= 0 && column < MIN_BOARD_SIZE) {
        if (enemyBoard.isCellOccupied(row, column)) {
            char shipType = enemyBoard.getPosition(row, column);
            std::cout << "Hit on a ship of type " << shipType << "!" << std::endl;
            for (auto& ship : enemyFleet) {
                if (!ship->isSunk() && ship->getLength() == shipType - '0') {
                    ship->sink();
                    break;
                }
            }
        } else {
            std::cout << "Miss!" << std::endl;
        }
        enemyBoard.setPosition(row, column, enemyBoard.isCellOccupied(row, column) ? 'X' : 'O');
        enemyBoard.print();
    } else {
        std::cout << "Invalid coordinate. Please enter a valid coordinate." << std::endl;
        playerTurn(enemyBoard, enemyFleet);
    }
}

void Game::switchTurn() {
    turn = (turn == 1) ? 2 : 1;
}

void Game::checkGameOver() {
    bool player1Sunk = true;
    bool player2Sunk = true;
    for (const auto& ship : fleetPlayer1) {
        if (!ship->isSunk()) {
            player1Sunk = false;
            break;
        }
    }
    for (const auto& ship : fleetPlayer2) {
        if (!ship->isSunk()) {
            player2Sunk = false;
            break;
        }
    }
    if (player1Sunk || player2Sunk) {
        gameOver = true;
        std::cout << "Player " << (player1Sunk ? player2.getName() : player1.getName()) << " wins!" << std::endl;
        updateRanking(player1Sunk ? player2.getName() : player1.getName());
    }
}

void Game::updateRanking(const char* winnerName) {
    int score = turn == 1 ? fleetPlayer2.size() : fleetPlayer1.size(); // Score based on the remaining number of ships
    ranking.push_back(std::make_pair(winnerName, score));
    std::sort(ranking.begin(), ranking.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second > b.second;
    });
    if (ranking.size() > 5) {
        ranking.resize(5);
    }
}
