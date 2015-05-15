#include "CFreeMemoryKeeper.h"
#include "CNodeList.h"
#include "CFreeNodeTree.h"
#include "CListNode.h"
#include "CMemoryNode.h"
#include "consts.h"

CFreeMemoryKeeper::CFreeMemoryKeeper(CThreadHeap* pth, int ln, int tn)
	:m_pHeap(pth), m_iListNumber(ln), m_iTreeNumber(tn)
{
	m_aFreeList = new CNodeList<CListNode>[ln];
	m_aFreeTree = new CFreeNodeTree[tn];
}

CFreeMemoryKeeper::~CFreeMemoryKeeper()
{
	delete[] m_aFreeList;
	delete[] m_aFreeTree;
}

void CFreeMemoryKeeper::Mount(CListNode* pln)
{
	size_t ulLnSize = pln->GetSize();
	
	if(ulLnSize < 0)
		return;
	
	pln->DecRC();
	
	if(ulLnSize <= HEAP_MEMORY_UNIT * m_iListNumber)
	{/*
		int iListKey = __getListKeyByMap(ulLnSize / HEAP_MEMORY_UNIT);
		if(iListKey>=0 && iListKey<m_iListNumber)
		{

		}*/
		int iListKey = (ulLnSize-1) / HEAP_MEMORY_UNIT;
		m_aFreeList[iListKey].Insert(nullptr,pln);
		__setListMap(iListKey);
	}
	else
	{
		int iTreeKey = (ulLnSize - HEAP_MEMORY_UNIT * m_iListNumber - 1) / m_TREE_SIZE;
		if(iTreeKey >= m_iTreeNumber)
			iTreeKey = m_iTreeNumber - 1;
		 m_aFreeTree[iTreeKey].Insert(pln);
	}
}

void CFreeMemoryKeeper::UMount(CListNode* pln)
{
	size_t ulLnSize = pln->GetSize();
	
	if(ulLnSize < 0)
		return;
	
	pln->IncRC();
	
	if(ulLnSize <= HEAP_MEMORY_UNIT * m_iListNumber)
	{
		int iListKey = (ulLnSize-1) / HEAP_MEMORY_UNIT;
		m_aFreeList[iListKey].Delete(pln);
		__setListMap(iListKey);
	}
	else
	{
		int iTreeKey = (ulLnSize - HEAP_MEMORY_UNIT * m_iListNumber - 1) / m_TREE_SIZE;
		if(iTreeKey >= m_iTreeNumber)
			iTreeKey = m_iTreeNumber - 1;
		m_aFreeTree[iTreeKey].Delete(pln);
	}

}

//认为sz已经做了对齐
CListNode* CFreeMemoryKeeper::UMount(size_t sz)
{
	int iKey = __getListKeyByMap(sz);
	
	if(iKey < 0)
		return nullptr;
	
	if(iKey < m_iListNumber)
	{
		CListNode* ret = m_aFreeList[iKey].Delete(nullptr);
		ret->IncRC();
		__setListMap(iKey);
		return ret;
	}

	if(iKey >= m_iListNumber)
	{
		CListNode* ret = m_aFreeTree[iKey-m_iListNumber].Delete(sz);
		ret->IncRC();
		__setListMap(iKey);
		return ret;

	}


	if(sz <= HEAP_MEMORY_UNIT * m_iListNumber)
	{
		int iListKey = (sz-1) / HEAP_MEMORY_UNIT;
		iListKey = __getListKeyByMap(iListKey);
		if(iListKey < m_iListNumber && iListKey > 0)
		{
			CListNode* ret = m_aFreeList[iListKey].Delete(nullptr);
			ret->IncRC();
			__setListMap(iListKey);
			return ret;
		}
	}
	
	int iTreeKey = (sz - HEAP_MEMORY_UNIT * m_iListNumber - 1) / m_TREE_SIZE;
	if(iTreeKey >= m_iTreeNumber)
		iTreeKey = m_iTreeNumber - 1;
	CListNode* ret = m_aFreeTree[iTreeKey].Delete(sz);
	ret->IncRC();
	return ret;
}

int CFreeMemoryKeeper::__getListKeyByMap(size_t sz)
{
	if(sz <= 0)
		return -1;

	int i;
	if(sz <= HEAP_MEMORY_UNIT * m_iListNumber)
	for(i=(sz-1) / HEAP_MEMORY_UNIT; i<m_iListNumber; i++)
	{
		if(!(m_aFreeList[i].IsNull()))
			return i;
	}

	i = 0;
	if(sz > HEAP_MEMORY_UNIT * m_iListNumber)
		i = (sz - HEAP_MEMORY_UNIT * m_iListNumber - 1) / m_TREE_SIZE;
	if(i >= m_iTreeNumber)
		i = m_iTreeNumber - 1;
	for(; i<m_iTreeNumber; i++)
	{
		if(!(m_aFreeTree[i].Empty()) && m_aFreeTree[i].GetMaxSize() >= sz)
			return i+m_iListNumber;
	}

	return -1;
}

void CFreeMemoryKeeper::__setListMap(int key)
{

}
