#pragma once
#include "IList.h"
#include <assert.h>
#include <exception>

template<typename T>
class List : public Interface<T>
{
public:
	List();

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
		friend class List;
	public:
		Iterator() = default;
		
		Iterator operator + (size_t a);			// moves iterator forward  a times
		Iterator operator - (size_t a);			//				  backward
		Iterator operator ++();
		Iterator operator ++ (int);
		Iterator operator --();
		Iterator operator -- (int);
		void operator = (Iterator a);
		T operator *();

	private:
		Node* cur;
	};

	void clear() override;
	bool empty() override;
	size_t size() override;
	void insert(const T& data, int pos) override;
	void erase(size_t index) override;
	void print();
	void push_back(const T& data) override;
	void push_front(const T& data) override;
	void pop_back() override;
	void pop_front() override;
	Iterator begin();
	Iterator end();
private:

	Node* head;
	size_t m_size;
};
//----------------------------------------------- List's functions -------------------------------------------------------------------------------------------------------

template <typename T>
List<T>::List()
	: head(nullptr)
	, m_size(0)
{
}

template<typename T>
inline void List<T>::clear()
{
	while (head != nullptr) {
		Node* a;
		a = head;
		head = head->next;
		delete a;
		--m_size;
	}
}

template<typename T>
inline bool List<T>::empty()
{
	return (head == nullptr) ? 1 : 0;
}

template<typename T>
inline size_t List<T>::size()
{
	return m_size;
}

template<typename T>
inline void List<T>::insert(const T& data, int pos)
{
	assert(pos > 0);
	if (pos > m_size + 1) {
		throw std::out_of_range("Invalid size");
	}
	if (pos == 1) {
		if(head == nullptr){
			head = new Node(data, nullptr, nullptr);
			return;
		}
		else {
			head->prev = new Node(data, nullptr, head);
			head = head->prev;
			++m_size;
			return;
		}
	}
	Node* tempdecr = nullptr;
	Node* temp = head;
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
inline void List<T>::erase(size_t index)
{
	assert(index > 0);
	if (index > m_size) {
		throw std::out_of_range("Invalid size");
	}

	if (index == 1) {
		Node* a = head;
		head = head->next;
		delete a;
		--m_size;
		return;
	}
	Node* tempdecr = nullptr;
	Node* temp = head;
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
inline void List<T>::print()
{
	Node* a = head;
	while (a != nullptr) {
		std::cout << a->Data << std::endl;
		a = a->next;
	}
	std::cout << "-------------------------------------------" << std::endl;

}
//----------------------------------------------- List's  Push,   Pop ---------------------------------------------------------------------------------------------------
template<typename T>
inline void List<T>::push_back(const T& data)
{
	Node* temp = head;
	for (size_t i = 0; i < m_size; ++i) {
		if (temp->next != nullptr)
		{
			temp = temp->next;
		}
	}
	temp->next = new Node(data, temp, nullptr);

}

template<typename T>
inline void List<T>::push_front(const T & data)
{
	if (head == nullptr) {
		head = new Node(data, nullptr, nullptr);
		return;
	}
	else {
		head->prev = new Node(data, nullptr, head);
		head = head->prev;
		++m_size;
		return;
	}
	++m_size;
}

template<typename T>
inline void List<T>::pop_back()
{
	Node* tempdecr = nullptr;
	Node* temp = head;
	while (temp->next != nullptr) {
		tempdecr = temp;
		temp = temp->next;
	}
	tempdecr->next = nullptr;
	delete temp;
	--m_size;
}

template<typename T>
inline void List<T>::pop_front()
{
	Node* temp = head;
	head = head->next;
	delete temp;
}

//-----------------------------------------------List's	Begin,	End---------------------------------------------------------------------------------------------------------
template<typename T>
typename List<T>::Iterator List<T>::begin()
{
	Iterator it;
	it.cur = List::head;
	return it;
}

template<typename T>
typename List<T>::Iterator List<T>::end()
{
	Iterator it;
	it.cur = List::head;
	while (it.cur->next != nullptr) {
		it.cur = it.cur->next;
	}
	return it;
}

//----------------------------------------------- Iterator's operators ---------------------------------------------------------------------------------------------------------

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator+(size_t a)
{
	Iterator current;
	assert(cur != nullptr);
	current.cur = cur;
	for (size_t i = 0; i < a; ++i) {
		assert(current.cur->next != nullptr);
		current.cur = current.cur->next;
	}
	return current;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator-(size_t a)
{
	Iterator current;
	assert(cur != nullptr);
	current.cur = cur;
	for (size_t i = 0; i < a; ++i) {
		assert(current.cur->prev != nullptr);
		current.cur = current.cur->prev;
	}
	return current;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int)
{

	Iterator current;
	assert(cur != nullptr);
	current.cur = cur;
	assert(current.cur->next != nullptr);
	current.cur = current.cur->next;
	return current;

}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator++()
{
	assert(cur != nullptr);
	assert(cur->next != nullptr);
	cur = cur->next;
	return *this;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator--()
{
	assert(cur != nullptr);
	assert(cur->prev != nullptr);
	cur = cur->prev;
	return *this;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator--(int)
{
	Iterator current;
	assert(cur != nullptr);
	current.cur = cur;
	assert(current.cur->prev != nullptr);
	current.cur = current.cur->prev;
	return current;

}

template<typename T>
inline void List<T>::Iterator::operator=(Iterator a)
{
	cur = a.cur;
}

template<typename T>
inline T List<T>::Iterator::operator*()
{
	return cur->Data;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------