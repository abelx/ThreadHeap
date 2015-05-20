#include "CFreeMemoryKeeper.h"
#include "CNodeList.h"
#include "CFreeNodeTree.h"
#include "CListNode.h"
#include "CMemoryNode.h"
#include "functions.h"
#include <iostream>
using namespace std;

CFreeMemoryKeeper::CFreeMemoryKeeper(CThreadHeap* pth, int ln, int tn)
	:m_pHeap(pth), m_iListNumber(ln), m_iTreeNumber(tn)
{
	m_aFreeList = new CNodeList<CListNode>[ln];
	m_aFreeTree = new CFreeNodeTree[tn];
	m_iCheckBits = 0;
}

CFreeMemoryKeeper::~CFreeMemoryKeeper()
{
	delete[] m_aFreeList;
	delete[] m_aFreeTree;
}

void CFreeMemoryKeeper::check_comform()
{
	int test = 0;
	for(int i=0; i<m_iListNumber; i++)
	{
		if(!m_aFreeList[i].IsNull())
			test = test | (1<<i);
	}
	for(int i=0; i<m_iTreeNumber; i++)
	{
		if(!m_aFreeTree[i].Empty())
			test = test | (1 <<(i+m_iListNumber));
	}
	if(test != m_iCheckBits)
	{
		cout << "error" << endl;
		exit;
	}



}

void CFreeMemoryKeeper::Mount(CListNode* pln)
{
	check_comform();
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
		 __setListMap(iTreeKey + m_iListNumber);
	}
}

void CFreeMemoryKeeper::UMount(CListNode* pln)
{
	check_comform();
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
		__setListMap(iTreeKey + m_iListNumber);
	}

}

//认为sz已经做了对齐
CListNode* CFreeMemoryKeeper::UMount(size_t sz)
{
	check_comform();
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
}

int CFreeMemoryKeeper::__getListKeyByMap(size_t sz)
{
	if(sz <= 0)
		return -1;
	
	int iPos, iTmpBits;
	if(sz > HEAP_MEMORY_UNIT * m_iListNumber)
	{
		iPos = (sz - HEAP_MEMORY_UNIT * m_iListNumber - 1) / m_TREE_SIZE;
		if(iPos >= m_iTreeNumber)
			iPos = m_iTreeNumber - 1;
		iPos += m_iListNumber;
	}
	else
	{
		iPos = (sz - 1)/ m_TREE_SIZE;
	}

	iTmpBits = ClearBits(m_iCheckBits, iPos);
	int iKeyRet = ComputeBit2Index(iTmpBits);
	if(iKeyRet >= m_iListNumber)
	{
		for(int i=iKeyRet - m_iListNumber; i<m_iTreeNumber; i++)
		{
			if(!(m_aFreeTree[i].Empty()) && m_aFreeTree[i].GetMaxSize() >= sz)
				return i+m_iListNumber;
		}
		return -1;
	}
	else
		return iKeyRet;
}

void CFreeMemoryKeeper::__setListMap(int key)
{
	if(key < 0 || key > m_iListNumber + m_iTreeNumber - 1)
		return;

	if(key < m_iListNumber)
	{
		if(m_aFreeList[key].IsNull())
			m_iCheckBits = m_iCheckBits & ~(1<<key);
		else
			m_iCheckBits = m_iCheckBits | (1<<key);
	}
	else
	{
		if(m_aFreeTree[key-m_iListNumber].Empty())
			m_iCheckBits = m_iCheckBits & ~(1<<key);
		else
			m_iCheckBits = m_iCheckBits | (1<<key);
	}
}
