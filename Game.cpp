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
void Game::clearScreen() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux and macOS
#endif
}
void Game::play() {
    while (!gameOver) {
        clearScreen();
        std::cout << "Turn of " << (turn == 1 ? player1.getName() : player2.getName()) << std::endl;
        if (turn == 1) {
            player2Board.print();
            playerTurn(player2Board, fleetPlayer2);
            checkGameOver();
            if (gameOver) break;
        } else {
            player1Board.print();
            playerTurn(player1Board, fleetPlayer1);
            checkGameOver();
            if (gameOver) break;
        }
        switchTurn();
        checkGameOver();
    }
    std::cout << "Game Over!" << std::endl;
    announceWinner();
}
void Game::checkGameOver() {
    allShipsSunkPlayer1 = allShipsSunk(fleetPlayer1);
    allShipsSunkPlayer2 = allShipsSunk(fleetPlayer2);
    if (allShipsSunkPlayer1 && allShipsSunkPlayer2) {
        gameOver = true;
    } else if (allShipsSunkPlayer1) {
        gameOver = true;
        winner = &player2;
    } else if (allShipsSunkPlayer2) {
        gameOver = true;
        winner = &player1;
    }
    for (auto it = fleetPlayer1.begin(); it!= fleetPlayer1.end(); ++it) {
        if (*it!= nullptr && (*it)->isSunk()) {
            delete *it;
            *it = nullptr;
        }
    }
    for (auto it = fleetPlayer2.begin(); it!= fleetPlayer2.end(); ++it) {
        if (*it!= nullptr && (*it)->isSunk()) {
            delete *it;
            *it = nullptr;
        }
    }
}
void Game::announceWinner() const {
    if (winner == nullptr) {
        std::cout << "The game is a tie!" << std::endl;
    } else {
        std::cout << "The winner is " << winner->getName() << "!" << std::endl;
    }
}
bool Game::isGameWon() const{
    return allShipsSunk(fleetPlayer1) || allShipsSunk(fleetPlayer2);
}
bool Game::allShipsSunk(const std::vector<Ship*>& fleet) const{
    for (auto& ship: fleet) {
        if (!ship->isSunk())
            return false;
    }
    return true;
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
void Game::saveRanking(const char* file) {
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
    while (true) {
        std::cout << "Enter coordinate to shoot (e.g., A1): ";
        std::cin >> coordinate;
        if (strlen(coordinate) != 2) {
            std::cout << "Invalid coordinate. Please enter a valid coordinate (e.g., A1)." << std::endl;
            continue;
        }
        int row = coordinate[1] - '1';
        int column = std::toupper(coordinate[0]) - 'A';
        if (row < 0 || row >= MIN_BOARD_SIZE || column < 0 || column >= MIN_BOARD_SIZE) {
            std::cout << "Invalid coordinate. Please enter a valid coordinate." << std::endl;
            continue;
        }
        if (enemyBoard.getPosition(row, column) == 'X' || enemyBoard.getPosition(row, column) == 'O') {
            std::cout << "You've already shot at this coordinate. Please enter a new one." << std::endl;
            continue;
        }
        if (enemyBoard.isCellOccupied(row, column)) {
            char shipType = enemyBoard.getPosition(row, column);
            std::cout << "Hit on a ship of type " << shipType << "!" << std::endl;
            for (auto& ship : enemyFleet) {
                if (ship!= nullptr &&!ship->isSunk() && ship->getLength() == shipType - '0') {
                    ship->sink();
                    break;
                }
            }
        } else {
            std::cout << "Miss!" << std::endl;
        }
        enemyBoard.setPosition(row, column, enemyBoard.isCellOccupied(row, column) ? 'X' : 'O');
        enemyBoard.print();
        break;
    }
}
void Game::switchTurn() {
    turn = (turn == 1) ? 2 : 1;
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
