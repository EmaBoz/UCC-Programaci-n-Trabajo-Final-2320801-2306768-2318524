#include "Game.h"
#include<cstring>
#include<iostream>
int main() {
    int option;
    char player1Name[MAX_NAME_LENGTH];
    char player2Name[MAX_NAME_LENGTH];

    std::cout << "Welcome to Battleship!" << std::endl;
    std::cout << "Select game mode:" << std::endl;
    std::cout << "1. Single player (against Computer)" << std::endl;
    std::cout << "2. Two players" << std::endl;
    std::cout << "Option: ";
    std::cin >> option;

    if (option == 1) {
        std::cout << "Enter your name: ";
        std::cin >> player1Name;
        std::strcpy(player2Name, "Computer");
    } else if (option == 2) {
        std::cout << "Player 1, enter your name: ";
        std::cin >> player1Name;
        std::cout << "Player 2, enter your name: ";
        std::cin >> player2Name;
    } else {
        std::cout << "Invalid option. Exiting game." << std::endl;
        return 1;
    }

    Game game(player1Name, player2Name);
    game.play();
    game.saveRanking("ranking.txt");

    return 0;
}
