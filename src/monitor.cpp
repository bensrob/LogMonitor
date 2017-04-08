#include "../include/monitor.h"

void monitor::print()
{
	std::cout 	<< "	Active:     " << (this->functional?"Yes":"No")	<< std::endl
			<< "	Logfile:    " << this->logfile 			<< std::endl
			<< "	Protocol:   " << this->protocol 		<< std::endl
			<< "	Port:       " << this->port 			<< std::endl
			<< "	Count:	    " << this->count 			<< std::endl
			<< "	Listentime: " << this->listentime 		<< std::endl
			<< "	Bantime:    " << this->bantime 			<< std::endl
			<< "	Permanent:  " << this->permanent 		<< std::endl;

	for( std::vector<std::string>::iterator  it = this->regex.begin(); 	it != this->regex.end(); it++ )  	std::cout << "	Regex:      " << *it << std::endl;
	for( std::vector<std::string>::iterator  it = this->ignore.begin(); 	it != this->ignore.end(); it++ )	std::cout << "	Ignore:     " << *it << std::endl;
	for( std::vector<unsigned int>::iterator it = this->ignoreip.begin();	it != this->ignoreip.end(); it++ )	std::cout << "	Ignoreip:   " << *it << std::endl;
}
