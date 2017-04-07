#include "../include/parser.h"

void parser::getConfig( std::string filename )
{
	this->section = "general";

	std::ifstream file( filename.c_str() );
	if( file.is_open() )
	{
		while( file.good() )
		{
			char buffer[1024];
			file.getline( buffer, 1024 );
			getCommands( getWords( buffer ) );
		}
	}

	this->setDefaults();
	this->checkState();
}

//Set defaults after all configs have been read as order not guaranteed
void parser::setDefaults(){
	for( std::map<std::string,monitor>::iterator it = this->options.begin(); it!=this->options.end(); it++ )
	{
		if( it->second.protocol.empty() )	it->second.protocol =	this->options["general"].protocol;
		if( it->second.logfile.empty() )	it->second.logfile =	this->options["general"].logfile;
		if( it->second.port 	== 0 )		it->second.port =	this->options["general"].port;
		if( it->second.bantime 	== 0 )		it->second.bantime =	this->options["general"].bantime;
		if( it->second.count 	== 0 )		it->second.count =	this->options["general"].count;
		if( it->second.listentime == 0 )	it->second.listentime =	this->options["general"].listentime;
		if( it->second.permanent == 0 )		it->second.permanent =	this->options["general"].permanent;
	}
}

//Check all required variables are set
void parser::checkState()
{
	std::cout << "How many maps:	" << this->options.size() << std::endl;
        for( std::map<std::string,monitor>::iterator it = this->options.begin(); it!=this->options.end(); it++ )
        {
		std::cout << "IT'S RUNNING" << std::endl;
		it->second.functional = true;

		if( it->second.protocol.empty() )       it->second.functional = false;
                if( it->second.logfile.empty() )        it->second.functional = false;
                if( it->second.port       < 0 )         it->second.functional = false;
                if( it->second.bantime    < 1 )         it->second.functional = false;
                if( it->second.count      < 1 )         it->second.functional = false;
                if( it->second.listentime < 1 )         it->second.functional = false;
                if( it->second.permanent  < 0 )         it->second.functional = false;
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
	if( words.size() <= 1 )
	{
		if( words.size() > 0 && words[0].front() == '[' && words[0].back() == ']' )
		{
			this->section = words[0].substr( 1, words[0].size()-2 );
		}
		return;
	}

	if( words[1] == "any" ) 		return;
	else if( words[0] == "protocol" )	this->options[this->section].protocol	= words[1];
	else if( words[0] == "logfile" )	this->options[this->section].logfile	= words[1];
	else if( words[0] == "port" )		this->options[this->section].port	= std::stoi( words[1] );
	else if( words[0] == "bantime" )	this->options[this->section].bantime	= std::stoi( words[1] );
	else if( words[0] == "count" )		this->options[this->section].count	= std::stoi( words[1] );
	else if( words[0] == "listentime" )	this->options[this->section].listentime	= std::stoi( words[1] );
	else if( words[0] == "permanent" )	this->options[this->section].permanent	= std::stoi( words[1] );
}


parser::parser(){
	this->section = "general";
}


parser::~parser(){}
