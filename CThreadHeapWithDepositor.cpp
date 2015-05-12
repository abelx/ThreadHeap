#include "CThreadHeapWithDepositor.h"
#include "CTheadHeap.h"
#include "CUsedMemoryDepositor.h"

CThreadHeapWithDepositor::CThreadHeapWithDepositor()
{
	m_pThreadHeap = new CThreadHeap;
	m_pDepositor = new CUsedMemoryDepositor(m_pThreadHeap,2);
}

CThreadHeapWithDepositor::~CThreadHeapWithDepositor()
{
	delete m_pThreadHeap;
	delete m_pDepositor;
}

PVOID CThreadHeapWithDepositor::Alloc(size_t szTarget)
{
	CListNode *pclnRet = m_pThreadHeap->Alloc(szTarget);
	if(pclnRet == nullptr)
		return nullptr;
	
	m_pDepositor->Clear();	
	
	pclnRet->IncRC();
	m_pDepositor->Mount(pclnRet);

	return pclnRet->GetPointer();

}

bool CThreadHeapWithDepositor::Free(PVOID ptr)
{
	CListNode *pclnDel = (CListNode *)((BYTE *)ptr - MEMORY_NODE_SIZE);
	if(((SMemoryNode*)pclnDel)->m_iRc <= 0)
		return false;
	else
		pclnDel->DecRC();
	return true;
}

