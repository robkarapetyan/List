#pragma once

template<typename T>
class List
{
public:
	virtual ~List() {}

	virtual bool empty() = 0;
	virtual size_t size() = 0;
	virtual void insert(const T& data,size_t pos) = 0;
	virtual void erase(size_t index) = 0;
	virtual void clear() = 0;
	virtual void print() = 0;
	virtual const T& getValue(size_t pos) const = 0;
	virtual void push_back(const T& data) = 0;
	virtual void pop_back() = 0;
	virtual void push_front(const T& data) = 0;
	virtual void pop_front() = 0;
};
