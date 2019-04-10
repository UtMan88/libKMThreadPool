//////////////////////////////////////////////////////////////////////////
// KMTask.h
//
// Author: Keith Maggio
// Purpose:	Container for task data. Adds ease-of-use when adding 
//			additional functionality, like dependancies and such.
// Free for use and modification.
// Revision 1, July 4th, 2010
//////////////////////////////////////////////////////////////////////////
#ifndef _KM_TASK_H_
#define _KM_TASK_H_

#include "KMUtility.h"
using namespace kmp::threading::utility;

namespace kmp{
namespace threading{

class KMTask
{
private:
	KMTaskFunc		m_task;
	IKMTaskData*	m_data;
public:
	KMTask(KMTaskFunc task, IKMTaskData* data)
	{
		m_task = task;
		m_data = data;
	}

	~KMTask()
	{
		if(m_data!=NULL)
			delete m_data;
		m_data = NULL;
		m_task = NULL;
	}

	KMTaskFunc		GetTask()	{	return m_task;	}
	IKMTaskData*	GetData()	{	return m_data;	}
protected:
};

}}
#endif