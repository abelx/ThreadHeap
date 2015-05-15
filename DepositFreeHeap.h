#include <Windows.h>

namespace DepositFreeHeap
{
	extern DWORD tlsIndex;
	bool InitHeap();
	PVOID MyAlloc(size_t);
	void MyFree(PVOID);
};
