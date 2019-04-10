#include "KMThreadPool_Win32.h"
#include"KMThread_Win32.h"
using namespace kmp::threading;

KMThreadpool KMThreadpool::m_instance;

void KMThreadpool::Initialize(unsigned int uiTryMinNumThreads,
				unsigned int uiTryMaxNumThreads)
{
	unsigned int i;

	//Create the threads
	m_vthreads.assign(uiTryMinNumThreads, NULL);

	//Initialize the min number of threads
	for(i = 0; i < uiTryMinNumThreads; ++i)
	{
		m_vthreads[i] = new KMThread();
		m_vthreads[i]->Begin();
		if(m_vthreads[i]->isRunning())
		{
			++m_nactive;
		}
	}

	//Try to initialize the max number of threads. If one fails,
	//we stop.
	for(i = uiTryMinNumThreads; i < uiTryMaxNumThreads; ++i)
	{
		KMThread* trythread = new KMThread();
		trythread->Begin();
		if(trythread->isRunning())
		{
			m_vthreads.push_back(trythread);
			++m_nactive;
		}
		else
		{
			delete trythread;
			break;
		}
	}


}

void KMThreadpool::Shutdown()
{
	KMTask* deltask;
	KMThread* delthread;

	// Stop the delegation of tasks
	if(m_bprocess != false)
	{
		m_bprocess = false;
	}
	//Clear the threads
	while(!m_vthreads.empty())
	{
		delthread = m_vthreads.back();
		m_vthreads.pop_back();
		delthread->End();
		delete delthread;
	}
	//Clear the tasks
	while(!m_qtaskList.empty())//isEmpty())
	{
		//deltask = m_qtaskList.front();
		deltask = m_qtaskList.pop();
		delete deltask;
	}
}

void KMThreadpool::AddTask(KMTaskFunc task, IKMTaskData* data)
{
	KMTask* newTask = new KMTask(task,data);
	m_qtaskList.push(newTask);
}

unsigned int  KMThreadpool::getNumDormantThreads()
{
	unsigned int i, dormant = 0;
	for(i = 0; i < m_vthreads.size(); ++i)
	{
		if(m_vthreads[i]->isRunning() && m_vthreads[i]->isPaused())
		{
			++dormant;
		}
	}

	return dormant;
}

void KMThreadpool::BeginProcessing()
{
	m_bprocess = true;
}

void KMThreadpool::StopProcessing()
{
	m_bprocess = false;
}
