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

template<typename T>
class ArrayIterator;

template<typename T>
class Array {

   friend class ArrayIterator<T>;

public:
    explicit Array(size_t initialCapacity = 10) : m_size(0), 
                                                  m_capacity(initialCapacity > 1 ? initialCapacity : static_cast<size_t>(1)),
                                                  m_content(new T[m_capacity]) {}

    Array(const Array& other) : m_size(other.m_size), m_capacity(other.m_capacity), m_content(new T[m_capacity]) {
        std::copy(other.m_content, other.m_content + other.m_size, m_content);
    }

    virtual ~Array<T>() {
        delete[] m_content;
    }

    T& operator[](size_t index) {
        BOUNDS_CHECK(index, m_size);
        return m_content[index];
    }

    const T& operator[](size_t index) const {
        BOUNDS_CHECK(index, m_size);
        return m_content[index];
    }

    void add(T element) {
        if (m_size + 1 > m_capacity) {
            m_capacity = (m_capacity * 3) / 2 + 1;
            T* newContent = new T[m_capacity];
            std::copy(m_content, m_content + m_capacity, newContent);
            delete[] m_content;
            m_content = newContent;
        }
        m_content[m_size++] = element;
    }

    void removeAt(size_t index) {
        BOUNDS_CHECK(index, m_size);
        std::copy(m_content + index + 1, m_content + m_size, m_content + index);
        m_size--;
    }

    size_t size() const {
        return m_size;
    }

    Iterator<T> iter() {
        return Iterator<T>(new ArrayIterator<T>(*this));
    }

    friend std::ostream& operator<<(std::ostream &out, const Array<T>& vec) {
        out << "[";
        for (size_t i = 0; i < vec.m_size; i++) {
            out << vec.m_content[i];

            if (i < vec.m_size - 1) {
                out << ", ";
            }
        }

        out << "]";
        return out;
    }

private:
    size_t m_size;
    size_t m_capacity;
    T* m_content;
};

template<typename T>
class ArrayIterator : public AbstractIterator<T> {
public:
    ArrayIterator(Array<T>& parent) : m_parent(parent), m_currentIndex(0) {}

    virtual T& get() {
        BOUNDS_CHECK(m_currentIndex, m_parent.m_size);
        return m_parent[m_currentIndex];
    }

    virtual bool isValid() {
        return m_currentIndex < m_parent.m_size;
    }

    virtual void next() {
        m_currentIndex++;
    }

    virtual void remove() {
        BOUNDS_CHECK(m_currentIndex, m_parent.m_size);
        m_parent.removeAt(m_currentIndex);
    }

    virtual ~ArrayIterator() {}

private:
    Array<T>& m_parent;
    size_t m_currentIndex;
};

} // namespace acc
