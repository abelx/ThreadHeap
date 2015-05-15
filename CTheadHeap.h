#include <Windows.h>							
class CFreeMemoryKeeper;
class CMemoryPool;
class CListNode;

class CThreadHeap
{
public:
	CThreadHeap();
	virtual ~CThreadHeap();

	CListNode* Alloc(size_t);
	void Free(CListNode*);

//private:
	CFreeMemoryKeeper* m_Keeper;
	CMemoryPool* m_Pool;
};
/*
extern DWORD tlsIndex;

BOOL InitHeap();
PVOID MyAlloc(size_t sz);
void MyFree(PVOID ptr);
void MyTrueFree(PVOID ptr);
void DelHeap();
void MyDoFree(PVOID ptr);
void MyMessageFree(PVOID ptr);
*/