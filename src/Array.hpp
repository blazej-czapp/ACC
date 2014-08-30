#ifndef ACC_ARRAY
#define ACC_ARRAY

#include <iostream>

namespace acc {

template<typename T>
class Array {
public:
    explicit Array(size_t initialCapacity = 10) : m_size(0), 
                                                  m_capacity(initialCapacity > 1 ? initialCapacity : static_cast<size_t>(1)) {
        allocStorage(m_capacity);
    }

    Array(const Array& other) : m_size(other.m_size), m_capacity(other.m_capacity) {
    	allocStorage(m_capacity);
    	std::copy(other.m_content, other.m_content + other.m_capacity, m_content);
    }

    virtual ~Array<T>() {
        delete[] m_content;
    }

    T& operator[](size_t index) {
        return m_content[index];
    }

	const T& operator[](size_t index) const {
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

    size_t size() const {
        return m_size;
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
    void allocStorage(size_t size) {
		m_content = new T[size];
    }

    T* m_content;
    size_t m_size;
    size_t m_capacity;
};

}

#endif // ACC_ARRAY