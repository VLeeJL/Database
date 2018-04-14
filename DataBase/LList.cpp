#include "LList.h"

template<typename E>
E& LList<E>::operator[](int pos)
{
	moveToPos(pos);
	return curr->element;
}

template<typename E>
void LList<E>::clear()
{
	removeAll();
	init();
}

template <typename E>
void LList<E>::insert(const E &ele)
{
	curr->next = new Link<E>(ele, curr->next);
	if (curr == tail)
	{
		tail = curr->next;
	}
	++cnt;
}

//1����ǰָ��ָ�����ͷ�ڵ㣨�������ʱ�򣩣�2�����м��ʱ��3����β�ڵ��ʱ��
template <typename E>
E LList<E>::remove()
{
	assert(curr->next != NULL);//�������1
	//Assertֻ������debug�汾
	E it = curr->next->element;//��curr��ע��
	if (curr->next == tail)
	{
		tail = curr;
	}
	Link<E>* tempPtr = curr->next;
	curr->next = curr->next->next;
	delete tempPtr;
	--cnt;
	return it;
}

template <typename E>
inline void LList<E>::moveToStart()
{
	curr = head;
}

template <typename E>
inline void LList<E>::moveToEnd()
{
	curr = tail;
}

template <typename E>
void LList<E>::prev()
{
	if (curr == head)
		return;
	Link<E>* tempPtr = head;
	while (tempPtr->next != curr)
	{
		tempPtr = tempPtr->next;
	}
	curr = tempPtr;
}

template <typename E>
void LList<E>::next()
{
	if (curr != tail)
		curr = curr->next;
}

template <typename E>
inline int LList<E>::length() const
{
	return cnt;
}

template <typename E>
int LList<E>::curPos() const
{
	int currentPos = 0;
	Link<E>* tempPtr = head;
	while (tempPtr != curr)
	{
		++currentPos;
	}
	return currentPos;
}

template <typename E>
void LList<E>::moveToPos(int pos)
{
	//���Է�������Ǵ���ʵ�֣��籾��
	//Ҳ��ֱ�ӽ�curr��Ϊhead��һ�α����õ�Ŀ��λ�� 
	assert((pos >= 0) && (pos <= cnt));	
	int currentPos = curPos();
	int posCount = 0;
	if (currentPos <= pos)
	{
		posCount = currentPos;
		while (posCount != pos)
		{
			curr = curr->next;
			++posCount;
		}
	}
	else
	{
		Link<E>* tempPtr = head;
		while (posCount != pos)
		{
			tempPtr = tempPtr->next;
			posCount;
		}
	}	
}

template <typename E>
const E& LList<E>::getValue() const
{
	return curr->element;
}

template <typename E>
void LList<E>::apend(const E& it)
{
	tail->next = new Link<E>();
	tail = tail->next;
	++cnt;
}

template <typename E>
int LList<E>::search(const E& elem) const
{
	Link<E>* tempCurr = head;
	int tempCurPos = 0;
	while (tempCurr != nullptr)
	{
		if (tempCurr->element == elem)
			return tempCurPos;
		else
			tempCurr = tempCurr->next;
		++tempCurPos;
	}
	return -1;
}