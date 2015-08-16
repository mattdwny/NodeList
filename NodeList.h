#pragma once

#include <stdexcept>
#include "Node.h"

template <typename T>
class NodeList
{
public:
	//constructors
	NodeList();

	//size operations
	bool empty() const;
	std::size_t size() const;
	//std::size_t maxsize() const;

	//element access
	T&		front();
	T&		back();
	T&		operator[](std::size_t position);
	T&		at(std::size_t position);

	//list mutation
	void erase(std::size_t position);
	void insert(std::size_t position, const T& value);
	//void emplace(std::size_t position, Args&& ...);

	void push_front(const T& value);
	void push_back(const T& value);
	void pop_front();
	void pop_back();
	//void emplace_front(Args&& ...);
	//void emplace_back(Args&& ...);

	//auxiliary operations
	void clear();
	void sort();
	//void remove_if(Predicate pred);
	void remove(const T& value);
	void assign(const NodeList& other);
	void swap(const NodeList& other);

private:
	Node<T>* find(std::size_t position);
	void insert_between(Node<T> *first, Node<T> *second, const T& value);
	void remove_inner(Node<T> *first, Node<T> *second, Node<T> *third);

	std::size_t			mSize;
	Node<T>*			mHeadSentinel;
	Node<T>*			mTailSentinel;
};

template <typename T>
NodeList<T>::NodeList() : mSize(0), mHeadSentinel(new Node<T>()), mTailSentinel(new Node<T>())
{
	mHeadSentinel->mNext = mTailSentinel;
	mTailSentinel->mPrev = mHeadSentinel;
}

template <typename T>
std::size_t NodeList<T>::size() const
{
	return mSize;
}

template <typename T>
bool NodeList<T>::empty() const
{
	return mSize == 0;
}

template <typename T>
void NodeList<T>::insert(std::size_t position, const T& value)
{
	Node<T> *location = find(position);

	insert_between(location->mPrev, location, value);
	++mSize;
}

template <typename T>
void NodeList<T>::erase(std::size_t position)
{
	Node<T> *location = find(position);

	remove_inner(location->mPrev, location, location->mNext);
	--mSize;
}

template <typename T>
void NodeList<T>::push_front(const T& value)
{
	insert_between(mHeadSentinel, mHeadSentinel->mNext, value);
	++mSize;
}

template <typename T>
void NodeList<T>::push_back(const T& value)
{
	insert_between(mTailSentinel->mPrev, mTailSentinel, value);
	++mSize;
}

template <typename T>
void NodeList<T>::pop_front()
{
	remove_inner(mHeadSentinel, mHeadSentinel->mNext, mHeadSentinel->mNext->mNext);
	--mSize;
}

template <typename T>
void NodeList<T>::pop_back()
{
	remove_inner(mTailSentinel->mPrev->mPrev, mTailSentinel->mPrev, mTailSentinel);
	--mSize;
}

template <typename T>
T& NodeList<T>::front()
{
	return mHeadSentinel->mNext->mData;
}

template <typename T>
T& NodeList<T>::back()
{
	return mTailSentinel->mPrev->mData;
}

template <typename T>
T& NodeList<T>::at(std::size_t position)
{
	Node<T> *location = find(position);
	return location->mData;
}

template <typename T>
T& NodeList<T>::operator[](std::size_t position)
{
	return at(position);
}

template <typename T>
Node<T>* NodeList<T>::find(std::size_t position)
{
	Node<T> *temp = nullptr;

	if(position <= mSize/2)
	{
		temp = mHeadSentinel;
		while(position--) temp = temp->mNext;
		return temp->mNext;
	}

	position = (mSize - 1) - position; //zero if position was last element, 1 for second to last, 2, for third to last, etc
	
	temp = mTailSentinel;
	while(position--) temp = temp->mPrev;
	return temp->mPrev;
}

template <typename T>
void NodeList<T>::insert_between(Node<T> *first, Node<T> *second, const T& value)
{
	Node<T> *temp = new Node<T>(value, second, first);

	first->mNext = second->mPrev = temp;
}

template <typename T>
void NodeList<T>::remove_inner(Node<T> *first, Node<T> *second, Node<T> *third)
{
	delete second;

	first->mNext = third;
	third->mPrev = first;
}