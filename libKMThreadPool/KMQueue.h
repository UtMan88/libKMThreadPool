//////////////////////////////////////////////////////////////////////////
// KMThreadPool_Win32.h
//
// Author: Keith Maggio
// Purpose:	Our Threadpool Singleton class.
// Free for use and modification.
// Revision 1, September 5th, 2010
//////////////////////////////////////////////////////////////////////////
#ifndef _KM_QUEUE_H_
#define _KM_QUEUE_H_

#include "KMLock.h"
using namespace kmp::threading;

namespace kmp{ 
namespace threading{ 
namespace algorithms{

	// Thread-Safe Two-Lock Queue
	// Based on the algorithm presented by Maged M. Michael & Michael L. Scott
	// http://www.cs.rochester.edu/u/scott/papers/1996_PODC_queues.pdf
	template<typename TYPE>
	class KMQueue
	{
	private:
		struct tNode
		{
			TYPE element;
			tNode* next;

			tNode(TYPE _elem, tNode* _next) : element(_elem), next(_next)
			{}
			tNode(TYPE _elem) : element(_elem), next(NULL)
			{}
		};

		// Members
		tNode* m_head;	// The head acts as a dummy/invalidated pointer. When an item is the head,
						// then it's scheduled for deletion on the next pop (if it's not the last node
						// in the queue).
		tNode* m_tail;
		KMLock m_hLock;
		KMLock m_tLock;

		// Deactivated Functions
		KMQueue(KMQueue&)
		{}

		KMQueue& operator = (KMQueue&)
		{}


	public:
		KMQueue()
		{
			tNode* dummy = new tNode(NULL, NULL);
 			m_head = m_tail = dummy;
		}

		~KMQueue()
		{
			while(pop());
			delete m_head;
		}

		bool empty()
		{
			if(m_head->next != NULL)
				return false;
			return true;
		}

		void push(TYPE item)
		{
			tNode* node = new tNode(item);
			m_tLock.Lock();
			{
				m_tail->next = node;
				m_tail = node;
			}
			m_tLock.Unlock();
		}

		TYPE pop()
		{
			tNode* node;
			TYPE value;
			m_hLock.Lock();
			{
				node = m_head;
				tNode* newHead = node->next;
				if(newHead == NULL)
				{
					// If only the head is left, then the queue is empty
					// (Remember, the m_head is considered invalidated)
					m_hLock.Unlock();
					return NULL;
				}
				value = newHead->element;
				m_head = newHead;
			}
			m_hLock.Unlock();
			delete node;
			return value;

		}

	};
}}}
#endif