#ifndef PARSER
	#include <iostream>
	#include <vector>
	#include <sstream>

	struct parser
	{
		parser();
		~parser();

		std::vector<std::string> getWords( char *input );
	};

	#define PARSER
#endif
