#include "Timer.h"

Timer::Timer()
{
	QueryPerformanceFrequency(&_freq);
}

Timer::~Timer()
{

}


float Timer::GetElapsedTime()
{
	LARGE_INTEGER current;
	QueryPerformanceCounter(&current);

	return float(current.QuadPart - _start.QuadPart) / float(_freq.QuadPart);
} 