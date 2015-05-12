#ifndef CListNode_H
#define CListNode_H
#include <Windows.h>
#include "SMemoryNode.h"

class CListNode
{
public:
	CListNode(size_t sz=0, int rc=0,
		SMemoryNode* pl=nullptr, SMemoryNode* nl=nullptr, 
		SMemoryNode* pm=nullptr, SMemoryNode* nm=nullptr)
		:m_sListNode(sz,rc,pl,nl,pm,nm){}

	CListNode* GetPreviousPtr();
	void SetPreviousPtr(CListNode*);
	CListNode* GetNextPtr();
	void SetNextPtr(CListNode*);
	size_t GetSize();
	void SetSize(size_t);
	void IncRC();
	void DecRC();
	int GetRC();
	PVOID GetPointer();
private:
	SMemoryNode m_sListNode;	
};


#endif