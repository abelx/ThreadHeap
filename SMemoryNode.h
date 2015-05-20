#ifndef SMemoryNode_H
#define SMemoryNode_H
#include "functions.h"



struct SMemoryNode
{
	SMemoryNode(size_t sz, int rc,
		SMemoryNode* pl, SMemoryNode* nl, 
		SMemoryNode* pm, SMemoryNode* nm)
		:m_ulSize(sz), m_iRc(rc),
		m_pPreviousNodeInList(pl), m_pNextNodeInList(nl),
		m_pPreviousNodeInMemory(pm), m_pNextNodeInMemory(nm){}
	
	size_t m_ulSize;
	int m_iRc;
	char m_PointerInTree[12];
	struct SMemoryNode* m_pPreviousNodeInList;
	struct SMemoryNode* m_pNextNodeInList;
	struct SMemoryNode* m_pPreviousNodeInMemory;
	struct SMemoryNode* m_pNextNodeInMemory;

	//À˘ Ùœﬂ≥ÃID
	int m_hThread;
};

static const int HEAP_MEMORY_UNIT = 8;
static const int MEMORY_NODE_SIZE = g_Align(sizeof(SMemoryNode), HEAP_MEMORY_UNIT);
#endif
