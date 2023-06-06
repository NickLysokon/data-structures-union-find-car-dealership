#ifndef _DYNAMIC_ARRAY_H
#define _DYNAMIC_ARRAY_H

#include <iostream>

static const int MIN_ARRAY_SIZE = 10;
static const int GROWTH_FACTOR = 2;

template <class T>
class Array {
    int m_capacity;
    T* m_data;

    void resize();

public:
    Array();
    ~Array();

    void set(int index, T value);
    T& get(int index);
};



template <class T>
Array<T>::Array() {
    m_capacity = MIN_ARRAY_SIZE;

    m_data = (T*)malloc(m_capacity * sizeof(T));
    if (!m_data)
        throw std::bad_alloc();
}

template <class T>
Array<T>::~Array() {
    free(m_data);
}


template <class T>
void Array<T>::set(int index, T value) {
    while (index >= m_capacity) {
        resize();
    }

    m_data[index] = value;  //T operator=
}


template <class T>
T& Array<T>::get(int index) {
    return *(m_data + index);
}

template <class T>
void Array<T>::resize() {
    int capacity = m_capacity * GROWTH_FACTOR;
    T* tmp = (T*)realloc(m_data, capacity * sizeof(T));
    if (!tmp) {
        throw std::bad_alloc();
    }

    m_data = tmp;
    m_capacity = capacity;
}


#endif