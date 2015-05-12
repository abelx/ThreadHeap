#include "CTheadHeap.h"
#include "CMemoryPool.h"
#include <Windows.h>
#include <process.h>
#include "TEST.h"

void HandleAlloc(PVOID ptr)
{
	MyMessageFree(ptr);
}
void HandleFree(CListNode *pn)
{
	MyDoFree(pn->GetPointer());
}

 
DWORD WINAPI WorkThreadProc(PVOID pParam)
{
	MSG msg;
	
	InitHeap();
	
	while(true)
	{
		if(GetMessage(&msg, 0, 0, 0))
		{
			switch(msg.message)
			{
			case MSG_MY_ALLOC:
				HandleAlloc((PVOID)msg.wParam);
				break;
			case MSG_MY_FREE:
				HandleFree((CListNode *)msg.wParam);
				break;
			default:
				break;
			}
		}
	}
	return 0;

}

int main()
{
	TEST_HEAP();
	/*
	tlsIndex = TlsAlloc();
	InitHeap();
	CThreadHeap *tmph = (CThreadHeap *)TlsGetValue(tlsIndex);
	HANDLE hThread;
	DWORD iThreadId;
	iThreadId = GetCurrentThreadId();
	hThread = (HANDLE)_beginthreadex(NULL, 0, (unsigned (__stdcall *)(void *))WorkThreadProc, (void *)0, 0, (unsigned *)&iThreadId);
//	CloseHandle(hThread);


	PVOID test1 = MyAlloc(8);
	Sleep(1000);
	PostThreadMessage(iThreadId, MSG_MY_ALLOC, (WPARAM)test1, 0);
	MSG msg;
	while(true)
	{
		if(GetMessage(&msg, 0, 0, 0))
		{
			switch(msg.message)
			{
			case MSG_MY_ALLOC:
				HandleAlloc((PVOID)msg.wParam);
				break;
			case MSG_MY_FREE:
				HandleFree((CListNode *)msg.wParam);
				tmph->m_Pool->print_pool();
				break;
			default:
				break;
			}
		}
		//break;
	}
	tmph->m_Pool->print_pool();
	*/
	return 0;
	/*
	PVOID test1 = MyAlloc(8);
	MyTrueFree(test1);
	PVOID test2 = MyAlloc(8);
	tmph->m_Pool->print_pool();
	PVOID test3 = MyAlloc(8);
	PVOID t;
		tmph->m_Pool->print_pool();
	for(int i=1; i<8; i++)
	{
		size_t sz = i*8;//rand() % 256;
		t = MyAlloc(sz);
		tmph->m_Pool->print_pool();
		if(rand()%2 == 0 && t != NULL)
		{
			MyTrueFree(t);
			tmph->m_Pool->print_pool();
			
		}
	}
	//MyTrueFree(test1);
	tmph->m_Pool->print_pool();
	MyTrueFree(test3);
	tmph->m_Pool->print_pool();
	MyTrueFree(test2);
	tmph->m_Pool->print_pool();
	MyAlloc(8);
	tmph->m_Pool->print_pool();
	MyAlloc(8);
	tmph->m_Pool->print_pool();
	test2 = MyAlloc(240);
	test1 = MyAlloc(8);
	MyTrueFree(test2);
	MyTrueFree(test1);
	tmph->m_Pool->print_pool();
	DelHeap();
	*/
}
