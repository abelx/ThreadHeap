#include "CTheadHeap.h"
#include "CListNode.h"
#include "CMemoryPool.h"
#include "TEST.h"
#include "CThreadHeapWithDepositor.h"
#include <iostream>
#include "MessageFreeHeap.h"
#include "DepositFreeHeap.h"
#include <process.h>

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
	int iSz;
	for(int i=0; i<20; i++)
	{
		iSz = rand() % 512;
		test = TheHeap.Alloc(iSz);
		TheHeap.Free(test);
		cout << "alloc" << iSz << ":";
		TheHeap.m_Pool->print_pool();
	}
	TheHeap.Free(p1);
	TheHeap.m_Pool->print_pool();
	cout << "------------------Heap-test-end--------------------" << endl;
}

void TEST_HEAPWITHDEPOSITOR()
{
	cout << "------------------Heap-test--------------------" << endl;
	CThreadHeapWithDepositor TheHeap;
	PVOID test;
	for(int i=1; i<20; i++)
	{
		size_t sz = rand() % 512;
		test = TheHeap.Alloc(sz);
		TheHeap.m_pThreadHeap->m_Pool->print_pool();
		if(rand()%2 == 0 && test != NULL)
		{
			TheHeap.Free(test);
			TheHeap.m_pThreadHeap->m_Pool->print_pool();
			
		}
	}
	
	TheHeap.m_pThreadHeap->m_Pool->print_pool();
cout << "------------------Heap-test-end--------------------" << endl;
}

DWORD WINAPI MessageWorkThreadProc(PVOID pParam)
{
	using namespace MessageFreeHeap;

	MSG msg;
	
	InitHeap();
	
	while(true)
	{
		if(GetMessage(&msg, 0, 0, 0))
		{
			switch(msg.message)
			{
			case MSG_MY_ALLOC:
				if(rand()%2==0)
					MyFree((PVOID)msg.wParam);
				break;
			case MSG_MY_FREE:
				MyFree((PVOID)msg.wParam);
				break;
			default:
				break;
			}
		}
	}
	return 0;

}

DWORD WINAPI DepositWorkThreadProc(PVOID pParam)
{
	using namespace DepositFreeHeap;
	DWORD64 *freeTime = (DWORD64 *)pParam;
	*freeTime = 0;
	MSG msg;
	
	InitHeap();
	
	while(true)
	{
		if(GetMessage(&msg, 0, 0, 0))
		{
			switch(msg.message)
			{
			case MSG_MY_ALLOC:
				*freeTime = GetTimeTick() - *freeTime;
				MyFree((PVOID)msg.wParam);
				*freeTime = GetTimeTick() - *freeTime;
				break;
			default:
				break;
			}
		}
	}
	return 0;

}

void TEST_THREAD_MESSAGEHEAP()
{
	cout << "--------------------MESSAGE-TEST------------------" << endl
		<< "Memory pool message:" << endl;
	using namespace MessageFreeHeap;

	tlsIndex = TlsAlloc();
	InitHeap();
	HANDLE hThread;
	DWORD iThreadId;
	hThread = (HANDLE) _beginthreadex(NULL, 0, (unsigned (__stdcall *)(void *))MessageWorkThreadProc, (void *)0, 0, (unsigned *)&iThreadId);
	CThreadHeap *tmp = (CThreadHeap *)TlsGetValue(tlsIndex);
	PVOID test;
	int iSz;
	Sleep(100);
	
	for(int i=0; i<20; i++)
	{
		iSz = rand() % 512;
		test = MyAlloc(iSz);
		cout << "alloc" << iSz << ":";
		tmp->m_Pool->print_pool();
		PostThreadMessage(iThreadId, MSG_MY_ALLOC, (WPARAM)test, 0);
	}

	MSG msg;
	while(true)
	{
		if(GetMessage(&msg, 0, 0, 0))
		{
			switch(msg.message)
			{
			case MSG_MY_ALLOC:
				break;
			case MSG_MY_FREE:
				MyFree((PVOID)msg.wParam);
				tmp->m_Pool->print_pool();
				break;
			default:
				break;
			}
		}
	}
}

void TEST_THREAD_DEPOSITHEAP()
{
	DWORD64 initTime = 0, runTime = 0, allocTime = 0, freeTime = 0;
	cout << "---------------------DEPOSIT-TEST--------------------" << endl;
	using namespace DepositFreeHeap;
	runTime = GetTimeTick();
	
	tlsIndex = TlsAlloc();
	initTime = GetTimeTick();
	InitHeap();
	initTime = GetTimeTick() - initTime;
	HANDLE hThread;
	DWORD iThreadId;
	//hThread = (HANDLE) _beginthreadex(NULL, 0, (unsigned (__stdcall *)(void *))DepositWorkThreadProc, (void *)&freeTime, 0, (unsigned *)&iThreadId);
	CThreadHeap *tmp = ((CThreadHeapWithDepositor *)TlsGetValue(tlsIndex))->m_pThreadHeap;
	cout << "init:";
	tmp->m_Pool->print_pool();
	PVOID test;
	int iSz;
	//Sleep(100);
	
	for(int i=0; i<20; i++)
	{
		iSz = rand() % 512;
		allocTime = GetTimeTick() - allocTime;
		test = MyAlloc(iSz);
		allocTime = GetTimeTick() - allocTime;
		cout << "alloc" << iSz << ":";
		tmp->m_Pool->print_pool();
		MyFree(test);
		//PostThreadMessage(iThreadId, MSG_MY_ALLOC, (WPARAM)test, 0);
	}
	runTime = GetTimeTick() - runTime;
	cout << "------------------END------------------" << endl;
	cout << "time(cpu cycles):" << endl
		<< "init time:" << initTime << endl
		<< "alloc time:" << allocTime << endl
		<< "free time:" << freeTime << endl
		<< "run time:" << runTime << endl;
}