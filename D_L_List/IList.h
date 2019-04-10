#pragma once

template<typename T>
class Interface
{
public:
	virtual bool empty() = 0;
	virtual size_t size() = 0;
	virtual void insert(const T& data,size_t pos) = 0;
	virtual void erase(size_t index) = 0;
	virtual void clear() = 0;
	virtual void push_back(const T& data) = 0;
	virtual void pop_back() = 0;
	virtual void push_front(const T& data) = 0;
	virtual void pop_front() = 0;
};
