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


#ifndef ACC_ITERATOR
#define ACC_ITERATOR

#include <memory>

#include "AbstractIterator.hpp"

namespace acc {

/*
 * An adapter allowing different concrete iterator implementations to be used through a single object type.
 */
template<typename T>
class Iterator : public AbstractIterator<T> {
public:
    Iterator(AbstractIterator<T>* iterator) : m_iterator(iterator) {}
    Iterator(const Iterator<T>& other) : m_iterator(other.m_iterator) {}

    virtual T& get() {
        return m_iterator->get();
    }

    virtual bool isValid() {
        return m_iterator->isValid();
    }

    virtual void next() {
        m_iterator->next();
    }

    virtual void remove() {
        m_iterator->remove();
    }

    virtual ~Iterator() {}

private:
    std::shared_ptr<AbstractIterator<T>> m_iterator;
};

} // namespace acc

#endif // ACC_ITERATOR