#include <memory>

#ifndef BTREE_H_
#define BTREE_H_



//Ϊ���͸��Ӷȣ���ֹ������ʼ����=���������
//����һ���淶B+���Ľӿ�
template<typename Key, typename E>
class BTree
{
public:
	BTree() {}
	~BTree() {}
	BTree(const BTree&) = delete;
	BTree(const BTree&&) = delete;
	BTree& operator = (const BTree&) = delete;
	BTree& operator = (const BTree&&) = delete;

	virtual std::shared_ptr<E> search(const Key&) = 0;
	virtual void insert(Key&, E*) = 0;
	virtual std::shared_ptr<E> remove(const Key& key) = 0;
};

#endif // !BTREE_H_