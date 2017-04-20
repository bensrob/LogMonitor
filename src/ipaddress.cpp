#include "../include/ipaddress.h"

// Convert ip addresses into unsigned int
unsigned int ipaddress::convert( std::string input )
{
	// Find '/' if ip address contains a prefix notation
	int loc = input.find("/");

	// Set default prefix to 32
	int prefix = 32;

	// Create local copy of ip string
	std::string ip = input;

	// If input contains a '/'
	if( loc >= 0 )
	{
		// Pull prefix from input
		prefix	= std::stoi( input.substr( loc+1, input.size()-( loc+1 ) ) );
		// Pull ip address from input
		ip	= input.substr( 0, loc );
	}

	// If prefix is invalid
	if( prefix > 32 || prefix < 0 )	return 0;

	// Array to hold parts of ip address
	char ipsplit[4][4] = {'\0'};

	// Loop through input to split address into 8 bit segments
	int i=0, p=0;
	for( std::string::iterator it = ip.begin(); it!=ip.end(); it++, i++ )
	{
		// If '.' move to next section
		if( *it == '.' )
		{
			i = -1;
			p += 1;
		}
		// Add next number to array
		else
		{
			ipsplit[p][i] = *it;
		}
	}

	// Convert 8 bit segments into single unsigned int
	unsigned int ipint = std::stoi( ipsplit[3] );
	ipint += std::stoi( ipsplit[2] ) * 256;
	ipint += std::stoi( ipsplit[1] ) * ( 256 * 256 );
	ipint += std::stoi( ipsplit[0] ) * ( 256 * 256 * 256 );

	// Create bitmask for prefix
	std::bitset<32> netmask;
	for( int i = 0; i!=prefix; i++)
	{
		netmask.set(31-i);
	}

	// Binary AND ip address and netmask and return
	return (netmask.to_ulong() & ipint);
}
