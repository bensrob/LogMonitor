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
//	namespace Memman{ static std::string loc; }	//Location that allocation was called from

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
		inline	memman(){}
			~memman();

		//Public Functions
		static	void*	add	( std::size_t, char* );	//New allocation in tag group
		static	void	del	( void* );			//Free specified object
		inline 	void	print	();				//Prints current stats
		static  char*	loc;                	//Location allocation was called from
		inline	void	lock();
		inline  void	unlock();
	private:
		//Data
		static	memhead	*start;			//First header
		static	memhead	*end;			//Last header
		static	uint	nextid;			//Next free id number
		static	uint	size [MAX];		//Current size of allocations per id
		static	uint	num  [MAX];		//Current number of allocs per id
                static  uint    tsize[MAX];             //Total size
                static  uint    tnum [MAX];             //Total number of allocs
		static	char	tag  [MAX][TAG];	//Name specified when recieving an id
		static  std::mutex rwlock;              //Locked on read/write operations
	} static memman;


	//Inline functions
	inline void memman::print()
	{
		for( uint i = 0; i != nextid; i++ )	//Prints all memory stats
		{
			tout( i << "\t" << tag[i] << "\t" << num[i] << "\\" << tnum[i] << "\t" << size[i] 	\
				<< "\\" << tsize[i] << "\n");
		}
	}
	inline void memman::lock(){	rwlock.lock();		}
        inline void memman::unlock(){	rwlock.unlock();	}

	// Override global new to use memman, passing infomation about the caller
	inline void* operator new  ( size_t size  )	{       return memman.add( size, memman.loc );           }
	inline void operator delete ( void* todel )	{       memman.del(todel);                               }
	#define new (memman.lock(),memman.loc=(char*)__PRETTY_FUNCTION__,0)?0:new

#define MEMMAN
#endif

