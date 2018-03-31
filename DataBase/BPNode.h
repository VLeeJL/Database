#pragma once
#include <list>
#include <memory>

//����B+���ؼ��������ͺ���ָ��������ͬ

template <typename Key, typename E>
class BPNode
{	
public:
	class Pair
	{
	public:
		Pair() :_childPtr(nullptr) {}//Ĭ�Ϲؼ��ֵ��������ͻ��ṩ���ݳ�ʼ��
		Pair(const std::shared_ptr<Key>& keyPtr = nullptr, const std::shared_ptr<E>& ptr = nullptr)
			:_keyPtr(keyPtr), _ptr(ptr) {}
		Pair(const Pair&);
		Pair& operator=(const Pair&);
		Pair(const Pair&&) = delete;
		Pair& operator=(const Pair&&) = delete;
		void setValue(const std::shared_ptr<Key> keyPtr);
		std::shared_ptr<Key> getKey();
		std::shared_ptr<E> getPtr();
		~Pair() {}
	private:
		void helpCopy(const Pair&);
	private:
		std::shared_ptr<Key> _keyPtr;
		std::shared_ptr<E> _ptr;
	};
protected://�����������
	typedef typename std::list<std::shared_ptr<Pair>> PtrPair;
	//�ڵ㵱ǰ����������list��Pair���������
	PtrPair _ptrPairs;
	bool _isLeaf;
	//�ýڵ���������
	size_t _capacity;
public:
	BPNode() :_ptrPairs(new PtrPair()), isLeaf(false), _capacity(0) {}
	BPNode(const bool& isLeaf, const size_t& capacity = 0) :_ptrPairs(new PtrPair()),
		_isLeaf(isLeaf), _capacity(capacity) {}//�涨�������ڵ�ʱ��Ҫָ��������
	BPNode(const BPNode&);
	BPNode& operator=(const BPNode&);
	BPNode(const BPNode&&) = delete;
	BPNode& operator=(const BPNode&&) = delete;
	virtual ~BPNode() {}
	//������Ϊ��Զֻ��Ҷ�ӽڵ㷢��
	virtual void insert(const Key& key, const E& ptr) = 0;//�ڽڵ��ڲ�����pair��Ĭ�ϵ����߻����ȵ���full����
	virtual bool isLeaf() const = 0;//��ǰ�ڵ��Ƿ�ΪҶ�ӽڵ�
	virtual bool isFull() const = 0;//��ǰ�ڵ�ļ�¼�����Ƿ�Ϊ��
	virtual int numrecs() const = 0;//��ǰ��¼������
	//virtual std::shared_ptr<Key> getKeysArray() const {}//���عؼ�������ָ��
private:
	void helpCopy(const BPNode& bpNode);
};