#include "CMemoryPool.h"
#include "CListNode.h"
#include "CMemoryNode.h"
#include "CFreeMemoryKeeper.h"
#include <stdlib.h>
#include <malloc.h>
#include "CTheadHeap.h"
#include "functions.h"
#include "consts.h"
#include <iostream>
using namespace std;

CMemoryPool::CMemoryPool(CListNode**ppln, size_t sz)
{
	m_ulSize = sz;
	m_pMemory = malloc(sz);
	CMemoryNode* pm = (CMemoryNode*)m_pMemory;
	pm->Init(sz-MEMORY_NODE_SIZE);
	m_cMemoryList.Insert(nullptr, pm);
	*ppln = (CListNode*)pm;
}

CMemoryPool::~CMemoryPool()
{
	free(m_pMemory);
}

void CMemoryPool::CombineNode(CMemoryNode* pStart, CMemoryNode* pEnd)
{
	if(pStart==nullptr || pEnd==nullptr || pStart==pEnd)
		return;

	size_t ulNewSize = pStart->GetSize();
	CMemoryNode* pTmp = pStart->GetNextPtr();
	while(pTmp != pEnd)
	{
		ulNewSize += pTmp->GetSize() + MEMORY_NODE_SIZE;
		pTmp = pTmp->GetNextPtr();
	}
	ulNewSize += pEnd->GetSize() + MEMORY_NODE_SIZE;
	pStart->SetNextPtr(pEnd->GetNextPtr());
	pStart->SetSize(ulNewSize);
}

//函数内默认sz一定是unit的整数倍
CMemoryNode* CMemoryPool::SpliteNode(CMemoryNode* pSpl,size_t sz)
{
	int ulNewSize = pSpl->GetSize() - sz - MEMORY_NODE_SIZE;
	if(ulNewSize <= 0)
		return nullptr;

	CMemoryNode* pNewNode = (CMemoryNode*)(
		(BYTE*)pSpl + MEMORY_NODE_SIZE + sz);
	pNewNode->Init(ulNewSize, 0);
	pSpl->SetSize(sz);
	m_cMemoryList.Insert(pSpl, pNewNode);
	return pNewNode;
}

void CMemoryPool::print_pool()
{
	SMemoryNode * tmp= (SMemoryNode *)(m_pMemory);
	cout << "ThePool:";
	while(tmp!=nullptr)
	{
		cout <<tmp->m_ulSize << ","<<tmp->m_iRc <<";"; 
		tmp = tmp->m_pNextNodeInMemory;
	}
	cout << endl;
}


