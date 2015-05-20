#include "CListNode.h"
#include <Windows.h>


CListNode* CListNode::GetNextPtr()
{
	return (CListNode*)(m_sListNode.m_pNextNodeInList);
}

CListNode* CListNode::GetPreviousPtr()
{
	return (CListNode*)(m_sListNode.m_pPreviousNodeInList);
}

void CListNode::SetNextPtr(CListNode* ptr)
{
	m_sListNode.m_pNextNodeInList = (SMemoryNode*)ptr;
}

void CListNode::SetPreviousPtr(CListNode* ptr)
{
	m_sListNode.m_pPreviousNodeInList = (SMemoryNode*)ptr;
}

size_t CListNode::GetSize()
{
	return m_sListNode.m_ulSize;
}

void CListNode::SetSize(size_t sz)
{
	m_sListNode.m_ulSize = sz;
}

void CListNode::IncRC()
{
	m_sListNode.m_iRc++;
}

void CListNode::DecRC()
{
	m_sListNode.m_iRc--;
}

int CListNode::GetRC()
{
	return m_sListNode.m_iRc;
}

PVOID CListNode::GetPointer()
{
	return (PVOID)((BYTE*)this + MEMORY_NODE_SIZE);
}


