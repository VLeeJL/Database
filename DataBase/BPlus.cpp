#include "BPlus.h"


template<typename Key, typename E>
void BPlus<Key, E>::init()
{

}

template <typename Key, typename E>
std::shared_ptr<E> BPlus<Key, E>::search(const Key& key)
{
	_currentPtr = _rootPtr;
	while (!_currentPtr->isLeaf())
	{
		int pos = _currentPtr->searchKey(key);
		_currentPtr = _currentPtr->getPtrChild(pos);//�����pos��֤����Խ��
	}
	int pos = _currentPtr->searchKey(key);//����Ҷ�ӽڵ�
	if ((pos != -1) && _currentPtr->getKey(pos) == key)
	{
		E* tempElementPtr = _currentPtr->getChildElement(pos);
		std::shared_ptr<E> ptr(tempElementPtr);
		tempElementPtr = nullptr;
		return ptr;
	}
	else
		return nullptr;
}

//�ؼ��ֵĲ������������
template <typename Key, typename E>
void BPlus<Key, E>::insert(const Key& key, E* ptrElem)
{
	auto ptrElem = search(key);
	if (ptrElem != nullptr)
	{
		cout << "The element has already exist" << endl;
		return;
	}
	int pos = _currentPtr->searchKey(key);//��ʱ�Ѵ���Ҷ�ӽڵ�
	_currentPtr->insertKey(key, pos);//���뵽�Ѵ��ڵĹؼ���֮ǰ
	_currentPtr->insertChild(ptrElem, pos);//Ҷ�ӽڵ�ؼ���������ֵ������ͬ
	++_size;
	solveOverFlow(_currentPtr, true);
}

template <typename Key, typename E>
void BPlus<Key, E>::solveOverflow(BPNode<Key, E>* nodePtr, bool isLeaf)
{
	if (nodePtr->getChildListLength() < (_order + 1)) return;//����Ҫ�����������
	int midOrder = (_order + 1) / 2;
	BPNode<Key, E>* childPtr = getBPNode(isLeaf);
	for (int i = midOrder, j = 0; i != (_order + 1); ++i, ++j)
	{
		childPtr->insertKey(nodePtr->removeKey(i), j);
		if (isLeaf)
			childPtr->insertChild(nodePtr->removeChild(i), j);
		else
			childPtr->insertPtrChild(nodePtr->removeChild(i), j);
	}
	if (isLeaf)
		childPtr->setNextLeaf(nodePtr->getLeftLeaf(), nodePtr->getRightLeaf());//�������ҽڵ�	
	BPNode<Key, E>* parentPtr = nodePtr->getParentPtr();
	childPtr->setParentPtr(parentPtr);
	int pos = parentPtr->searchKey(childPtr->getKey(0));
	parentPtr->insertKey(childPtr->getKey(0), pos);
	parentPtr->insertPtrChild(childPtr, pos);
	return solveOverflow(parentPtr, parentPtr->isLeaf());
}
//�ڲ��ڵ�Ĺؼ�����������Ҫɾ��
template <typename Key, typename E>
std::shared_ptr<E> BPlus<Key, E>::remove(const Key& key)
{
	auto ptrElem = search(key);
	if (ptrElem == nullptr)
	{
		cout << "The element dosen't exist" << endl;
		return;
	}
	int pos = _currentPtr->searchKey(key);//��ʱ�Ѵ���Ҷ�ӽڵ�
	_currentPtr->removeKey(pos);
	E* tempElementPtr = _currentPtr->removeChild(pos);
	std::shared_ptr<E> ptr(tempElementPtr);
	tempElementPtr = nullptr;
	--_size;
	solveUnderflow(_currentPtr, true);
	return ptr;
}

template <typename Key, typename E>
void BPlus<Key, E>::mergeLeaf(BPNode<Key, E>* ptr, BPNode<Key, E>* operatedPtr, bool isRight)
{
	int size = ptr->getKeyListLength();
	int insertPos = isRight ? operatedPtr->getKeyListLength() - 1 : 0;
	operatedPtr->insertKey(ptr->removeKey(size - 1), insertPos);
	operatedPtr->insertPtrChild(ptr->removeChild(size - 1), insertPos);
}

template <typename Key, typename E>
void BPlus<Key, E>::solveUnderflow(BPNode<Key, E>* nodePtr, bool isLeaf)
{
	int midOrder = (_order + 1) / 2; 
	if (nodePtr->getChildListLength() >= midOrder) 
		return;//����Ҫ�����������	
	if (isLeaf)
	{

	}
	if ((nodePtr->getLeftLeaf()->getKeyListLength()) > midOrder)//�����ֵܴ���ȥ
	{
		mergeLeaf(nodePtr->getLeftLeaf(), nodePtr, false);
	}
	else if ((nodePtr->getRightLeaf()->getKeyListLength()) > midOrder)
	{
		mergeLeaf(nodePtr->getRightLeaf(), nodePtr, true);;
	}
	else//���ұ��ֵܽڵ�ϲ�
	{
		int size = nodePtr->getKeyListLength();
		BPNode<Key, E>* rightPtr = nodePtr->getRightLeaf();
		for (int i = szie - 1; i >= 0; --i)
		{
			mergeLeaf(nodePtr, rightPtr, false);
		}
	}
}

template <typename Key, typename E>
BPlus<Key, E>::~BPlus()
{
	if (_rootPtr != nullptr)
		delete _rootPtr;
	_rootPtr = nullptr;
}