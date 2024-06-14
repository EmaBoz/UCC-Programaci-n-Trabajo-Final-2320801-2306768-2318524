#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Board.h"
#include "Ship.h"
#include <vector>
#include <string>

class Game {
private:
    Player player1;
    Player player2;
    int turn;
    bool gameOver;
    bool allShipsSunkPlayer1;
    bool allShipsSunkPlayer2;
    Player* winner;
    std::vector<std::pair<std::string, int>> ranking;

public:
    void clearScreen();
    Board player1Board;
    Board player2Board;
    std::vector<Ship*> fleetPlayer1;
    std::vector<Ship*> fleetPlayer2;
    Game(const char* player1Name, const char* player2Name);
    ~Game();
    void play();
    bool isGameWon() const;
    void placeShips(Board& board, std::vector<Ship*>& fleet);
    void saveRanking(const char* file) ;
    void initialiseFleet(std::vector<Ship*>& fleet);
    void playerTurn(Board& enemyBoard, std::vector<Ship*>& enemyFleet);
    void switchTurn();
    void announceWinner()const;
    void checkGameOver();
    bool allShipsSunk(const std::vector<Ship*>& fleet) const;
    void updateRanking(const char* winnerName);
};
#endif
