//
// Created by Jan on 24.03.2016.
//

#include "Game.h"

void Game::Print()
{
    board->Print();
}

Game::Game()
{
    board = new Board();
}