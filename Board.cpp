//
// Created by Jan on 24.03.2016.
//

#include <iostream>
#include "Board.h"

using namespace std;

void Board::Print()
{
    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        boardSnapshot[i][j].type = None;
    }
    whitePlayer->PleaseCompleteTheSnapshot(boardSnapshot);
    blackPlayer->PleaseCompleteTheSnapshot(boardSnapshot);

    for(int i = 7; i >= 0; --i)
    {
        for(int j = 0; j < 8; ++j)
        {
            switch(boardSnapshot[i][j].type)
            {
                case None:
                    cout<<'-';
                    break;
                case Pawn:
                    if(boardSnapshot[i][j].colour == White)
                        cout<<'P';
                    else cout<<'p';
                    break;
                case Rook:
                    if(boardSnapshot[i][j].colour == White)
                        cout<<'R';
                    else cout<<'r';
                    break;
                case Knight:
                    if(boardSnapshot[i][j].colour == White)
                        cout<<'N';
                    else cout<<'n';
                    break;
                case Bishop:
                    if(boardSnapshot[i][j].colour == White)
                        cout<<'B';
                    else cout<<'b';
                    break;
                case Queen:
                    if(boardSnapshot[i][j].colour == White)
                        cout<<'Q';
                    else cout<<'q';
                    break;
                case King:
                    if(boardSnapshot[i][j].colour == White)
                        cout<<'K';
                    else cout<<'k';
                    break;
            }
        }
        cout<<endl;
    }
}

Board::Board()
{
    whitePlayer = new Player(White);
    blackPlayer = new Player(Black);
    turn = White;

    boardSnapshot = new Tile*[8];
    for(int i = 0; i < 8; ++i)
    {
        boardSnapshot[i] = new Tile[8];
    }
}