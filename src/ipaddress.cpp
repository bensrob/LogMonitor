#include "../include/ipaddress.h"

unsigned int ipaddress::convert( std::string input )
{
	int loc = input.find("/");
	int prefix = 32;
	std::string ip = input;

	if( loc >= 0 )
	{
		prefix	= std::stoi( input.substr( loc+1, input.size()-( loc+1 ) ) );
		ip	= input.substr( 0, loc );
	}

	if( prefix > 32 || prefix < 0 )	return 0;

	char ipsplit[4][4] = {'\0'};
	int i=0, p=0;

	for( std::string::iterator it = ip.begin(); it!=ip.end(); it++, i++ )
	{
		if( *it == '.' )
		{
			i = -1;
			p += 1;
		}
		else
		{
			ipsplit[p][i] = *it;
		}
	}

	unsigned int ipint = std::stoi( ipsplit[3] );
	ipint += std::stoi( ipsplit[2] ) * 256;
	ipint += std::stoi( ipsplit[1] ) * ( 256 * 256 );
	ipint += std::stoi( ipsplit[0] ) * ( 256 * 256 * 256 );

	std::bitset<32> netmask;
	for( int i = 0; i!=prefix; i++)
	{
		netmask.set(31-i);
	}

	return (netmask.to_ulong() & ipint);
}
