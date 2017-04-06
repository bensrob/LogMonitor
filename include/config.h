#ifndef CONFIG
	#include <vector>
	#include <string>

	struct cfile
	{
		cfile( std::string n, int l, unsigned char *d)
		{
			this->name 	= n;
			this->len	= l;
			this->data	= new unsigned char [this->len];
			this->data	= d;
			delete d;
		}
		~cfile()
		{
			delete data;
		}
		unsigned int 	len;
		std::string	name;
		unsigned char 	*data;
	};

	struct config
	{
		std::vector<cfile> *defaults;
		config();
		~config();
	};

	#define CONFIG
#endif
