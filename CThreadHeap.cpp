#include "CTheadHeap.h"
#include "CFreeMemoryKeeper.h"
#include "CUsedMemoryDepositor.h"
#include "CMemoryPool.h"
#include "functions.h"
#include "consts.h"
#include "CMemoryNode.h"
#include "CListNode.h"
#include <Windows.h>

CThreadHeap::CThreadHeap()
{
	
	CListNode *pIniNode;
	m_Pool = new CMemoryPool(&pIniNode, 1024*16);
	
	if(pIniNode != nullptr)
	{
		m_Keeper = new CFreeMemoryKeeper(this, 16, 4);
		m_Keeper->Mount(pIniNode);
	}
}

CThreadHeap::~CThreadHeap()
{
	delete m_Pool;
	delete m_Keeper;
}

CListNode* CThreadHeap::Alloc(size_t sz)
{
	if(sz <= 0)
		return nullptr;

	sz = g_Align(sz, HEAP_MEMORY_UNIT);//对齐
	CListNode* ret = m_Keeper->UMount(sz);
	
	if(ret == nullptr)
		return nullptr;

	CListNode* newp = (CListNode*)(m_Pool->SpliteNode((CMemoryNode*)ret, sz));
	
	if(newp != nullptr)
	{
		m_Keeper->Mount(newp);
	}

	//设置内存块所属线程handle
	((SMemoryNode*)ret)->m_hThread = (int)GetCurrentThreadId();
	return ret;
}

void CThreadHeap::Free(CListNode *pln)
{
	//CListNode *pln = (CListNode*)((BYTE*)ptr - MEMORY_NODE_SIZE);
	
	if(pln->GetRC()!=0)
		return;

	CMemoryNode* mtmp = (CMemoryNode*)pln;
	CMemoryNode* pStart = mtmp;
	CMemoryNode* pEnd = mtmp;
	if(mtmp->GetPreviousPtr()->GetRC() == -1)
	{
		m_Keeper->UMount((CListNode*)(mtmp->GetPreviousPtr()));
		pStart = mtmp->GetPreviousPtr();
	}
	if(mtmp->GetNextPtr()!=nullptr && mtmp->GetNextPtr()->GetRC() == -1)
	{
		pEnd = mtmp->GetNextPtr();
		m_Keeper->UMount((CListNode*)pEnd);
	}
	m_Pool->CombineNode(pStart, pEnd);
	m_Keeper->Mount((CListNode*)pStart);
}





/*
BOOL InitHeap()
{
	CThreadHeap *tmp = new CThreadHeap;
	return TlsSetValue(tlsIndex,tmp);
}

void DelHeap()
{
	CThreadHeap *tmp = (CThreadHeap *)TlsGetValue(tlsIndex);
	delete tmp;
}

PVOID MyAlloc(size_t sz)
{
	CThreadHeap *tmp = (CThreadHeap *)TlsGetValue(tlsIndex);
	return tmp->Alloc(sz);
}

void MyFree(PVOID ptr)
{
	CListNode *tmp = (CListNode *)((BYTE *)ptr - MEMORY_NODE_SIZE);
	tmp->DecRC();
}

void MyTrueFree(PVOID ptr)
{
	CListNode *tmp = (CListNode *)((BYTE *)ptr - MEMORY_NODE_SIZE);
	tmp->DecRC();
	CThreadHeap *pHeap = (CThreadHeap *)TlsGetValue(tlsIndex);
	//pHeap->Free(ptr);
}

void MyDoFree(PVOID ptr)
{
	CThreadHeap *pHeap = (CThreadHeap *)TlsGetValue(tlsIndex);
	//pHeap->Free(ptr);
}


void MyMessageFree(PVOID ptr)
{
	CListNode *tmp = (CListNode *)((BYTE *)ptr - MEMORY_NODE_SIZE);
	tmp->DecRC();
	if(tmp->GetRC() == 0)
	{
		SMemoryNode *del = (SMemoryNode *)tmp;
		DWORD iThreadId = (DWORD)(del->m_hThread);
		if(iThreadId == GetCurrentThreadId())
		{
			CThreadHeap *pHeap = (CThreadHeap *)TlsGetValue(tlsIndex);
			//pHeap->Free(ptr);
		}
		else
		{
			PostThreadMessage(iThreadId, MSG_MY_FREE, (WPARAM)del, 0); 
		}
	}
}*/