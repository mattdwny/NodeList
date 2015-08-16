#pragma once

template <typename T>
class Node
{
public:
	Node();
	Node(const T& data, Node *next, Node *prev);

	T		mData;
	Node*	mNext;
	Node*	mPrev;
};

template <typename T>
Node<T>::Node() : mData(), mNext(nullptr), mPrev(nullptr) {}

template <typename T>
Node<T>::Node(const T& data, Node *next, Node *prev) : mData(data), mNext(next), mPrev(prev) {}