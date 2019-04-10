//////////////////////////////////////////////////////////////////////////
// KMLock.h
//
// Author: Keith Maggio
// Purpose:	Container to interface with CRITICAL_SECTION.
//			Can be used later on to switch between CRITICAL SECTION
//			for Windows, and another critical section-like class
//			for another platform.
// Free for use and modification.
// Revision 1, July 4th, 2010
//////////////////////////////////////////////////////////////////////////
#ifndef _KM_LOCK_H_
#define _KM_LOCK_H_

#define WINDOWS_LEAN_AND_MEAN
#include <Windows.h>

namespace kmp{
namespace threading{

class KMLock
{
private:
	CRITICAL_SECTION m_critsec;
public:
	KMLock()
	{
		::InitializeCriticalSection(&m_critsec);
	}

	~KMLock()
	{
		::DeleteCriticalSection(&m_critsec);
	}

	void Lock()
	{
		::EnterCriticalSection(&m_critsec);
	}

	void Unlock()
	{
		::LeaveCriticalSection(&m_critsec);
	}
protected:
};
}}

#endif