#ifndef CTAIL
	#include "../include/monitor.h"

	#define EVENT_SIZE	( sizeof (struct inotify_event) )
	#define BUF_LEN		( 1024 * ( EVENT_SIZE + 16 ) )

	struct ctail
	{
		int fd;
		int wd;
		std::string loc;
		std::ifstream log;
		ctail(const ctail &in);
		ctail(std::string location);
		void init();
		std::vector<std::string> watch();
		std::vector<monitor> monitors;
		~ctail();
	};

	#define CTAIL
#endif

