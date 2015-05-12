#ifndef CMemoryPool_H
#define CMemoryPool_H

//#include "CMemoryNode.h"
#include "CNodeList.h"
#include <Windows.h>

class CMemoryNode;
class CListNode;
class CThreadHeap;

class CMemoryPool
{
public:
	CMemoryPool(CListNode**, size_t sz = 1024);
	~CMemoryPool();
	void CombineNode(CMemoryNode*, CMemoryNode*);
	CMemoryNode* SpliteNode(CMemoryNode*, size_t);
	void print_pool();
private:
	PVOID m_pMemory;
	size_t m_ulSize;
	CNodeList<CMemoryNode> m_cMemoryList;
};

#endif