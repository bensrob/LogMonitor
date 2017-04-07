#ifndef CONFIG
	#include <vector>
	#include <string>
	#include <fstream>

	struct cfile
	{
		cfile( std::string n, unsigned int l, unsigned char *d)
		{
			this->name 	= n;
			this->len	= l;
			this->data	= new unsigned char [this->len];
			for( unsigned int i = 0; i!=this->len; i++ )
			{
				this->data[i] = d[i];
			}
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
				std::ifstream input(it->name.c_str());
				if( !input.is_open() )
				{
					std::ofstream output(it->name.c_str());
					if( output.is_open() )
					{
						output.write((char*)it->data, it->len);
						output.close();
					}
				}
				else input.close();
			}
		}
	};

	#define CONFIG
#endif
