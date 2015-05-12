#include "CUsedMemoryDepositor.h"
#include "CListNode.h"
#include "CMemoryNode.h"
#include "CTheadHeap.h"
#include "CFreeMemoryKeeper.h"
#include "CMemoryPool.h"

void CUsedMemoryDepositor::Mount(CListNode* pMnt)
{
	m_DepositList[0].Insert(nullptr,pMnt);
}

void CUsedMemoryDepositor::UMount(CListNode* pUmnt)
{
	m_DepositList[0].Delete(pUmnt);
}

void CUsedMemoryDepositor::__clearList(int i)
{
	if(i<0 || i>m_iListNumber)
		return;

	CListNode *pclnTmp;
	while(!m_DepositList[i].IsNull())
	{
		pclnTmp = m_DepositList[i].Delete(); //删除头节点
		if(pclnTmp->GetRC() == 0)
			m_pHeap->Free(pclnTmp);
		else
			m_DepositList[(i+1)%m_iListNumber].Insert(nullptr, pclnTmp);
	}

}

void CUsedMemoryDepositor::Clear()
{
	if(m_iMountTimes==0)
	{
		m_iMountTimes++;
		return;
	}

	int thresh = _CLEAR_THRESHOLD;
	int i;
	for(i=0; i<m_iListNumber; i++)
	{
		if(m_iMountTimes % thresh != 0)
		{
			__clearList(i-1);
			break;
		}
		thresh *= _CLEAR_THRESHOLD;
	}
	if(i == m_iListNumber)
	{
		__clearList(i-1);
		m_iMountTimes = 0;
	}

	m_iMountTimes++;
}
/*
void CUsedMemoryDepositor::Clear()
{
	if(m_iMountTimes==0)
	{
		m_iMountTimes++;
		return;
	}


	int thresh = m_CLEAR_THRESHOLD_MAX;

	for(int i=m_iListNumber-1; i>=0; i--)
	{
		if(m_iMountTimes%thresh == 0)
		{
			CListNode* tmp = ((CListNode*)(m_DepositList+i))->GetNextPtr(); //为了遍历做了个强转，不太好
			CListNode* del;	
			while(tmp != nullptr)
			{
				del = tmp->GetNextPtr();
				if(tmp->GetRC() == 0)
				{
					(m_DepositList+i)->Delete(tmp);
					CMemoryNode* mtmp = (CMemoryNode*)tmp;
					CMemoryNode* pStart = mtmp;
					CMemoryNode* pEnd = mtmp;
					if(mtmp->GetPreviousPtr()->GetRC() == -1)
					{
						m_pHeap->m_Keeper->UMount((CListNode*)(mtmp->GetPreviousPtr()));
						pStart = mtmp->GetPreviousPtr();
					}
					if(mtmp->GetNextPtr()!=nullptr && mtmp->GetNextPtr()->GetRC() == -1)
					{
						pEnd = mtmp->GetNextPtr();
						m_pHeap->m_Keeper->UMount((CListNode*)pEnd);
					}
					m_pHeap->m_Pool->CombineNode(pStart, pEnd);
					m_pHeap->m_Keeper->Mount((CListNode*)pStart);
				}
				else
				{
					if(i<m_iListNumber-1)
					{
						(m_DepositList+i)->Delete(tmp);
						(m_DepositList+i+1)->Insert(nullptr,tmp);
					}
				}
				tmp = del;
			}
			break;
		}
		thresh =thresh / m_CLEAR_THRESHOLD;
	}
	m_iMountTimes = (m_iMountTimes+1)%(m_CLEAR_THRESHOLD_MAX + 1);
}

*/