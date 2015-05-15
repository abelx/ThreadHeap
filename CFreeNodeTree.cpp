#include "CFreeNodeTree.h"
#include "CListNode.h"
#include <iostream>
#include <cstring>
#include "SMemoryNode.h"

using namespace std;

void CFreeNodeTree::Insert(CListNode* pNode)
{
	multimap<size_t, int>::const_iterator tmp = m_Tree.insert(multimap<size_t, int>::value_type(pNode->GetSize(), (int)pNode));
	memcpy(((SMemoryNode*)pNode)->m_PointerInTree, &tmp, 12);

}

CListNode* CFreeNodeTree::Delete(size_t sz)
{
	multimap<size_t, int>::const_iterator itor = m_Tree.lower_bound(sz);
	if(itor == m_Tree.end())
		return nullptr;
	else
	{
		CListNode* ret = (CListNode*)(itor->second);
		m_Tree.erase(itor);
		return ret;
	}
}

void CFreeNodeTree::Delete(CListNode* pNode)
{	
	m_Tree.erase(*((multimap<size_t, int>::const_iterator *)(((SMemoryNode*)pNode)->m_PointerInTree)));
}

bool CFreeNodeTree::Empty()
{
	return m_Tree.empty();
}

int CFreeNodeTree::GetMaxSize()
{
	multimap<size_t, int>::const_reverse_iterator itor = m_Tree.rbegin();
	return itor->first;
}

