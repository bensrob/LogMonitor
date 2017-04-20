#ifndef PARSER
	#include "../include/monitor.h"
	#include "../include/ipaddress.h"
	#include "../include/findfiles.h"

	// Parse files to extract config
	class parser
	{
	public:
		// (Con|De)structor
		parser();
		~parser();

		// Main function to extract config from all files and return a result
                std::map<std::string,monitor>   getConfig();

	private:
		// Current monitor config is being extracted for
		std::string section;

		// Map of <name,config> to return
		std::map<std::string,monitor> options;

		// Extract all config from file
		void    getFile( std::string filename );

		// Split a string into words
		std::vector<std::string> 	getWords( char *input );

		// Extract config from vector<string> listing a line broken down into words
		void 	getCommands( std::vector<std::string> words );

		// Fill in any missing information using defaults
		void	setDefaults();

		// Check if all required fields are filled
		void	checkState();
	};

	#define PARSER
#endif
