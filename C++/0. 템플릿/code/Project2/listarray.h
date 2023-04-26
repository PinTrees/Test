#pragma once
#include <iostream>
#include <string>
#include "listbase.h"

template <typename T>
class ArrayList : public ListBase<T>
{
    T* data;
    int capacity;
    int length;

public:
    // »ý¼ºÀÚ
    ArrayList(int n = 1) : data(new T[n]), capacity(n), length(0) {}


    void ForEach(std::function<void(T)> fptr) override {
        for (int i = 0; i < length; i++) fptr(data[i]);
    }


    void push_back(T s) {
        if (capacity <= length) {
            T* temp = new T[capacity * 2];
            for (int i = 0; i < length; i++) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
            capacity *= 2;
        }

        data[length] = s;
        length++;
    }
    T operator[](int i) { return data[i]; }
    void remove(int x) {
        for (int i = x + 1; i < length; i++) {
            data[i - 1] = data[i];
        }
        length--;
    }
    int size() { return length; }

    ~ArrayList() {
        if (data) {
            delete[] data;
        }
    }
};