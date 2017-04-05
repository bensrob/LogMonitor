#include "main.h"
#include "ctail.h"
#include "threads.h"


//Vector of all ctails
std::vector<ctail> logfiles;

//Before exit
void cleanup( int sig )
{
	std::cout << "\nRecieved interupt. Code" << sig << ".\n";
	//Indicate that threads should close
	threadkiller = true;
	//Clear logfiles to call destructors
	logfiles.clear();
	exit(0);
}


int main()
{
	//Catch interupt signal and begin cleanup
	signal(SIGINT, cleanup);

	//List of log files to follow
	std::vector<std::string> loglocs;
	loglocs.push_back("/var/log/syslog");
	loglocs.push_back("/var/log/fail2ban.log");

	//Create new ctail per logfile
	for( std::vector<std::string>::iterator it = loglocs.begin(); it != loglocs.end(); it++ )	logfiles.emplace_back( *it );

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
