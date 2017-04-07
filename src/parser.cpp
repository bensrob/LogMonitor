#include "../include/parser.h"

void parser::getConfig( std::string filename )
{
	std::ifstream file( filename.c_str() );
	if( file.is_open() )
	{
		while( file.good() )
		{
			char buffer[1024];
			file.getline( buffer, 1024 );
			std::vector<std::string> words = getWords( buffer );

			for(int i=0; i!=words.size(); i++)  std::cout << words[i] << std::endl;
		}
	}
}


std::vector<std::string> parser::getWords( char *input )
{
	std::string buffer;
	std::stringstream ss(input);
	std::vector<std::string> words;
	while( ss >> buffer )
	{
		if( buffer.size() > 0 )
		{
			if( buffer.front() == '#' )	break;
			if( buffer.front() == '=' )	buffer = buffer.substr( 1, buffer.size()-1 );
			if( buffer.back () == '=' )	buffer.pop_back();
			if( buffer.size() > 0 )		words.push_back(buffer);
		}
	}
	return words;
}


void parser::getCommands( std::vector<std::string> words )
{
	if( words.size() == 0 ) return;
	if( words[0].front() == '[' && words[0].back() == ']' )
	{
		this->section = words[0].substr( 1, words[0].size()-2 );
		return;
	}

	if( words[0] == "protocol" )
	{
	}
	else if( words[0] == "port" )
	{
	}
	else if( words[0] == "bantime" )
	{
	}
	else if( words[0] == "count" )
	{
	}
	else if( words[0] == "listentime" )
	{
	}
	else if( words[0] == "permanent" )
	{
	}
	else if( words[0] == "logfile" )
	{
	}
	else if( words[0] == "regex" )
	{
	}
	else if( words[0] == "ignore" )
	{
	}
	else if( words[0] == "ignoreip" )
	{
	}
}


parser::parser(){
	this->section = "general";
}


parser::~parser(){}
