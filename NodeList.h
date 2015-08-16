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

	std::size_t			mSize;
	Node<T>*			mHead;
	Node<T>*			mTail;
};

template <typename T>
NodeList<T>::NodeList() : mSize(0), mHead(nullptr), mTail(nullptr) {}

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
	if(position == 0)	  return push_front(value); //delagation to avoid issues with the head pointer
	if(position == mSize) return push_back(value);  //delegation to avoid issues with the tail pointer

	Node<T> *location = find(position);
	Node<T> *temp = new Node<T>(value, location, location->mPrev);
	temp->mNext->mPrev = temp;
	temp->mPrev->mNext = temp;
	++mSize;
}

template <typename T>
void NodeList<T>::erase(std::size_t position)
{
	//if(empty()) throw std::length_error("tried to erase an element in an empty NodeList");

	if(position == 0)		   return pop_front();
	if(position == mSize - 1)  return pop_back();

	Node<T> *location = find(position);

	location->mNext->mPrev = location->mPrev;
	location->mPrev->mNext = location->mNext;
	--mSize;
}

template <typename T>
void NodeList<T>::push_front(const T& value)
{
	if(mSize > 0)
	{
		Node<T>* temp = new Node<T>(value, mHead, nullptr);
		mHead->mPrev = temp;

		mHead = temp;
		++mSize;
		return;
	}

	mHead = mTail = new Node<T>(value, nullptr, nullptr);
	++mSize;
}

template <typename T>
void NodeList<T>::push_back(const T& value)
{
	if(mSize > 0)
	{
		Node<T>* temp = new Node<T>(value, nullptr, mTail);
		mTail->mNext = temp;

		mTail = temp;
		++mSize;
		return;
	}

	mTail = mHead = new Node<T>(value, nullptr, nullptr);
	++mSize;
}

template <typename T>
void NodeList<T>::pop_front()
{
	//I think the standard doesn't require range checking for user-proofing
	//if(empty()) throw std::lengtherror("tried to erase an element in an empty NodeList");

	if(mSize > 1)
	{
		Node<T> *temp = mHead;
		mHead = mHead->mNext;
		mHead->mPrev = nullptr;
		delete temp;
		--mSize;
		return;
	}

	delete mHead;
	mHead = mTail = nullptr;
	--mSize;
}

template <typename T>
void NodeList<T>::pop_back()
{
	//I think the standard doesn't require range checking for user-proofing
	//if(empty()) throw std::lengtherror("tried to erase an element in an empty NodeList");

	if(mSize > 1)
	{
		Node<T>* temp = mTail;
		mTail = mTail->mPrev;
		mTail->mNext = nullptr;
		delete temp;
		--mSize;
		return;
	}

	delete mTail;
	mTail = mHead = nullptr;
	--mSize;
}

template <typename T>
T& NodeList<T>::front()
{
	return mHead->mData;
}

template <typename T>
T& NodeList<T>::back()
{
	return mTail->mData;
}

template <typename T>
Node<T>* NodeList<T>::find(std::size_t position)
{
	if(position == 0)		  return mHead;
	if(position == mSize - 1) return mTail;

	Node<T> *temp = nullptr; //I leave optimization to the compiler

	if(position <= mSize/2)
	{
		temp = mHead->mNext;
		while(--position) temp = temp->mNext;
		return temp;
	}

	position = (mSize - 1) - position; //zero if position was last element, 1 for second to last, 2, for third to last, etc
	
	temp = mTail->mPrev;
	while(--position) temp = temp->mPrev;
	return temp;
}