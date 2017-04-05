#ifndef MONITOR

#include <string>
#include <vector>

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

	std::vector<int>	 ignoreip;	//Ip addresses to ignore.  Only stores
						//network bits to '&' with detected
};

#define MONITOR
#endif
