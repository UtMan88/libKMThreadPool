//////////////////////////////////////////////////////////////////////////
//	Palpable Aftertaste's Timer Class
//	by Keith Maggio
//	
//	Purpose:	Generates elapsed time and calculates FPS
//////////////////////////////////////////////////////////////////////////

#ifndef _PA_TIMER
#define _PA_TIMER

#include <windows.h>
#include <ctime>

class Timer
{
private:
	LARGE_INTEGER	_start;
	LARGE_INTEGER	_freq;
	
public:
	Timer();
	~Timer();

	float GetElapsedTime();

	//////////////////////////////////////////////////////////////////////////
	//	Reset
	//	Purpose:	Resets the timer. 
	//				Called in a function that updates every frame, reset when necessary.
	//////////////////////////////////////////////////////////////////////////
	void Reset() { QueryPerformanceCounter(&_start); }
	
};

#endif
