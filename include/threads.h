#ifndef THREADS
	#include <thread>
	#include <string>
	#include <vector>
	#include <iostream>
	#include "ctail.h"

	//Flag to indicate threads should close
	extern bool threadkiller;
	//Main thread function
	void logthread( ctail *logfile );

	#define THREADS
#endif