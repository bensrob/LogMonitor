#include "../include/monitor.h"

// Print config stored in monitor
void monitor::print()
{
	// Single line config
	tout( 	   "	Active:     " << (this->functional?"Yes":"No")	<< endl
		<< "	Logfile:    " << this->logfile 			<< endl
		<< "	Protocol:   " << this->protocol 		<< endl
		<< "	Port:       " << this->port 			<< endl
		<< "	Count:	    " << this->count 			<< endl
		<< "	Listentime: " << this->listentime 		<< endl
		<< "	Bantime:    " << this->bantime 			<< endl
		<< "	Permanent:  " << this->permanent 		<< endl );

	// Regex strings
	for( std::vector<std::string>::iterator  it = this->regex.begin(); 	it != this->regex.end(); it++ )
	{
		tout( "	Regex:      " << *it << endl );
	}

	// Regex ignore strings
	for( std::vector<std::string>::iterator  it = this->ignore.begin(); 	it != this->ignore.end(); it++ )
	{
		tout( "	Ignore:     " << *it << endl );
	}

	// IP Addresses to ignore
	for( std::vector<unsigned int>::iterator it = this->ignoreip.begin();	it != this->ignoreip.end(); it++ )
	{
		tout( "	Ignoreip:   " << *it << endl );
	}
}
