#ifndef CMemoryNode_H
#define CMemoryNode_H

#include "SMemoryNode.h"

class CMemoryNode
{
public:
	CMemoryNode(size_t sz=0, 
		CMemoryNode* pm=nullptr, CMemoryNode* nm=nullptr,
		int rc=0)
		:m_sMemoryNode(sz,rc,nullptr,nullptr,(SMemoryNode*)pm, (SMemoryNode*)nm){}
	void Init(size_t sz=0, int rc = 0, 
		CMemoryNode* pm = nullptr, CMemoryNode* nm =nullptr);

	CMemoryNode* GetPreviousPtr();
	void SetPreviousPtr(CMemoryNode*);
	CMemoryNode* GetNextPtr();
	void SetNextPtr(CMemoryNode*);
	size_t GetSize();
	void SetSize(size_t);
	int GetRC();
	
private:
	SMemoryNode m_sMemoryNode;	
};


#endif