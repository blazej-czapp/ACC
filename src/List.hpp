#pragma once
#include "Iterator.hpp"

namespace acc {

template<typename T>
class List {
public:
	virtual T& operator[](size_t index) = 0;
	virtual const T& operator[](size_t index) const = 0;
	virtual void add(T element) = 0;
	virtual void addAt(size_t index, T element) = 0;
	virtual bool remove(const T &element) = 0;
	virtual void removeAt(size_t index) = 0;
	virtual bool contains(const T &element) const = 0;
	virtual size_t indexOf(const T &element) const = 0;
	virtual size_t lastIndexOf(const T &element) const = 0;
	
	virtual Iterator<T> iterator() = 0;
	virtual size_t size() const = 0;
	virtual void clear() = 0;
};

//TODO: as abstract functions:
//bool addAll(List<T> &iterator);
//bool addAll(List<T> &target, size_t index, List<T> &source);
//bool containsAll()
//

	
} //end of namespace acc