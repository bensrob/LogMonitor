//Threadsafe cout

#ifndef PCH
	#include <iostream>
	#include <mutex>
#endif

#ifndef TOUT
	// Inline mutex
	// Call by 	x = name of mutex
	//		y = command to run inside
	// No trailing semicolon for command consistancy

	// LOCK if mutex already exists in scope
	#ifndef LOCK
	#define LOCK( x, y )	x.lock();               \
	                        y;                      \
        	                x.unlock()
	#endif

	// NEWLOCK to create a new static mutex
	#ifndef NEWLOCK
	#define NEWLOCK( x, y ) static std::mutex x;    \
	                        x.lock();               \
	                        y;                      \
	                        x.unlock()
	#endif


	// Threadsafe (C)Output
	class tout
	{
	public:
	        // Indicated write in progress
	        static std::mutex writelock;

		// Template capture to pass to cout
		// Does NOT work with endl so using defines to switch to '/n'
		// Returns reference to itself so operator << can be chained
		template <typename type>
	        tout operator << ( type i )
		{
	                std::cout << i;
	                return *this;
	        }
	} static tout;

	// Apply lock to tout
	#define tout(x)		LOCK( tout.writelock, tout << x )

	// Define endl as '\n'
	#define QUOTE(x) #x
	#define	endl 	 QUOTE(\n)

	#define TOUT
#endif
