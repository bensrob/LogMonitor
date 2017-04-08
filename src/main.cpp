#include "../include/main.h"
#include "../include/ctail.h"
#include "../include/threads.h"
#include "../include/config.h"
#include "../include/parser.h"
#include "../include/monitor.h"

//Vector of all ctails
std::vector<ctail> logfiles;

//Before exit ensure everything is closed
void cleanup( int sig )
{
	std::cout << "\nRecieved interupt. Code" << sig << ".\n";
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
		std::cout << "Found config for " << it->first << std::endl;
		it->second.print();
		loglocs.push_back( it->second.logfile );
	}
	std::unique( loglocs.begin(), loglocs.end() );

	//Create new ctail per logfile
	for( std::vector<std::string>::iterator it = loglocs.begin(); it != loglocs.end(); it++ )
	{
		logfiles.emplace_back( *it );
		//Attach all monitors for this logfile
		for( std::map<std::string,monitor>::iterator monit = monitors.begin(); monit != monitors.end(); monit++ )
			if( monit->second.logfile == *it ) logfiles.back().monitors.push_back( monit->second );
	}

	//Begin a watch thread per logfile
	for( std::vector<ctail>::iterator it = logfiles.begin(); it != logfiles.end(); it++ )     	std::thread ( logthread, &*it ).detach();

	//Main loop
	//Handles cleaning of old database entries
	while( true )
	{
		sleep(60);
		//Delete all expired database entries
	}
}
