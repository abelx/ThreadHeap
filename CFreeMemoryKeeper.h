#include "CNodeList.h"
class CThreadHeap;
class CMemoryNode;
class CListNode;
class CFreeNodeTree;

class CFreeMemoryKeeper
{
public:
	CFreeMemoryKeeper(CThreadHeap*, int, int);
	~CFreeMemoryKeeper();
	void Mount(CListNode*);
	void UMount(CListNode*);
	CListNode* UMount(size_t);
//private:
public:
	int __getListKeyByMap(size_t);
	void __setListMap(int);
	static const int m_TREE_SIZE = 256;
	CNodeList<CListNode>* m_aFreeList;
	CFreeNodeTree* m_aFreeTree;
	int m_iListNumber;
	int m_iTreeNumber;
	CThreadHeap* m_pHeap;
};
