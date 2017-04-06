#ifndef CONFIG
	#include <vector>
	#include <string>

	struct cfile
	{
		cfile( int n, int l, unsigned char *d)
		{
			this->name 	= n;
			this->len	= l;
			this->data	= new unsigned char [this->len];
			this->data	= d;
			delete d;
		}
		~cfile(){
			delete data;
		}
		unsigned int 	len;
		std::string	name;
		unsigned char 	*data;
	};

	struct configfiles
	{
		std::vector<cfile> cfiles;
		void add( int n, int l, unsigned char *d)
		{
		}
	};

	#define CONFIG
#endif
