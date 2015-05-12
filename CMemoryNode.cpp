#include "CMemoryNode.h"

CMemoryNode* CMemoryNode::GetNextPtr()
{
	return (CMemoryNode*)(m_sMemoryNode.m_pNextNodeInMemory);
}

CMemoryNode* CMemoryNode::GetPreviousPtr()
{
	return (CMemoryNode*)(m_sMemoryNode.m_pPreviousNodeInMemory);
}

void CMemoryNode::SetNextPtr(CMemoryNode* ptr)
{
	m_sMemoryNode.m_pNextNodeInMemory = (SMemoryNode*)ptr;
}

void CMemoryNode::SetPreviousPtr(CMemoryNode* ptr)
{
	m_sMemoryNode.m_pPreviousNodeInMemory = (SMemoryNode*)ptr;
}

size_t CMemoryNode::GetSize()
{
	return m_sMemoryNode.m_ulSize;
}

void CMemoryNode::SetSize(size_t sz)
{
	m_sMemoryNode.m_ulSize = sz;
}

int CMemoryNode::GetRC()
{
	return m_sMemoryNode.m_iRc;
}


void CMemoryNode::Init(size_t sz, int rc,
		CMemoryNode* pm, CMemoryNode* nm)
{
	m_sMemoryNode.m_iRc = rc;
	m_sMemoryNode.m_ulSize = sz;
	m_sMemoryNode.m_pNextNodeInList = nullptr;
	m_sMemoryNode.m_pNextNodeInMemory = (SMemoryNode*)nm;
	m_sMemoryNode.m_pPreviousNodeInList = nullptr;
	m_sMemoryNode.m_pPreviousNodeInMemory = (SMemoryNode*)pm;
}