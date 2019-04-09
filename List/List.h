#pragma once
#include "IList.h"
#include <assert.h>
#include <exception>

template<typename T>
class List : public Interface<T>
{
public:
	List() : head(nullptr), m_size(0)
	{
	}

	void erase(size_t index) override;
	void clear() override;
	bool empty() override;
	size_t size() override;
	void insert(const T& data, int pos) override;
	void print();
private:
	struct Node {
		Node(const T& data, Node* n) : next(n), Data(data)
		{
		}
		Node* next;
		T Data;
	};

	Node* head;
	int m_size;
};

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
	tempdecr->next = temp->next;
	delete temp;
	--m_size;
}

template<typename T>
inline bool List<T>::empty()
{
	return head == nullptr;
	
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
		head = new Node(data, head);
		++m_size;
		return;
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
		tempdecr->next = new Node(data, temp);
	}
	else
	{
		temp->next = new Node(data, nullptr);
	}
	++m_size;
}

template<typename T>
inline void List<T>::print()
{
	Node* a = head;
	for (int i = 0; i < m_size; ++i) {
		std::cout << a->Data << std::endl;
		a = a->next;
	}
	std::cout << "-------------------------------------------" << std::endl;

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