/*------------------------*/
/* WARNING NOT THREADSAFE */
/*------------------------*/

#ifndef PCH
	#include <iostream>
	#include <string.h>
#endif

#ifndef MEMMAN
	#define uint unsigned int	//Dont judge me (for alignment, neatness and laziness reasons)
	#define MAX 1024		//Maximum number of ids
	#define TAG 16			//Characters allocated for a tag detailing alloc reason
	namespace Memman{ static std::string loc; }	//Location that allocation was called from

	struct memhead
	{
		uint	id;		//Optional id for what called allocated the memory
		uint	size;		//Size of allocation
		memhead	*prev;		//Pointer to previous head or null for first element
		memhead	*next;		//Pointer to next header or null for last element
	};

	class memman
	{
	public:
		//(Con|De)structor
		inline	memman():	start(0), end(0), nextid(0), alloc(0), decon(0){}
			~memman();

		//Public Functions
			void*	add	( std::size_t, std::string );	//New allocation in tag group
			void	del	( void* );			//Free specified object
		inline 	void	print	();				//Prints current stats
	private:
		//Data
			memhead	*start;			//First header
			memhead	*end;			//Last header
			uint	nextid;			//Next free id number
			uint	size [MAX];		//Current size of allocations per id
			uint	num  [MAX];		//Current number of allocs per id
                        uint    tsize[MAX];             //Total size
                        uint    tnum [MAX];             //Total number of allocs
			char	tag  [MAX][TAG];	//Name specified when recieving an id
			bool	alloc;			//Indicates class is alloc
			bool	decon;			//Indicates deconstruction
	} 	static memman;


	//Inline functions
	inline void memman::print()	{ 	for( uint i = 0; i != nextid; i++ ) //Prints all memory stats
						std::cout << i << "\t" << tag[i] << "\t" << num[i] << "\\" << tnum[i] << "\t" << size[i] << "\\" << tsize[i] << "\n"; }

	//Override global new to use memman, passing infomation about the caller
	inline void* operator new  ( size_t size )     {       return memman.add( size, Memman::loc );         }
	inline void operator delete ( void* todel )    {       memman.del(todel);                              }
	#define new (Memman::loc=__PRETTY_FUNCTION__,0)?0:new

#define MEMMAN
#endif
