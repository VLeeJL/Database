#ifndef BPLUS_H_
#define BPLUS_H_
#include "BPNode.h"
#include "BPLeafNode.h"
#include "BTree.h"

//keyֵ��childֵ��һ��
//(m/2, m)���ؼ�ֵ
//��m/2+1��m+1��������
template <typename Key, typename E>
class BPlus : BTree<Key, E>
{
public:
	BPlus(): _order(0), _size(0), _rootPtr(new BPNormalNode<Key, E>()), _currentPtr(_rootPtr), _rootLeafNode(new BPLeafNode()) {}
	BPlus(const int& capacity) : _order(capacity), _size(0), _rootPtr(new BPNormalNode<Key, E>()),
		_currentPtr(_rootPtr), _rootLeafNode(new BPLeafNode()) {}
	BPlus(const BPlus&) = delete;
	BPlus& operator=(const BPlus&) = delete;

	std::shared_ptr<E> search(const Key&);
	void insert(Key&, E*);
	std::shared_ptr<E> remove(const Key&);
	~BPlus();
private:
	void mergeLeaf(BPNode<Key, E>*, BPNode<Key, E>*, bool);
	void solveOverflow(BPNode<Key, E>*, bool);
	void solveUnderflow(BPNode<Key, E>*, bool);
	void init();
private:
	int _order;//�ؼ�ֵ������
	int _size;//B+���ܵĹؼ�ֵ����
	BPNode<Key, E>* _rootPtr;
	BPNode<Key, E>* _currentPtr;
	BPNode* _rootLeafNode;
};

//�򵥹���ģʽ
template <typename Key, typename E>
BPNode<Key, E>* getBPNode(bool isLeaf)
{
	if (isLeaf)
		return new BPLeafNode<Key, E>();
	else
		return new BPNormalNode<Key, E>();
}
#endif // !BPLUS_H_