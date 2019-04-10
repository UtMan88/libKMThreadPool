#include "KMThread_Win32.h"
using namespace kmp::threading;

KMThread::KMThread()
{
	m_hthread = NULL;

	m_ptask = NULL;
	m_pthreadpool = NULL;

	m_brunning = false;
	m_uithreadID = 0;
	m_dwexit = 0;
}

KMThread::~KMThread()
{
	End();
}

void KMThread::SetTask(KMTask* task)
{
	m_ptask = task;
}

void KMThread::Begin()
{
	// Set our thread pool
	m_pthreadpool = KMThreadpool::getInstance();
#if defined( _WIN32 )
	// Start the thread.
	m_hthread = (HANDLE)_beginthreadex( NULL,
		0,
		&cThreadProc,
		(void*)this,
		0,
		&m_uithreadID );

	m_brunning = true;
	if( m_hthread == NULL )
	{
		// You can add extra error-handling here.
		m_brunning = false;
	}
#endif /* defined( _WIN32 ) */
}

void KMThread::End()
{
#if defined( _WIN32 )
	if( m_hthread != NULL )
	{
		m_brunning = false;
		WaitForSingleObject( m_hthread, INFINITE );
		DWORD ExitCode;
		GetExitCodeThread( m_hthread, &ExitCode );
		m_dwexit = ExitCode;
		CloseHandle( m_hthread );
		m_hthread = NULL;
	}
#endif /* defined( _WIN32 ) */
}

DWORD KMThread::ThreadProc()
{
	m_ptask = NULL;

	// The main thread-loop. As long as this loop
	// is running, the thread stays alive.
	while(m_brunning)
	{

		Sleep(1);

		// The thread pauses when it finishes a task.
		// Adding a task resumes it.
		if(m_ptask != NULL)
		{
			m_lock.Lock();
			{
				KMTaskFunc task = m_ptask->GetTask();
				IKMTaskData* data = m_ptask->GetData();
				// Run the actual task
				if(task != NULL && data != NULL)
				{
					task(data);
				}
				// Task is complete.
				m_bpaused = true;
				delete m_ptask;
				m_ptask = NULL;
			}
			m_lock.Unlock();
		}
		
		// If we're finished with our task, grab a new one.
		if(/*m_bpaused == true && */m_ptask == NULL &&
			m_pthreadpool->IsProcessing() == true)
		{
			m_ptask = m_pthreadpool->m_qtaskList.pop();
		}
	}

	return 0;
}