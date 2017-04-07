#include "../include/parser.h"

std::vector<std::string> parser::getWords( char *input )
{
	std::string buffer;
	std::stringstream ss(input);
	std::vector<std::string> words;
	while( ss >> buffer )
        {
                if( buffer.at(0) == '#' ) break;
                words.push_back(buffer);
        }
	return words;
}

parser::parser(){}

parser::~parser(){}
