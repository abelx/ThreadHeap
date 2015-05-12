#include "CNodeList.h"
#include <stdlib.h>
#include <malloc.h>

class CThreadHeap;
class CMemoryNode;
class CListNode;

class CUsedMemoryDepositor
{
public:
	CUsedMemoryDepositor(CThreadHeap* pHeap, int ln=4, bool cf=true)
		:m_pHeap(pHeap), m_iListNumber(ln)
	{
		m_DepositList = new CNodeList<CListNode>[ln];

		m_iMountTimes = 0;

	}
	~CUsedMemoryDepositor()
	{
		delete[] m_DepositList;
	}

	void Clear();
	void Mount(CListNode*);
	void UMount(CListNode*);

private:
	void __clearList(int);

private:
	static const int _CLEAR_THRESHOLD = 2;
	
	CThreadHeap* m_pHeap;
	int m_iListNumber;
	int m_iMountTimes;
	CNodeList<CListNode>* m_DepositList;
};
