//////////////////////////////////////////////////////////////////////////
// KMThread_Win32.h
//
// Author: Keith Maggio
// Purpose:	Container for all thread-based actions
// Free for use and modification.
// Revision 1, September 5th, 2010
//////////////////////////////////////////////////////////////////////////
#ifndef KM_THREAD_H_
#define KM_THREAD_H_

#define WINDOWS_LEAN_AND_MEAN
#include <windows.h>
#include<process.h>

#include<iostream>
using std::cout;

#include"KMThreadPool_Win32.h"
#include"KMTask.h"
#include"KMLock.h"
#include"KMUtility.h"
using namespace kmp::threading;
using namespace kmp::threading::utility;

namespace kmp{
namespace threading{

class KMThread
{
private:
	//Nested Classes
	//SpinLock
	
//private:
	KMThreadpool*		m_pthreadpool;

	HANDLE				m_hthread;
	KMLock				m_lock;
	KMTask*				m_ptask;

	bool				m_brunning;
	bool				m_bpaused;
	unsigned int		m_uithreadID;
	DWORD				m_dwexit;

public:
	bool			isRunning()		{	return m_brunning;		}
	bool			isPaused()		{	return m_bpaused;		}
	unsigned int	getThreadID()	{	return m_uithreadID;	}
	DWORD			getExitCode()	{	return m_dwexit;		}
	
	void			Lock()			{	m_lock.Lock();			}
	void			Unlock()		{	m_lock.Unlock();		}

	void			Pause()			{	m_bpaused = true;		}
	void			Resume()		{	m_bpaused = false;		}

	KMThread();
	~KMThread();
	void SetTask(KMTask* task);
	void Begin();
	void End();
	DWORD ThreadProc();
protected:
	static unsigned __stdcall cThreadProc(LPVOID _pThis)
	{
		return ((KMThread*)_pThis)->ThreadProc();
	}
};
}}
#endif