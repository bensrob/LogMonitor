#ifndef FINDFILES
	#include <string>
	#include <vector>
	#include <dirent.h>

	std::vector<std::string> findfiles( std::string folder = "." );

	#define FINDFILES
#endif
