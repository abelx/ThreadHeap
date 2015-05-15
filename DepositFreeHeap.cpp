#include "DepositFreeHeap.h"
#include "CThreadHeapWithDepositor.h"

namespace DepositFreeHeap
{
	DWORD tlsIndex;
	bool InitHeap()
	{
		CThreadHeapWithDepositor *TheHeap = new CThreadHeapWithDepositor;
		return TlsSetValue(tlsIndex, TheHeap);
	}

	PVOID MyAlloc(size_t sz)
	{
		CThreadHeapWithDepositor *tmp = (CThreadHeapWithDepositor *)TlsGetValue(tlsIndex);
		return tmp->Alloc(sz);
	}

	void MyFree(PVOID ptr)
	{
		CThreadHeapWithDepositor *tmp = (CThreadHeapWithDepositor *)TlsGetValue(tlsIndex);
		tmp->Free(ptr);
	}
}
