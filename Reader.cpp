//
// Created by Jan on 31.03.2016.
//

#include "Reader.h"

using namespace std;

string Reader::getEvent()
{
    return event;
}

string Reader::getSite()
{
    return site;
}

string Reader::getDate()
{
    return date;
}

string Reader::getResult()
{
    return result;
}

string Reader::getWhite()
{
    return white;
}

string Reader::getBlack()
{
    return black;
}

Reader::Reader(string name)
{
    string s;
    match_results<string::const_iterator> result;

    try
    {
        file.open(name);
    }
    catch (ifstream::failure e) {
        cerr << "Exception opening/reading/closing file\n";
    }

    tags = new regex("\\[(\\w+) \"([\\s\\S]*)\"\\]");

    while(!file.eof())
    {
        getline(file, s);
        if(regex_match(s, result, *tags))
        {
            if(result[1].str() == "Event")
                event = result[2].str();
            else if(result[1].str() == "Site")
                site = result[2].str();
            else if(result[1].str() == "Date")
                date = result[2].str();
            else if(result[1].str() == "Result")
                this->result = result[2].str();
            else if(result[1].str() == "White")
                white = result[2].str();
            else if(result[1].str() == "Black")
                black = result[2].str();
        }
    }
}

Reader::~Reader()
{
    file.close();
}

Reader::Reader()
{

}





