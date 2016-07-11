//
// Created by Jan on 24.03.2016.
//

#include "Board.h"


using namespace std;

Tile** Board::getBoardSnapshot(){
    return this->boardSnapshot;
}

void Board::UpdateSnapshot()
{
    for(int i = 0; i < BOARD_HEIGHT; ++i)
    {
        for(int j = 0; j < BOARD_WIDTH; ++j)
            boardSnapshot[i][j].type = None;
    }
    whitePlayer->PleaseCompleteTheSnapshot(boardSnapshot);
    blackPlayer->PleaseCompleteTheSnapshot(boardSnapshot);
}

void Board::Print()
{
    UpdateSnapshot();

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
    {
        cout<<"Kingside castling"<<endl;
        switch (turn)
        {
            case White:
                whitePlayer->KingsideCastling();
                turn = Black;
                break;
            case Black:
                blackPlayer->KingsideCastling();
                turn = White;
                break;
            default:
                cout<<"Kolejka nieznanego gracza"<<endl;
                break;
        }
    }
    else if(s == "O-O-O")
    {
        cout<<"Queenside castling"<<endl;
        switch (turn)
        {
            case White:
                whitePlayer->QueensideCastling();
                turn = Black;
                break;
            case Black:
                blackPlayer->QueensideCastling();
                turn = White;
                break;
            default:
                cout<<"Kolejka nieznanego gracza"<<endl;
                break;
        }
    }
    else
    {
        match_results<string::const_iterator> result;
        regex_match(s, result, *pattern);

        PieceType type = None;
        PieceType promotion = None;

        int startColumn;
        int startRow;
        int targetColumn;
        int targetRow;

        bool take;

        //into natural language
        if(result[1].str().empty())
        {
            cout<<"Pawn ";
            type = Pawn;
        }
        else switch(result[1].str()[0])
            {
                case 'K':
                    cout<<"King ";
                    type = King;
                    break;
                case 'Q':
                    cout<<"Queen ";
                    type = Queen;
                    break;
                case 'R':
                    cout<<"Rook ";
                    type = Rook;
                    break;
                case 'N':
                    cout<<"Knight ";
                    type = Knight;
                    break;
                case 'B':
                    cout<<"Bishop ";
                    type = Bishop;
                    break;
                default:
                    cout<<"None ";
                    break;
            }
        if(!result[2].str().empty())
        {
            cout<<"in row "<<result[2]<<", ";
            startColumn = result[2].str()[0] - '`';   //for a to equal 1 and so on
        }
        else startColumn  = 0;

        if(!result[3].str().empty())
        {
            cout<<"in column "<<result[3]<<", ";
            startRow = result[3].str()[0] - '0';
        }
        else startRow = 0;

        if(!result[4].str().empty())
        {
            cout<<"took and ";
            take = true;
        }
        else take = false;

        cout<<"moved to "<<result[5]<<result[6];
        targetColumn = result[5].str()[0] - '`';
        targetRow = result[6].str()[0] - '0';

        if(!result[7].str().empty())
        {
            cout<<" and got promoted into a ";
            switch(result[7].str()[1])
            {
                case 'Q':
                    cout<<"Queen ";
                    promotion = Queen;
                    break;
                case 'R':
                    cout<<"Rook ";
                    promotion = Rook;
                    break;
                case 'N':
                    cout<<"Knight ";
                    promotion = Knight;
                    break;
                case 'B':
                    cout<<"Bishop ";
                    promotion = Bishop;
                    break;
                default:
                    cout<<"None ";
                    break;
            }
        }
        cout<<endl;

        UpdateSnapshot();
        switch (turn)
        {
            case White:
                if(promotion == None)whitePlayer->FindPieceToMove(type, startColumn, startRow, targetColumn, targetRow, boardSnapshot);
                else whitePlayer->MovePawnAndPromote(type, startColumn, startRow, targetColumn, targetRow, boardSnapshot, promotion);
                if(take)blackPlayer->FindPieceToTake(targetColumn, targetRow);
                turn = Black;
                break;
            case Black:
                if(promotion == None)blackPlayer->FindPieceToMove(type, startColumn, startRow, targetColumn, targetRow, boardSnapshot);
                else blackPlayer->MovePawnAndPromote(type, startColumn, startRow, targetColumn, targetRow, boardSnapshot, promotion);
                if(take)whitePlayer->FindPieceToTake(targetColumn, targetRow);
                turn = White;
                break;
            default:
                cout<<"Kolejka nieznanego gracza"<<endl;
                break;
        }

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

    pattern = new regex("([KQRNB])?([a-h])?([1-8])?(x)?([a-h])([1-8])(=[QRNB])?[+#]?");
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


