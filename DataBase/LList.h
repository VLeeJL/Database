#ifndef LLIST_H_
#define LLIST_H_
#include "List.h"
#include "Link.h"
#include <cassert>

template <typename E>
class LList : public List<E>
{
public:
	LList() { init(); }
	LList(const LList&) = delete;
	~LList() { removeAll(); }
	E operator[](const int&);
	void clear();
	void insert(const E&);
	void apend(const E&);
	E remove();
	void moveToStart();
	void moveToEnd();
	void prev();
	void next();
	int length() const;
	int curPos() const;
	void moveToPos(int pos);
	const E& getValue() const;	
	int search(const E&) const;
private:
	Link<E> *head;
	Link<E> *tail;
	Link<E> *curr;//ʵ��ʵ�ֵ�ʱ����ָ��ǰ�ڵ��ǰһ���ڵ㣬���Ƕ����ʾ������Ȼ�ǵ�ǰ�ڵ�
	int cnt;
	void init()
	{
		head = tail = curr = new Link<E>();
	}
	void removeAll()
	{
		while (head != nullptr)
		{
			curr = head;
			head = head->next;
			delete curr;
		}
	}
};
#endif // !LLIST_H_