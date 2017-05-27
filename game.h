#ifndef GAME_H
#define GAME_H

int random(int MIN, int MAX)
{
    return (rand() % (MAX - MIN + 1)) + MIN;
}

#endif // GAME_H
