#include "../include/monitor.h"

void monitor::print()
{
	std::cout 	<< "	Active:     " << (this->functional?"Yes":"No")	<< endl
			<< "	Logfile:    " << this->logfile 			<< endl
			<< "	Protocol:   " << this->protocol 		<< endl
			<< "	Port:       " << this->port 			<< endl
			<< "	Count:	    " << this->count 			<< endl
			<< "	Listentime: " << this->listentime 		<< endl
			<< "	Bantime:    " << this->bantime 			<< endl
			<< "	Permanent:  " << this->permanent 		<< endl;

	for( std::vector<std::string>::iterator  it = this->regex.begin(); 	it != this->regex.end(); it++ )  	std::cout << "	Regex:      " << *it << endl;
	for( std::vector<std::string>::iterator  it = this->ignore.begin(); 	it != this->ignore.end(); it++ )	std::cout << "	Ignore:     " << *it << endl;
	for( std::vector<unsigned int>::iterator it = this->ignoreip.begin();	it != this->ignoreip.end(); it++ )	std::cout << "	Ignoreip:   " << *it << endl;
}
