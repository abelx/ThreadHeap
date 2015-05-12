#include "CTheadHeap.h"
#include "CListNode.h"
#include "CMemoryPool.h"
#include "TEST.h"
#include "CThreadHeapWithDepositor.h"
#include <iostream>
using namespace std;

CListNode *GetNode(PVOID ptr)
{
	CListNode *pln = (CListNode*)((BYTE*)ptr - MEMORY_NODE_SIZE);
	return pln;
}

void TEST_HEAP()
{
	cout << "--------------------Heap-test---------------" << endl;
	CThreadHeap TheHeap;
	CListNode* p1 = TheHeap.Alloc(3);
	
	TheHeap.m_Pool->print_pool();
	CListNode* test = TheHeap.Alloc(8);
	
	TheHeap.m_Pool->print_pool();
	TheHeap.Free(test);
	TheHeap.m_Pool->print_pool();

	for(int i=1; i<10; i++)
	{
		size_t sz = i*8;//rand() % 256;
		test = TheHeap.Alloc(sz);
		TheHeap.m_Pool->print_pool();
		if(rand()%2 == 0 && test != NULL)
		{
			TheHeap.Free(test);
			TheHeap.m_Pool->print_pool();
			
		}
	}
	TheHeap.Free(p1);
	TheHeap.m_Pool->print_pool();
	cout << "------------------Heap-test-end--------------------" << endl;
}

void TEST_HEAPWITHDEPOSITOR()
{
	cout << "------------------Heap-test--------------------" << endl;
	CThreadHeapWithDepositor TheHeap;
	PVOID p1 = TheHeap.Alloc(3);
	
	TheHeap.m_pThreadHeap->m_Pool->print_pool();
	PVOID test = TheHeap.Alloc(8);
	
	TheHeap.m_pThreadHeap->m_Pool->print_pool();
	TheHeap.Free(test);
	TheHeap.m_pThreadHeap->m_Pool->print_pool();

	for(int i=1; i<20; i++)
	{
		size_t sz = i*8;//rand() % 256;
		test = TheHeap.Alloc(sz);
		TheHeap.m_pThreadHeap->m_Pool->print_pool();
		if(rand()%2 == 0 && test != NULL)
		{
			TheHeap.Free(test);
			TheHeap.m_pThreadHeap->m_Pool->print_pool();
			
		}
	}
	TheHeap.Free(p1);
	TheHeap.m_pThreadHeap->m_Pool->print_pool();
cout << "------------------Heap-test-end--------------------" << endl;
}

