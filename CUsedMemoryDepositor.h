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
		:m_pHeap(pHeap), m_iListNumber(ln), m_bClearFlag(cf)
	{
		m_DepositList = new CNodeList<CListNode>[ln];
		
		m_CLEAR_THRESHOLD_MAX = m_CLEAR_THRESHOLD;
		for(int i=0; i<ln-1; i++)
			m_CLEAR_THRESHOLD_MAX *= m_CLEAR_THRESHOLD;

		m_iMountTimes = 0;

	}
	~CUsedMemoryDepositor()
	{
		delete[] m_DepositList;
	}


	void Mount(CListNode*);
	void UMount(CListNode*);
private:
	static const int m_CLEAR_THRESHOLD = 2;
	int m_CLEAR_THRESHOLD_MAX;
	void __Clear();
	CThreadHeap* m_pHeap;
	bool m_bClearFlag;
	int m_iListNumber;
	int m_iMountTimes;
	CNodeList<CListNode>* m_DepositList;
};
