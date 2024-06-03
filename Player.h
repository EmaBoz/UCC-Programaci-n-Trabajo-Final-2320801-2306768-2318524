#ifndef PLAYER_H
#define PLAYER_H

const int MAX_NAME_LENGTH = 100;
class Player {
private:
    char name[MAX_NAME_LENGTH];
public:
    Player(const char* name);
    const char* getName() const;
};

#endif
