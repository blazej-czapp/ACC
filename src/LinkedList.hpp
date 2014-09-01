#pragma once
#include <stdexcept>

#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif  

template <typename T>
class LinkedListIterator;

template<typename T>
class Iterator {
private:
	Iterator<T>* iterator;
public:
	Iterator(Iterator<T>* p_iterator) : iterator(p_iterator)
	{
	}

	virtual T operator*() {
		return *(*iterator);
	}

	virtual bool hasNext() {
		return iterator->hasNext();
	}

	virtual void next() {
		iterator->next();
	}

	virtual void remove() {
		iterator->remove();
	}

	virtual ~Iterator() {
		delete iterator;
	}
};

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

	void addAt(int index, T element) {

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
			throw std::exception("LinkedList get could not reach element.");
		}
	}

	/* Returns true if element was found. */
	bool remove(const T& object) {
		Node* current_node = head;
		while (true) {
			if (current_node == NULL) return false;
			if (current_node->element == object) break;
			current_node = current_node->next;
		}

		delete_node(current_node);
		return true; 
	}

	bool removeAt(const int index) {
		int position = 0;
		Node* current_node = head;
		while (position < index) {
			if (current_node == NULL) return false;
			current_node = current_node->next;
		}
		delete_node(current_node);
		return true;
	}

	int size() {
		return m_size;
	}

	Iterator<T> iter() {
		return Iterator<T>(new LinkedListIterator<T>(this));
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
class LinkedListIterator : public Iterator<T> {
private:
	LinkedList<T> *list;
	Node<T> *current;
	bool current_element_was_removed;
public:
	LinkedListIterator(LinkedList<T> *p_list) : 
		Iterator(NULL),
		list(p_list)
	{
		current = list->head;
		current_element_was_removed = false;
	}

	T operator*() {
		if (current_element_was_removed) {
			throw std::exception("Current element was removed!");
		}

		if (current != NULL) {
			return current->element;
		} else {
			throw std::exception("LinkedListIterator operator* access to wrong element.");
		}
	}

	virtual bool hasNext() {
		if (current_element_was_removed) {
			throw std::exception("Current element was removed!");
		}

		return current != NULL;
	}

	virtual void next() {
		if (current_element_was_removed) {
			current_element_was_removed = false;
			return; //Do nothing remove moved pointer to next.
		}

		if (current != NULL) {
			current = current->next;
		} else {
			throw std::exception("LinkedListIterator next gone to far.");
		}
	}

	virtual void remove() {
		Node<T>* next_current = current->next;
		list->delete_node(current);
		current = next_current;
		current_element_was_removed = true;
	}

	virtual ~LinkedListIterator() {

	}
};