#pragma once

template<typename T>
class Interface 
{
public:
	virtual bool empty() = 0;
	virtual size_t size() = 0;
	virtual void insert(const T& data,int pos) = 0;
	virtual void erase(size_t index) = 0;
	virtual void clear() = 0;
};