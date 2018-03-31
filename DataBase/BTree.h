#pragma once
#include <memory>

//Ϊ���͸��Ӷȣ���ֹ������ʼ����=���������
//����һ���淶B+���Ľӿ�
template<typename Key, typename E>
class BTree
{
public:
	BTre() {}
	~BTree() {}
	BTree(const BTree&) = delete;
	BTree(const BTree&&) = delete;
	BTree& operator = (const BTree&) = delete;
	BTree& operator = (const BTree&&) = delete;

	virtual std::shared_ptr<E> search(const Key&) = 0;
	virtual void insert(const Key&, const std::shared_ptr<E>) = 0;
	virtual void remove(const Key& key) = 0;
};