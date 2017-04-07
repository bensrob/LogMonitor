#ifndef IPADDRESS
	#include <string>
	#include <bitset>

	struct ipaddress
	{
		unsigned int convert( std::string input );
	};

	#define IPADDRESS
#endif
