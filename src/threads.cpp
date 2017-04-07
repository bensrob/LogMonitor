#include "../include/threads.h"

//When true threads will stop working and close
bool threadkiller = false;


//Per logfile threads
void logthread( ctail *logfile )
{
	//Loop while close not indicated
	while( !threadkiller )
	{
		//Wait for inotify to indicate a change to the file
		//and recieves vector of discovered logs
		std::vector<std::string> logs = logfile->watch();

		//If not indicated to close
		//Prevents potentially utilising already freed ctails
		if( !threadkiller )
		{
			//For each discovered log
			for(    std::vector<std::string>::iterator it = logs.begin();   \
				it != logs.end();				       \
				it++	    )
			{
				//Output log content
				std::cout << *it << "\n";
			}
		}
	}
}
