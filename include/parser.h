#ifndef PARSER
	#include <iostream>
	#include <vector>
	#include <sstream>
	#include <map>
	#include <fstream>
	#include "../include/monitor.h"
	#include "../include/ipaddress.h"

	struct parser
	{
		parser();
		~parser();

		std::string section;
		std::map<std::string,monitor> options;

		std::vector<std::string> getWords( char *input );
		void 			 getCommands( std::vector<std::string> words );
		void			 getConfig( std::vector<std::string> files );
		void			 getFile( std::string filename );
		void			 setDefaults();
		void			 checkState();
	};

	#define PARSER
#endif
