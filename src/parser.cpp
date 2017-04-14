#include "../include/parser.h"

std::map<std::string,monitor> parser::getConfig()
{
	std::vector<std::string> files = findfiles();
	std::vector<std::string> conf, local;

	//Find all .conf and .local files
        for( std::vector<std::string>::iterator it = files.begin(); it != files.end(); it++ )
        {
                if	( it->find(".conf" ) != std::string::npos )	conf.push_back(*it);
        	else if ( it->find(".local") != std::string::npos )	local.push_back(*it);
	}

	//Get settings from .conf files
        for( std::vector<std::string>::iterator it = conf.begin(); it != conf.end(); it++ )	getFile( *it );

	//Overwrite where needed from .local files
	for( std::vector<std::string>::iterator it = local.begin(); it != local.end(); it++ )	getFile( *it );

	//Fill in any missing data from general settings
	this->setDefaults();

	//Check monitors for completed config
	this->checkState();

	//Remove all monitors with incomplete configuration
	std::map<std::string,monitor>::iterator it = this->options.begin();
	while( it != this->options.end() )
	{
		if( !it->second.functional )
		{
			this->options.erase (it);
			it = this->options.begin();
		}
		else it++;
	}

	return this->options;
}

void parser::getFile( std::string filename )
{
	this->section = "ERROR";

	std::ifstream file( filename.c_str() );
	if( file.is_open() )
	{
		while( file.good() )
		{
			char buffer[1024];
			file.getline( buffer, 1024 );
			getCommands( getWords( buffer ) );
		}
		file.close();
	}
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
                if( it->second.regex.empty()  )         it->second.regex =	this->options["general"].regex;
                if( it->second.ignore.empty() )         it->second.ignore =	this->options["general"].ignore;
                if( it->second.ignoreip.empty() )       it->second.ignoreip =	this->options["general"].ignoreip;
	}
}

//Check all required variables are set
void parser::checkState()
{
        for( std::map<std::string,monitor>::iterator it = this->options.begin(); it!=this->options.end(); it++ )
        {
		it->second.functional = true;

		if( it->second.protocol.empty() )       it->second.functional = false;
                if( it->second.logfile.empty() )        it->second.functional = false;
                if( it->second.port       < 0 )         it->second.functional = false;
                if( it->second.bantime    < 1 )         it->second.functional = false;
                if( it->second.count      < 1 )         it->second.functional = false;
                if( it->second.listentime < 1 )         it->second.functional = false;
                if( it->second.permanent  < 0 )         it->second.functional = false;
		if( it->second.regex.empty()  )		it->second.functional = false;
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

	if( words[0] == "port" && words[1] == "any" ) 	return;
	else if( words[0] == "protocol" )	this->options[this->section].protocol	= words[1];
	else if( words[0] == "logfile" )	this->options[this->section].logfile	= words[1];
	else if( words[0] == "port" )		this->options[this->section].port	= std::stoi( words[1] );
	else if( words[0] == "bantime" )	this->options[this->section].bantime	= std::stoi( words[1] );
	else if( words[0] == "count" )		this->options[this->section].count	= std::stoi( words[1] );
	else if( words[0] == "listentime" )	this->options[this->section].listentime	= std::stoi( words[1] );
	else if( words[0] == "permanent" )	this->options[this->section].permanent	= std::stoi( words[1] );
	else if( words[0] == "regex" )
	{
		std::string temp;
		for( std::vector<std::string>::iterator it = ++(words.begin()); it!=words.end(); it++ )
		{
			temp += " " + *it;
		}
		this->options[this->section].regex.push_back( temp );
	}
        else if( words[0] == "ignore" )
        {
		std::string temp;
                for( std::vector<std::string>::iterator it = ++(words.begin()); it!=words.end(); it++ )
                {
                        temp += " " + *it;
                }
                this->options[this->section].ignore.push_back( temp );
        }
        else if( words[0] == "ignoreip" )
        {
		ipaddress ip;
                for( std::vector<std::string>::iterator it = ++(words.begin()); it!=words.end(); it++ )
                {
			this->options[this->section].ignoreip.push_back( ip.convert( *it ) );
                }
        }
}


parser::parser(){
	this->section = "ERROR";
}


parser::~parser(){}
