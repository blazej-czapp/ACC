// The MIT License (MIT)

// Copyright (c) 2014 Błażej Czapp, Damian Powązka

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include <assert.h>

#include "List.hpp"
#include "AbstractIterator.hpp"
#include "Iterator.hpp"

#define BOUNDS_CHECK(index, size) {                                                                           \
                                assert(index >= 0);                                                           \
                                if (index >= size) {                                                          \
                                    throw std::out_of_range("Index out of bounds: " + std::to_string(index) + \
                                                             ", size: " + std::to_string(size));              \
                                }                                                                             \
                            }

namespace acc {

template<typename T> class ArrayIterator;
template<typename T> class ArrayReverseIterator;

template<typename T>
class ArrayList : public List<T> {
   friend class ArrayIterator<T>;
   friend class ArrayReverseIterator<T>;

private:
    int m_size;
    int m_capacity;
    T* m_content;

public:
    explicit ArrayList(int initialCapacity = 10) : 
        m_size(0), 
        m_capacity(initialCapacity > 1 ? initialCapacity : 1),
        m_content(new T[m_capacity]) 
    {


    }

    ArrayList(const ArrayList& other) : 
        m_size(other.m_size), 
        m_capacity(other.m_capacity), 
        m_content(new T[m_capacity]) 
    {
        std::copy(other.m_content, other.m_content + other.m_size, m_content);

    }

    virtual ~ArrayList<T>() {
        delete[] m_content;
    }

    virtual T& operator[](int index) {
        BOUNDS_CHECK(index, m_size);
        return m_content[index];
    }

    virtual const T& operator[](int index) const {
        BOUNDS_CHECK(index, m_size);
        return m_content[index];
    }

    virtual void add(T element) {
        if (m_size + 1 > m_capacity) {
            m_capacity = (m_capacity * 3) / 2 + 1;
            T* newContent = new T[m_capacity];
            std::copy(m_content, m_content + m_capacity, newContent);
            delete[] m_content;
            m_content = newContent;
        }
        m_content[m_size++] = element;
    }

    virtual void addAt(int index, T element) {
        if(m_size + 1 > m_capacity) {
            m_capacity = (m_capacity * 3) / 2 + 1;
            T* newContent = new T[m_capacity];
            std::copy(m_content, m_content + index, newContent);
            std::copy(m_content+index, m_content + m_size + 1, newContent + index + 1);
            delete[] m_content;
            m_content = newContent;   
            m_content[index] = element;
            m_size++;
        } else {
            for(int i=m_size-1; i>=index; i--) {
                m_content[i+1] = m_content[i];
            }
            m_content[index] = element;
            m_size++;
        }
    }

    virtual bool remove(const T &element) {
        for(int i=0;i<m_size;i++) {
            if(m_content[i] == element) {
                removeAt(i);
                return true;
            }
        }

        return false;
    }

    virtual void removeAt(int index) {
        BOUNDS_CHECK(index, m_size);
        std::copy(m_content + index + 1, m_content + m_size, m_content + index);
        m_size--;
    }

    virtual int size() const {
        return m_size;
    }

    virtual void clear() {
        //Should we reset m_content to initial size? 
        m_size = 0; 
    }

    virtual Iterator<T> iterator() {
        return Iterator<T>(new ArrayIterator<T>(*this));
    }

    virtual Iterator<T> reverse() {
        return Iterator<T>(new ArrayReverseIterator<T>(*this));
    }

    virtual bool contains(const T &element) const {
        for(int i=0;i<m_size;i++) {
            if(m_content[i] == element) {
                return true;
            }
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream &out, const ArrayList<T>& vec) {
        out << "[";
        for (int i = 0; i < vec.m_size; i++) {
            out << vec.m_content[i];

            if (i < vec.m_size - 1) {
                out << ", ";
            }
        }

        out << "]";
        return out;
    }
};

template<typename T>
class ArrayIterator : public AbstractIterator<T> {
private:
    ArrayList<T>& m_parent;
    int m_currentIndex;
    bool currentElementWasRemoved;
public:
    ArrayIterator(ArrayList<T> &parent) : 
        m_parent(parent), 
        m_currentIndex(0),
        currentElementWasRemoved(false)
    {

    }

    virtual T& get() {
        BOUNDS_CHECK(m_currentIndex, m_parent.m_size);
        return m_parent[m_currentIndex];
    }

    virtual bool hasCurrent() {
        return m_currentIndex < m_parent.m_size;
    }

    virtual void next() {
        if(!currentElementWasRemoved) {
            m_currentIndex++;
        } else {
            currentElementWasRemoved = false;
        }
        
    }

    virtual void remove() {
        BOUNDS_CHECK(m_currentIndex, m_parent.m_size);
        m_parent.removeAt(m_currentIndex);
        currentElementWasRemoved = true;
    }

    virtual int index() {
        return m_currentIndex;
    }

    virtual ~ArrayIterator() {}
};

template<typename T>
class ArrayReverseIterator : public AbstractIterator<T> {
private:
    ArrayList<T>& m_parent;
    int m_currentIndex;
public:
    ArrayReverseIterator(ArrayList<T> &parent) : 
        m_parent(parent), 
        m_currentIndex(parent.m_size-1)
    {

    }

    virtual T& get() {
        BOUNDS_CHECK(m_currentIndex, m_parent.m_size);
        return m_parent[m_currentIndex];
    }

    virtual bool hasCurrent() {
        return m_currentIndex >= 0;
    }

    virtual void next() {
        m_currentIndex--;
    }

    virtual void remove() {
        BOUNDS_CHECK(m_currentIndex, m_parent.m_size);
        m_parent.removeAt(m_currentIndex);
    }

    virtual int index() {
        return m_currentIndex;
    }

    virtual ~ArrayReverseIterator() {}
};

} // namespace acc
