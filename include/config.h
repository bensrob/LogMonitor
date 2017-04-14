#ifndef CONFIG
	// Struct to store default config files
	struct cfile
	{
		// Initialise struct with name, length and data
		cfile( std::string n, unsigned int l, unsigned char *d)
		{
			this->name 	= n;
			this->len	= l;
			this->data	= new unsigned char [this->len];
			for( unsigned int i = 0; i!=this->len; i++ )	this->data[i] = d[i];
		}
		unsigned int 	len;
		std::string	name;
		unsigned char 	*data;

		// Free resources
		~cfile()
		{
			delete this->data;
		}
	};

	// Struct to store default configfiles and create them as needed
	struct config
	{
		std::vector<cfile> *defaults;
		config();
		~config();

		// Create default files
		void createDefaults()
		{
			// For each file in vector
			for( std::vector<cfile>::iterator it = defaults->begin(); it != defaults->end(); it++)
			{
				// Check if file exists
				std::ifstream input(it->name.c_str());
				if( !input.is_open() )
				{
					// If it does not create and open it for output
					std::ofstream output(it->name.c_str());
					if( output.is_open() )
					{
						// If open write data to file
						output.write((char*)it->data, it->len);
						output.close();
					}
				}
				// If file exists close handle and do not overwrite
				else input.close();
			}
		}
	};

	#define CONFIG
#endif
