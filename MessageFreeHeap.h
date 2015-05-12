#include <Windows.h>

namespace MessageFreeHeap
{
	extern DWORD tlsIndex;
	bool InitHeap();
	PVOID MyAlloc(size_t);
	void MyFree(PVOID);
}
