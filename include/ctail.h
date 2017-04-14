#ifndef CTAIL
	#include "../include/monitor.h"

	// Size of inofity events
	#define EVENT_SIZE	( sizeof (struct inotify_event) )

	// Size of buffer for tailing files
	#define BUF_LEN		( 1024 * ( EVENT_SIZE + 16 ) )

	// Struct for each logfile
	// Contains all information for logfile + tailing
	// Contains all monitors that use the logfile
	struct ctail
	{
                // Constructors
		ctail(std::string location);
                ctail(const ctail &in);

		// Initialiser
		void init();

		// Destructor
		~ctail();

		// File descriptor
		int fd;

		// Watch descriptor
		int wd;

		// Is the ctail initialised
		bool initialised;

		// Location of logfile
		std::string loc;

		// Ifsteam for logfile
		std::ifstream log;

		// Waits for logfile to update, then returns with a vector<string> of updates
		std::vector<std::string> watch();

		// All of the monitors for this log file
		std::vector<monitor> monitors;
	};

	#define CTAIL
#endif

