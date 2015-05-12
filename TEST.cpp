#include "CTheadHeap.h"
#include "CListNode.h"
#include "CMemoryPool.h"

CListNode *GetNode(PVOID ptr)
{
	CListNode *pln = (CListNode*)((BYTE*)ptr - MEMORY_NODE_SIZE);
	return pln;
}

void TEST_HEAP()
{
	CThreadHeap TheHeap;
	PVOID p1 = TheHeap.Alloc(3);
	
	TheHeap.m_Pool->print_pool();
	PVOID test = TheHeap.Alloc(8);
	
	TheHeap.m_Pool->print_pool();
	TheHeap.Free(GetNode(test));
	TheHeap.m_Pool->print_pool();

	for(int i=1; i<10; i++)
	{
		size_t sz = i*8;//rand() % 256;
		test = TheHeap.Alloc(sz);
		TheHeap.m_Pool->print_pool();
		if(rand()%2 == 0 && test != NULL)
		{
			TheHeap.Free(GetNode(test));
			TheHeap.m_Pool->print_pool();
			
		}
	}
	TheHeap.Free(GetNode(p1));
	TheHeap.m_Pool->print_pool();
}
