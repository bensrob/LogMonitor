#ifndef CONFIG
	#include <vector>
	#include <string>
	#include <fstream>

	struct cfile
	{
		cfile( std::string n, int l, unsigned char *d)
		{
			this->name 	= n;
			this->len	= l;
			this->data	= new unsigned char [this->len];
			this->data	= d;
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
		void createDefaults()
		{
			for( std::vector<cfile>::iterator it = defaults->begin(); it != defaults->end(); it++)
			{
				std::ofstream output(it->name.c_str());
				if( output.is_open() )
				{
					output.write((char*)it->data, it->len);
					output.close();
				}
			}
		}
	};

	#define CONFIG
#endif
