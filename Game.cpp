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

Game::Game(string name)
{
    board = new Board();
    reader = new Reader(name);
}

Game::Game()
{

}

Game::~Game()
{
    delete board;
    delete reader;
}