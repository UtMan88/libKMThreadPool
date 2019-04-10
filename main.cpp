//////////////////////////////////////////////////////////////////////////
// Main.cpp
//
// Author: Keith Maggio
// Purpose:	Main program entrance.
// Free for use and modification.
// Revision 1, July 4th, 2010
//////////////////////////////////////////////////////////////////////////
#include <ctime>
#include "KMUtility.h"
#include "KMThreadPool_Win32.h"
using kmp::threading::KMThreadpool;
using kmp::threading::utility::IKMTaskData;

// Visual Leak Detector. If you don't have it, comment this line out
// (Or download it - it's free!)
#include <vld.h>

// Time keeping
#include "Timer.h"

#define MAX_TASKS 500 // Change this to modify the number of tasks

//////////////////////////////////////////////////////////////////////////
// This is our sample derived data class.
class SampleTask : public IKMTaskData
{
public:
	int tasknum;
	SampleTask() {}
	SampleTask(int data) { tasknum = data; }
	~SampleTask() {}
};

void Sample1(IKMTaskData* data)
{
	// Once we have the sample data, we cast it
	// To the type we need.
	SampleTask* _data = (SampleTask*)data;
	printf("S%d\n", _data->tasknum);	// When the task started
	for(int i=0;i<200000;++i);
	printf("F%d\n", _data->tasknum);	// When the task finishes
}

void Sample2(IKMTaskData* data)
{
	SampleTask* _data = (SampleTask*)data;
	printf("S%d\n", _data->tasknum);
	for(int i=0;i<5000;++i);
	printf("F%d\n", _data->tasknum);
}
//////////////////////////////////////////////////////////////////////////

int main()
{
	int addTask = 0;
	KMThreadpool* pool = KMThreadpool::getInstance();
	// Initialize the threadpool.
	pool->Initialize(2, 4);
	printf("Thread pool Initialized with %d threads.\n", pool->getActiveThreads());
	system("pause");

	// Add tasks to our threadpool.
	for(int i = 0; i < MAX_TASKS; ++i)
	{
		SampleTask* data = new SampleTask(i);
		if(i%2==0)
			pool->AddTask(Sample1, data);
		else
			pool->AddTask(Sample2, data);
	}

	// See how long it takes to execute
	Timer elapsed;
	pool->BeginProcessing();
	elapsed.Reset();
	while(true)
	{
		// Check to see if all tasks are completed. This is
		// only for this sample program. In others, the
		// pool will be shut down once the program exits.
		if( pool->getActiveThreads()==pool->getNumDormantThreads() && !pool->hasWaitingTasks())
			break;

		// Cut-off in the middle of execution
		if(GetAsyncKeyState(VK_ESCAPE))
			break;
	}

	float imediatefinish = elapsed.GetElapsedTime();
	pool->StopProcessing();
	// Fin
	pool->Shutdown();
	printf("Thread Pool has finished in %f seconds.\n", imediatefinish);
	printf("CPU Time (ExecutionTime/NumberOfThreads+NumberOfProcessors) is %f seconds\n     on a duel-core processor. ",
			(imediatefinish/(pool->getActiveThreads()+2)));
	system("pause");
	return 0;
}