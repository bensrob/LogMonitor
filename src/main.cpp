#include "../include/main.h"

//Vector of all ctails
std::vector<ctail> logfiles;

//Before exit ensure everything is closed
void cleanup( int sig )
{
	tout( "\nRecieved interupt. Code" << sig << ".\n" );
	threadkiller = true;
	logfiles.clear();
	exit(0);
}


int main()
{
	//Catch interupt signal and begin cleanup
	signal(SIGINT, cleanup);

	//Create default config file if needed
	config.createDefaults();

	//Read config files;
	std::map<std::string,monitor> monitors = parser.getConfig();

	//Find logfile locations from monitors
	std::vector<std::string> loglocs;
	for( std::map<std::string,monitor>::iterator it = monitors.begin();	it != monitors.end();	it++ )
	{
		tout( "Found config for " << it->first << endl );
		it->second.print();
		loglocs.push_back( it->second.logfile );
	}
	std::unique( loglocs.begin(), loglocs.end() );

	//Create new ctail per logfile
	for( std::vector<std::string>::iterator it = loglocs.begin(); it != loglocs.end(); it++ )	logfiles.emplace_back( *it );

	//Loop through all ctails to initialise and spawn threads
	for( std::vector<ctail>::iterator it = logfiles.begin(); it != logfiles.end(); it++ )
	{
		//Attach all monitors for this logfile
		for( std::map<std::string,monitor>::iterator monit = monitors.begin(); monit != monitors.end(); monit++ )
			if( it->loc == monit->second.logfile )	it->monitors.push_back( monit->second );

		//Start thread, passing ctail for a logfile
		std::thread ( logthread, &*it ).detach();
	}

	//Main loop
	//Handles cleaning of old database entries
	while( true )
	{
		memman.print();
		sleep(10);
		//Delete all expired database entries
	}
}
