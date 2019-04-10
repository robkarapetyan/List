#pragma once
#include "IList.h"
#include <assert.h>
#include <exception>

template<typename T>
class DLList : public List<T>
{
public:
	DLList();
	~DLList() override {};

private:
	struct Node {
		Node(const T& data, Node* p, Node* n)
			: prev(p), next(n), Data(data)
		{
		}
		Node* prev;
		Node* next;
		T Data;
	};
public:

	class Iterator {
		friend class DLList;
	public:
		Iterator() = default;
		Iterator& operator=(const Iterator&) = default;

		Iterator operator + (size_t a);	// moves iterator forward  a times
		Iterator operator - (size_t a);	// moves iterator backward a times
		Iterator operator ++();
		Iterator operator ++ (int);
		Iterator operator --();
		Iterator operator -- (int);
		T operator *();
	private:
		Node* m_cur;
	};

	void clear() override;
	bool empty() override;
	size_t size() override;
	void insert(const T& data, size_t pos) override;
	void erase(size_t index) override;
	void print();
	void push_back(const T& data) override;
	void push_front(const T& data) override;
	void pop_back() override;
	void pop_front() override;
	Iterator begin();
	Iterator end();
private:

	Node* m_head;
	size_t m_size;
};
//----------------------------------------------- List's functions -----------------

template <typename T>
DLList<T>::DLList()
	: m_head(nullptr)
	, m_size(0)
{
}


template<typename T>
inline void DLList<T>::clear()
{
	while (m_head != nullptr) {
		Node* a = m_head;
		m_head = m_head->next;
		delete a;
		--m_size;
	}
}

template<typename T>
inline bool DLList<T>::empty()
{
	return m_head == nullptr;
}

template<typename T>
inline size_t DLList<T>::size()
{
	return m_size;
}

template<typename T>
inline void DLList<T>::insert(const T& data, size_t pos)
{
	assert(pos > 0);
	if (pos > m_size + 1) {
		throw std::out_of_range("Invalid size");
	}
	if (pos == 1) {
		if(m_head == nullptr){
			m_head = new Node(data, nullptr, nullptr);
			++m_size;
			return;
		}
		m_head->prev = new Node(data, nullptr, m_head);
		m_head = m_head->prev;
		++m_size;
		return;
	}
	Node* tempdecr = nullptr;
	Node* temp = m_head;
	for (size_t i = 1; i < pos; ++i) {
		tempdecr = temp;
		if (temp->next != nullptr)
		{
			temp = temp->next;
		}
	}
	if (temp != tempdecr)
	{
		tempdecr->next = temp->prev = new Node(data, tempdecr, temp);
	}
	else
	{
		temp->next = new Node(data, temp, nullptr);
	}
	++m_size;
}

template<typename T>
inline void DLList<T>::erase(size_t index)
{
	assert(index > 0);
	if (index > m_size) {
		throw std::out_of_range("Invalid size");
	}

	if (index == 1) {
		Node* a = m_head;
		m_head = m_head->next;
		delete a;
		--m_size;
		return;
	}
	Node* tempdecr = nullptr;
	Node* temp = m_head;
	for (size_t i = 1; i < index; ++i) {
		tempdecr = temp;
		if (temp->next != nullptr)
		{
			temp = temp->next;
		}
	}
	Node* third = temp->next;
	tempdecr->next = temp->next;
	third->prev = tempdecr;
	delete temp;
	--m_size;
}

template<typename T>
inline void DLList<T>::print()
{
	Node* a = m_head;
	while (a != nullptr) {
		std::cout << a->Data << std::endl;
		a = a->next;
	}
	std::cout << "-------------------------------------------" << std::endl;

}
//----------------------------------------------- Push & Pop ------------------------
template<typename T>
inline void DLList<T>::push_back(const T& data)
{
	Node* temp = m_head;
	for (size_t i = 0; i < m_size; ++i) {
		if (temp->next != nullptr)
		{
			temp = temp->next;
		}
	}
	temp->next = new Node(data, temp, nullptr);
	++m_size;
}

template<typename T>
inline void DLList<T>::push_front(const T & data)
{
	if (m_head == nullptr) {
		m_head = new Node(data, nullptr, nullptr);
		++m_size;
		return;
	}
	else {
		m_head->prev = new Node(data, nullptr, m_head);
		m_head = m_head->prev;
		++m_size;
		return;
	}
}

template<typename T>
inline void DLList<T>::pop_back()
{
	Node* tempdecr = nullptr;
	Node* temp = m_head;
	while (temp->next != nullptr) {
		tempdecr = temp;
		temp = temp->next;
	}
	tempdecr->next = nullptr;
	delete temp;
	--m_size;
}

template<typename T>
inline void DLList<T>::pop_front()
{
	Node* temp = m_head;
	m_head = m_head->next;
	delete temp;
	--m_size;
}

//-----------------------------------------------List's	Begin,	End------------------
template<typename T>
typename DLList<T>::Iterator DLList<T>::begin()
{
	Iterator it;
	it.cur = DLList::m_head;
	return it;
}

template<typename T>
typename DLList<T>::Iterator DLList<T>::end()
{
	Iterator it;
	it.m_cur = DLList::m_head;
	while (it.m_cur->next != nullptr) {
		it.m_cur = it.m_cur->next;
	}
	return it;
}

//----------------------------------------------- Iterator's operators --------------

template<typename T>
typename DLList<T>::Iterator DLList<T>::Iterator::operator+(size_t a)
{
	Iterator current;
	assert(m_cur != nullptr);
	current.m_cur = m_cur;
	for (size_t i = 0; i < a; ++i) {
		assert(current.m_cur->next != nullptr);
		current.m_cur = current.m_cur->next;
	}
	return current;
}

template<typename T>
typename DLList<T>::Iterator DLList<T>::Iterator::operator-(size_t a)
{
	Iterator current;
	assert(m_cur != nullptr);
	current.m_cur = m_cur;
	for (size_t i = 0; i < a; ++i) {
		assert(current.m_cur->prev != nullptr);
		current.m_cur = current.m_cur->prev;
	}
	return current;
}

template<typename T>
typename DLList<T>::Iterator DLList<T>::Iterator::operator++(int)
{
	Iterator current;
	assert(m_cur != nullptr);
	current.m_cur = m_cur;
	assert(current.m_cur->next != nullptr);
	current.m_cur = current.m_cur->next;
	return current;
}

template<typename T>
typename DLList<T>::Iterator DLList<T>::Iterator::operator++()
{
	assert(m_cur != nullptr);
	assert(m_cur->next != nullptr);
	m_cur = m_cur->next;
	return *this;
}

template<typename T>
typename DLList<T>::Iterator DLList<T>::Iterator::operator--()
{
	assert(m_cur != nullptr);
	assert(m_cur->prev != nullptr);
	m_cur = m_cur->prev;
	return *this;
}

template<typename T>
typename DLList<T>::Iterator DLList<T>::Iterator::operator--(int)
{
	Iterator current;
	assert(m_cur != nullptr);
	current.m_cur = m_cur;
	assert(current.m_cur->prev != nullptr);
	current.m_cur = current.m_cur->prev;
	return current;

}

template<typename T>
inline T DLList<T>::Iterator::operator*()
{
	return m_cur->Data;
}
