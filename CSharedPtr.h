#include "CListNode.h"
#include "DepositFreeHeap.h"
using namespace DepositFreeHeap;

template <typename T>
class CSharedPtr
{
public:
	explicit CSharedPtr(T* ptr)
	{
		m_pMem = ptr;
		m_pclnMem = (CListNode *)((char*)m_pMem - MEMORY_NODE_SIZE);
	}

	~CSharedPtr()
	{
		m_pclnMem->DecRC();
		if(m_pclnMem->GetRC() == 0)
			MyFree(m_pMem);
	}

	CSharedPtr& operator=(const CSharedPtr& csp)
	{
		m_pMem = csp.m_pMem;
		m_pclnMem->IncRC();
	}

	T* operator->()
	{
		return m_pMem;
	}

private:
	T* m_pMem;
	CListNode *m_pclnMem;
};
