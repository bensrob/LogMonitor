#include "include/ctail.h"

ctail::ctail(std::string location)
{
	this->loc = location;
	this->init();
}

ctail::ctail(const ctail &in){
	this->loc = in.loc;
	this->init();
}

void ctail::init(){
	this->log.open(this->loc);
	//if( !*this->log.is_open() )        exit(1);
	this->log.seekg(0,std::ios_base::end);
	this->fd = inotify_init();
       	//if( fd < 0 )    exit(2);
	this->wd = inotify_add_watch( fd, this->loc.c_str(), IN_MODIFY );
	//if( wd < 0 )    exit(3);
}

std::vector<std::string> ctail::watch(){
	std::vector<std::string> returnbuffer;
	char buffer[BUF_LEN];
	read( this->fd, buffer, BUF_LEN );
	//if( length < 0) exit(4);
	this->log.clear();
	while( !this->log.eof() )
	{
		std::string line;
		getline(this->log,line);
		if( line.length() > 0 )	returnbuffer.push_back(line);
	}
	return returnbuffer;
}

ctail::~ctail(){
	inotify_rm_watch( this->fd, this->wd );
	close( this->fd );
	this->log.close();
}

