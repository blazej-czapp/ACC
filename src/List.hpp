#pragma once
#include "Iterator.hpp"

namespace acc {

template<typename T>
class List {
public:
	virtual T& operator[](int index) = 0;
	virtual const T& operator[](int index) const = 0;
	virtual void add(T element) = 0;
	virtual void addAt(int index, T element) = 0;
	virtual bool remove(const T &element) = 0;
	virtual bool removeAt(int index) = 0;
	virtual bool contains(const T &element) const = 0;
	virtual int indexOf(const T &element) const = 0;
	virtual int lastIndexOf(const T &element) const = 0;
	
	virtual Iterator<T> iterator() = 0;
	virtual int size() const = 0;
	virtual void clear() = 0;
	virtual ~List() { }
};

//TODO: as abstract functions:
//bool addAll(List<T> &iterator);
//bool addAll(List<T> &target, size_t index, List<T> &source);
//bool containsAll()
//

	
} //end of namespace acc