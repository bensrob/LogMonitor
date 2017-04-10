#include "../include/memman.h"

//New allocation
//Allocates memory, assigned correct header options and adds to tracking
//Returns pointer to after header for data
void* memman::add( std::size_t size, std::string intag )
{
	while( this->alloc == true )	sleep(1);
	this->alloc = true;

	std::cout << "ALLOC!\t" << intag << std::endl;
	//Allocate and zero memory
	int fullsize = size + sizeof(memhead);
	memhead *head = (memhead*) memset( malloc( fullsize ), 0, fullsize );

	//Find if tag exists
	uint id = 0;
	while( id != this->nextid && intag.compare( 0, TAG-1, tag[id]) ){ id++; }
	if( id == this->nextid ) nextid++;

	//Configure header
	head->id	= id;
	head->size	= size;
	head->next	= 0;
	head->prev	= this->end;

	//Add tracking
	strcpy( this->tag[id],  intag.substr( 0, TAG-1 ).c_str() );
	this->end	= head;
	this->size[id]	+= size;
	this->tsize[id]	+= size;
	this->num[id]	+= 1;
	this->tnum[id]	+= 1;
	if(!this->start)this->start = head;

	//Update last header
	if(head->prev) head->prev->next = head;

	this->alloc=false;

	//Return pointer to data location
	return (void*)(head+1);
}

//Free memory
//Frees up allocated memory after updating adjoined headers and tracking infomation
void memman::del ( void* todel )
{
	while( this->decon == true )    sleep(1);
        this->decon = true;

	std::cout << "DEALLOC!\t" << std::endl;
	//Move pointer onto header
	memhead* head = (memhead*)todel-1;

	//Update adjoined headers
	if( head->prev )	head->prev->next = head->next;
	if( head->next )	head->next->prev = head->prev;

	//Update tracking information
	if( this->start == head ) this->start = head->next;
	if( this->end == head )	  this->end   = head->prev;
	this->size[head->id]	  -= head->size;
	this->num [head->id]	  -= 1;

	this->decon = false;

	//Free memory
	free( head );
}

//Destructor
//Calls del(void*) function for all tracked elements to free them all
memman::~memman()
{
	//Start at the first element and loop until no more
	memhead *next = this->start;
	while( next )
	{
		//Assign next element then call del(void*)
		memhead* cur = next;
		next = next->next;
		this->del(cur+1);
	}
}
