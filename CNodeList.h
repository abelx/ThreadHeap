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
	//preptr 为NULL，在头部插入
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
	//pdeleteptr为null，从链表头删除一个结点
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