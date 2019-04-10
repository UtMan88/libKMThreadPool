//////////////////////////////////////////////////////////////////////////
// KMUtility.h
//
// Author: Keith Maggio
// Purpose:	Serves as a namespace to hold smaller data structures.
// Free for use and modification.
// Revision 1, July 4th, 2010
//////////////////////////////////////////////////////////////////////////
#ifndef KM_UTILITY_H_
#define KM_UTILITY_H_

namespace kmp{
namespace threading{
namespace utility
{
	//Class Interfaces
	class IKMTaskData 
	{
	public:
		IKMTaskData() {}
		IKMTaskData(const IKMTaskData&) {}
		IKMTaskData& operator = (const IKMTaskData&) {}
		virtual ~IKMTaskData() = 0 {};
	};

	//Type Definitions
	typedef void (*KMTaskFunc)(IKMTaskData*);

}
}}
#endif
