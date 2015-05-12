#ifndef CNodeList_H
#define CNodeList_H

#include "CListNode.h"
#include "CMemoryNode.h"

template <class T>
class CNodeList
{
public:
	//CNodeList();
	//~CNodeList();
	T* Delete(T* pDeletePtr = nullptr);
	//(pre, the)
	void Insert(T*, T*);
	bool IsNull();
private:
	T m_pHead;
};

template <class T>
void CNodeList<T>::Insert(T* pPrePtr, T* pInsertPtr)
{
	//preptr ΪNULL����ͷ������
	if(pPrePtr == nullptr)
		pPrePtr = &m_pHead;

	T* pNextPtr = pPrePtr->GetNextPtr();
	if(pNextPtr != nullptr)
	{
		pNextPtr->SetPreviousPtr(pInsertPtr);
	}
	pInsertPtr->SetNextPtr(pNextPtr);
	pPrePtr->SetNextPtr(pInsertPtr);
	pInsertPtr->SetPreviousPtr(pPrePtr);
}

template <class T>
T* CNodeList<T>::Delete(T* pDeletePtr)
{
	//pdeleteptrΪnull��������ͷɾ��һ�����
	if(pDeletePtr == nullptr)
	{
		pDeletePtr = m_pHead.GetNextPtr();
		if(pDeletePtr == nullptr)
			return nullptr;
	}


	T* pPrePtr = pDeletePtr->GetPreviousPtr();
	if(pPrePtr == nullptr)
		return nullptr;

	T* pNextPtr = pDeletePtr->GetNextPtr();
	
	pPrePtr->SetNextPtr(pNextPtr);
	if(pNextPtr != nullptr)
	{
		pNextPtr->SetPreviousPtr(pPrePtr);
	}
	return pDeletePtr;
}

template <class T>
bool CNodeList<T>::IsNull()
{
	if(m_pHead.GetNextPtr() == nullptr)
		return true;
	else
		return false;
}


#endif