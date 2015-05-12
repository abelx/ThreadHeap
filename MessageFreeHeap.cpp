#include "MessageFreeHeap.h"
#include "CTheadHeap.h"
#include "SMemoryNode.h"
#include "CListNode.h"

namespace MessageFreeHeap
{
	DWORD tlsIndex;
	bool InitHeap()
	{
		CThreadHeap *TheHeap = new CThreadHeap;
		return TlsSetValue(tlsIndex,TheHeap);
	}

	PVOID MyAlloc(size_t sz)
	{
		CThreadHeap *tmp = (CThreadHeap *)TlsGetValue(tlsIndex);
		return tmp->Alloc(sz)->GetPointer();
	}

	void MyFree(PVOID ptr)
	{
		SMemoryNode *tmp = (SMemoryNode *)((BYTE *)ptr - MEMORY_NODE_SIZE);
		DWORD iThreadId = tmp->m_hThread;
		if(iThreadId != GetCurrentThreadId())
		{
			PostThreadMessage(iThreadId, MSG_MY_FREE, (WPARAM)ptr, 0);	
		}
		else
		{
			CThreadHeap *TheHeap = (CThreadHeap *)TlsGetValue(tlsIndex);
			TheHeap->Free((CListNode *)tmp);
		}
	}
}
