#include <Windows.h>

class CThreadHeap;
class CUsedMemoryDepositor;

class CThreadHeapWithDepositor
{
public:
	CThreadHeapWithDepositor();
	virtual ~CThreadHeapWithDepositor();

	PVOID Alloc(size_t);
	bool Free(PVOID);
//private:
	
	CThreadHeap *m_pThreadHeap;
	CUsedMemoryDepositor *m_pDepositor;
};
