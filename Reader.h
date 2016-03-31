//
// Created by Jan on 31.03.2016.
//

#ifndef INC_3DCHESS_READER_H
#define INC_3DCHESS_READER_H

#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include "Delarations.h"

using namespace std;

class Reader {
public:
    string getEvent();
    string getSite();
    string getDate();
    string getResult();
    string getWhite();
    string getBlack();

    Reader(string name);
    ~Reader();
private:
    string event="";
    string site="";
    string date="";
    string result="";
    string white="";
    string black="";
    ifstream file;
    regex* tags;
    regex* moves;

    Reader();
};


#endif //INC_3DCHESS_READER_H
