#ifndef MONITOR

	// Struct to store all config per monitor
	struct monitor
	{
		std::string 		protocol;	//Protocol to detect.	'Any' for all

		int			port;		//Port to detect.	'0' for all

		int			bantime;	//Length on ban

		int			count;		//Detections before ban

		int			listentime;	//Timeframe for detections

		int			permanent;	//Should ban become permanent. 0 for no
							//'>0' number of bans before permanent

		std::string		logfile;	//Location of logfile

		std::vector<std::string> regex;		//Regex to match

		std::vector<std::string> ignore;	//Regex to ignore

		std::vector<unsigned int> ignoreip;	//Ip addresses to ignore.  Only stores
							//network bits to '&' with detected

		bool			functional;	//Does the monitor have all the settings set correctly

		// Constructor and initialisation
		monitor(): port(0), bantime(0), count(0), listentime(0), permanent(0), functional(false) {}

		// Print all config stored in monitor
		void print();
	};

	#define MONITOR
#endif
