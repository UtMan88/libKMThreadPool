//////////////////////////////////////////////////////////////////////////
// KMThreadPool_Win32.h
//
// Author: Keith Maggio
// Purpose:	Our Threadpool Singleton class.
// Free for use and modification.
// Revision 2, September 6th, 2010
//////////////////////////////////////////////////////////////////////////
#ifndef KM_THREADPOOL_H_
#define KM_THREADPOOL_H_

#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>

#include<iostream>
using std::cout;

#include<queue>
#include<vector>
using std::queue;
using std::vector;

#include"KMTask.h"
#include"KMUtility.h"
//#include"KMLocklessQueue.h"
#include "KMQueue.h"
using namespace kmp::threading::utility;
using namespace kmp::threading::algorithms;

namespace kmp{
namespace threading{

class KMThread;

class KMThreadpool
{
	//Nested Classes
	
private:
	//queue<KMTask*>		m_qtaskList;
	//KMLocklessQueue<KMTask*> m_qtaskList;
	KMQueue<KMTask*>	m_qtaskList;
	vector<KMThread*>	m_vthreads;
	unsigned int		m_nactive;
	unsigned int		m_ndormant;

	volatile bool m_bprocess;

	// Friend to the threads so we can access the tasks directly.
	friend class KMThread;

	//Singleton
	static KMThreadpool m_instance;
	KMThreadpool()
	{
		//KMTask* dummy = new KMTask(NULL, NULL);
		//m_qtaskList = KMLocklessQueue<KMTask*>(dummy);
		m_bprocess = false;
	}
	KMThreadpool(const KMThreadpool&);
	KMThreadpool& operator = (const KMThreadpool&);
	~KMThreadpool()
	{
		Shutdown();
	}
public:

	static KMThreadpool* getInstance()   {	return &m_instance;			}
	unsigned int  getActiveThreads()	 {	return m_nactive;			}
	bool          hasWaitingTasks()		 {	return !m_qtaskList.empty();}
	unsigned int  getNumDormantThreads();
	bool		  IsProcessing()		 {	return m_bprocess;			}
	//size_t  getNumQueuedTasks()			 {	return m_qtaskList.size();	}

	void Initialize(unsigned int uiTryMinNumThreads,
					unsigned int uiTryMaxNumThreads);

	void Shutdown();
	void AddTask(KMTaskFunc task, IKMTaskData* data);

	void BeginProcessing();
	void StopProcessing();

protected:
};
}}

#endif