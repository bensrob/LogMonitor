#include "../include/ctail.h"

// Construct ctail from string and call init()
ctail::ctail(std::string location)
{
	this->loc = location;
	this->init();
}

// Construct ctail from ctail reference
ctail::ctail(const ctail &in)
{
	this->loc = in.loc;
	this->init();
}

// Initialise ctail
void ctail::init()
{
	// Reset initialised flag
	this->initialised = false;

	// Open logfile
	this->log.open(this->loc);

	// If logfile is open
	if( this->log.is_open() )
	{
		//Move to end of logfile
		this->log.seekg(0,std::ios_base::end);

		// If seek worked correctly
		if( this->log.good() )
		{
			// Initialise file descriptor for inotify
			this->fd = inotify_init();

			// If file descriptor is initalised
			if( fd >= 0 )
			{
				// Add a watch on logfile
				this->wd = inotify_add_watch( fd, this->loc.c_str(), IN_MODIFY );

				// If watch created successfully
				if( wd >=0 )	this->initialised = true;
				else
				{
					close( this->fd );
                			this->log.close();
				}
			}
			else this->log.close();
		}
		else this->log.close();
	}

	// If there was an error during initalisation
	if( this->initialised == false )	tout( "Error reading " << loc << endl );
}

// Wait for change to logfile, and return a vector of new lines
std::vector<std::string> ctail::watch()
{
	// Initialise buffer
	std::vector<std::string> returnbuffer;
	char buffer[BUF_LEN];

	// Wait for new lines
	int length = read( this->fd, buffer, BUF_LEN );

	// If there are file changes
	if( length >= 0 )
	{
		// Clear error bits from input stream
		this->log.clear();

		// While end of file has not been reached
		while( !this->log.eof() )
		{
			// Get line from logfile
			std::string line;
			getline(this->log,line);

			// If line is not empty add to return vector
			if( line.length() > 0 )	returnbuffer.push_back(line);
		}
	}
	// Return vector of new lines
	return returnbuffer;
}

// Destructor
ctail::~ctail(){
	// If ctail is initialised
	if( this->initialised )
	{
		// Remove watch
		inotify_rm_watch( this->fd, this->wd );

		// Remove file descriptor
		close( this->fd );

		// Close input stream
		this->log.close();
	}
}

