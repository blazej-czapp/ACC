#pragma once
#include <stdexcept>
#include "Iterator.hpp"
#include "AbstractIterator.hpp"

#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif  

namespace acc {

template <typename T>
class LinkedListIterator;
template <typename T>
class LinkedListReverseIterator;

template <typename T>
class Node {
public:
	Node<T> *prev, *next;
	T element;
public:
	Node(T p_element) : element(p_element)
	{
		next = NULL;
		prev = NULL;
	}
};


template <typename T>
class LinkedList {
	friend class LinkedListIterator<T>;
private:
	int m_size;
	Node<T> *head, *tail;
public:
	LinkedList() {
		this->head = NULL;
		this->tail = NULL;
		m_size = 0;
	}

	LinkedList(LinkedList<T> &other) : LinkedList()
	{
		for(Iterator<T> it = other.iterator();it.hasCurrent();it.next()) {
			this->add(it.get());
		}
	}

	void add(T element) {
		if (head == NULL) {
			head = new Node<T>(element);
			tail = head;
		}
		else {
			tail->next = new Node<T>(element);
			tail->next->prev = tail;
			tail = tail->next;
		}
		m_size++;
	}

	bool addAt(int index, T element) {
		if(index == 0) {
			Node<T> *new_one = new Node<T>(element);
			new_one->next = head;
			head->prev = new_one;
			head = new_one;
			m_size++;
			return true;
		} 

		if(index == m_size-1) {
			Node<T> *new_one = new Node<T>(element);
			new_one->prev = tail->prev;
			new_one->next = tail;
			tail->prev->next = new_one;
			m_size++;
			return true;
		} 

		//Middle element.
		Node<T> *node = head;
		int position = 0;
		while(position < index) {
			if(node == NULL) {
				return false;
			}
			node = node->next;
			position++;
		}

		Node<T> *new_one = new Node<T>(element);
		node->prev->next = new_one;
		new_one->next = node;
		new_one->prev = node->prev;
		node->prev = new_one;

		m_size++;
		return true;
	}

	T get(int index) {
		int position = 0;
		Node<T> *current_node = head;
		while (position < index) {
			if (current_node != NULL) {
				current_node = current_node->next;
				position++;
			} else {
				break;
			}
		}

		if (current_node != NULL) {
			return current_node->element;
		} else {
			//TODO: ...
			//throw std::exception("LinkedList get could not reach element.");
		}
	}

	/* Returns true if element was found. */
	bool remove(const T& object) {
		Node<T>* current_node = head;
		while (true) {
			if (current_node == NULL) {
				return false;	
			} 
			if (current_node->element == object) {
				break;
			}
			current_node = current_node->next;
		}

		delete_node(current_node);
		return true; 
	}

	bool removeAt(const int index) {
		int position = 0;
		Node<T>* current_node = head;
		while (position < index) {
			if (current_node == NULL) {
				return false;
			}
			current_node = current_node->next;
			position++;
		}
		delete_node(current_node);
		return true;
	}

	int size() {
		return m_size;
	}

	Iterator<T> iterator() {
		return Iterator<T>(new LinkedListIterator<T>(this));
	}

	Iterator<T> reverse() {
		return Iterator<T>(new LinkedListReverseIterator<T>(this));
	}

	~LinkedList() {
		while (tail != NULL)
		{
			delete_node(tail);
		}
	}

private:
	void delete_node(Node<T>* node) {
		if (node == head) {
			head = node->next; //Uses fact thet next is NULL when there is no next.
		}
		if (node == tail) {
			tail = node->prev; //Uses fact that prev is NULL when there is no prev.
		}
		if (node->prev != NULL) {
			node->prev->next = node->next;
		}
		if (node->next != NULL) {
			node->next->prev = node->prev;
		}
		--m_size;
		delete node;
	}
};

template <typename T>
class LinkedListIterator : public AbstractIterator<T> {
private:
	LinkedList<T> *list;
	Node<T> *current, *nextAfterDelete;
	int position;
public:
	LinkedListIterator(LinkedList<T> *p_list) : list(p_list)
	{
		current = list->head;
		nextAfterDelete = NULL;
		position = 0;
	}

	virtual bool hasCurrent() {
		return current != NULL || nextAfterDelete != NULL;
	}

	virtual int index() {
		return position;
	}

	virtual void next() {
		if(current == NULL && nextAfterDelete != NULL) {
			current = nextAfterDelete;
			nextAfterDelete = NULL;
		} else if(current != NULL) {
			current = current->next;
			position++;
		} else {
			//TODO: Throw something.
		}
	}

	virtual T& get() {
		if(current != NULL) {
			return current->element;
		} else {
			//TODO: Throw something.
		}
	}

	virtual void remove() {
		nextAfterDelete = current->next;
		list->delete_node(current);
		current = NULL;
	}

	virtual ~LinkedListIterator() {

	}
};

template<typename T>
class LinkedListReverseIterator : public AbstractIterator<T> {
private:
	LinkedList<T> *list;
	Node<T> *current;
	Node<T> *prev;
public:
	LinkedListReverseIterator(LinkedList<T> *p_list) : list(p_list)
	{
		current = list->tail;
		prev = NULL;
	}

	virtual bool hasNext() {
		return current != NULL;
	}

	virtual T& next() {
		if(current != NULL) {
			prev = current;
			current = current->prev;
			return prev->element;
		} else {
			//TODO: ...
		}
	}

	virtual void remove() {
		if(prev != NULL) {
			list->delete_node(prev);
		} else {
			//TODO: ...
		}
	}
};

} //namespace acc