#include <iostream>
#include "Game.h"

using namespace std;

Game* game;

int main()
{
    game = new Game();
    game->Print();

    return 0;
}