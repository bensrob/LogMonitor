#ifndef IPADDRESS
	// Convert ip addresses into unsigned int
	struct ipaddress
	{
		unsigned int convert( std::string input );
	};

	#define IPADDRESS
#endif
