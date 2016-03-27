//
// Created by Jan on 24.03.2016.
//

#include "Game.h"

void Game::Print()
{
    board->Print();
}

void Game::Move(const string s)
{
    board->Move(s);
}

Game::Game()
{
    board = new Board();
}