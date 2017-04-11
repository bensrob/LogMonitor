#include "../include/memman.h"

//Initialise variables
memhead* memman::start		= 0;		//First header
memhead* memman::end		= 0;		//Last header
uint    memman::nextid		= 0;            //Next free id number
uint    memman::size [MAX]	= {0};   	//Current size of allocations per id
uint    memman::num  [MAX]	= {0};  	//Current number of allocs per id
uint    memman::tsize[MAX]	= {0};   	//Total size
uint    memman::tnum [MAX]	= {0};          //Total number of allocs
char    memman::tag  [MAX][TAG]	= {0};         	//Name specified when recieving an id
bool    memman::alloc 		= false;        //Indicates class is alloc
bool    memman::decon		= false;        //Indicates deconstruction

// New allocation
// Allocates memory, assigned correct header options and adds to tracking
// Returns pointer to after header for data
void* memman::add( std::size_t insize, std::string intag )
{
	if( intag.empty() )	intag = "NOT SET";

	// spinlock
	while( alloc == true )	sleep(1);
	alloc = true;

	// Allocate and zero memory
	int fullsize = insize + sizeof(memhead);
	memhead *head = (memhead*) memset( malloc( fullsize ), 0, fullsize );

	// Find if tag exists
	uint id = 0;
	while( id != nextid && intag.compare( 0, TAG-1, tag[id]) ){ id++; }
	if( id == nextid ) nextid++;

	// Configure header
	head->id	= id;
	head->size	= insize;
	head->next	= 0;
	head->prev	= end;

	// Add tracking
	strcpy( tag[id],  intag.substr( 0, TAG-1 ).c_str() );
	end		= head;
        size[id]        += insize;
	tsize[id]	+= insize;
	num[id]		+= 1;
	tnum[id]	+= 1;
	if(!start)	start = head;

	// Update last header
	if(head->prev) head->prev->next = head;

	alloc=false;

	// Return pointer to data location
	return (void*)(head+1);
}

// Free memory
// Frees up allocated memory after updating adjoined headers and tracking infomation
void memman::del ( void* todel )
{
	// Spinlock
	while( decon == true )    sleep(1);
        decon = true;

	// Move pointer onto header
	memhead* head = (memhead*)todel-1;

	// Update adjoined headers
	if( head->prev )	head->prev->next = head->next;
	if( head->next )	head->next->prev = head->prev;

	// Update tracking information
	if( start == head )     start = head->next;
	if( end == head )	end   = head->prev;
	size[head->id]	  	-= head->size;
	num [head->id]	  	-= 1;

	decon = false;

	// Free memory
	free( head );
}

// Destructor
// Calls del(void*) function for all tracked elements to free them all
memman::~memman()
{
	// Start at the first element and loop until no more
	memhead *next = start;
	while( next )
	{
		// Assign next element then call del(void*)
		memhead* cur = next;
		next = next->next;
		del(cur+1);
	}
}
