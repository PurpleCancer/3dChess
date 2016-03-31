//
// Created by Jan on 24.03.2016.
//

#include <iostream>
#include "Board.h"


using namespace std;

void Board::Print()
{
    for(int i = 0; i < BOARD_HEIGHT; ++i)
    {
        for(int j = 0; j < BOARD_WIDTH; ++j)
        boardSnapshot[i][j].type = None;
    }
    whitePlayer->PleaseCompleteTheSnapshot(boardSnapshot);
    blackPlayer->PleaseCompleteTheSnapshot(boardSnapshot);

    for(int i = BOARD_HEIGHT-1; i >= 0; --i)
    {
        for(int j = 0; j < BOARD_WIDTH; ++j)
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

void Board::Move(const string s)
{
    if(s == "O-O")
        cout<<"Kingside castling"<<endl;
    else if(s == "O-O-O")
        cout<<"Queenside castling"<<endl;
    else
    {
        match_results<string::const_iterator> result;
        regex_match(s, result, *pattern);


        //into natural language
        if(result[1].str().empty())
            cout<<"Pawn ";
        else switch(result[1].str()[0])
            {
                case 'K':
                    cout<<"King ";
                    break;
                case 'Q':
                    cout<<"Queen ";
                    break;
                case 'R':
                    cout<<"Rook ";
                    break;
                case 'N':
                    cout<<"Knight ";
                    break;
                case 'B':
                    cout<<"Bishop ";
                    break;
                default:
                    cout<<"None ";
                    break;
            }
        if(!result[2].str().empty())
            cout<<"in row "<<result[2]<<", ";
        if(!result[3].str().empty())
            cout<<"in column "<<result[3]<<", ";
        if(!result[4].str().empty())
            cout<<"took and ";
        cout<<"moved to "<<result[5]<<result[6];
        if(!result[7].str().empty())
        {
            cout<<" and got promoted into a ";
            switch(result[7].str()[1])
            {
                case 'K':
                    cout<<"King ";
                    break;
                case 'Q':
                    cout<<"Queen ";
                    break;
                case 'R':
                    cout<<"Rook ";
                    break;
                case 'N':
                    cout<<"Knight ";
                    break;
                case 'B':
                    cout<<"Bishop ";
                    break;
                default:
                    cout<<"None ";
                    break;
            }
        }
        cout<<endl;

        /*int j = 0;
        for(size_t i = 1; i < result.size(); ++i, ++j)
        {
            cout<<j<<':'<<result[i]<<endl;
        }*/
    }

}

Board::Board()
{
    whitePlayer = new Player(White);
    blackPlayer = new Player(Black);
    turn = White;

    boardSnapshot = new Tile*[BOARD_HEIGHT];
    for(int i = 0; i < BOARD_HEIGHT; ++i)
    {
        boardSnapshot[i] = new Tile[BOARD_WIDTH];
    }

    pattern = new regex("([KQRNB])?([a-h])?([1-8])?(x)?([a-h])([1-8])(=[KQRNB])?[+#]?");
}

Board::~Board()
{
    delete whitePlayer;
    delete blackPlayer;
    for(int i = 0; i < BOARD_HEIGHT; ++i)
    {
        delete boardSnapshot[i];
    }
    delete boardSnapshot;
    delete pattern;
}


