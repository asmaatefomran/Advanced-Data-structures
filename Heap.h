#ifndef HEAP_H
#define HEAP_H

#include <bits/stdc++.h>
#include "MaxHeap.h"
#include "MinHeap.h"

using namespace std;

template<typename T>
class Heap {
private:
    bool is_mx_heap;
    MaxHeap<T> mx;
    MinHeap<T> mn;

public:
    Heap(bool mxx = true);
    void insert(int priority, T value);
    T extract_top();
    T get_top() const;
    bool empty() const;
    void cout_heap() const;
    static void heapSort(std::vector<pair<int, T>>& arr, bool isMaxHeap = true);
};

template<typename T>
Heap<T>::Heap(bool mxx) : is_mx_heap(mxx) {}

template<typename T>
void Heap<T>::insert(int priority, T value) {
    if (is_mx_heap) mx.insert(priority, value);
    else mn.insert(priority, value);
}

template<typename T>
T Heap<T>::extract_top() {
    return (is_mx_heap ? mx.extract_mx() : mn.extract_mn());
}

template<typename T>
T Heap<T>::get_top() const {
    return (is_mx_heap ? mx.get_mx() : mn.get_mn());
}

template<typename T>
bool Heap<T>::empty() const {
    return (is_mx_heap ? mx.empty() : mn.empty());
}

template<typename T>
void Heap<T>::cout_heap() const {
    (is_mx_heap ? mx.cout_mxheap() : mn.cout_mnheap());
}

template<typename T>
void Heap<T>::heapSort(std::vector<pair<int, T>>& arr, bool isMaxHeap) {
    Heap<T> temp(isMaxHeap);
    for (const auto& elem : arr) temp.insert(elem.first, elem.second);
    for (int i = 0; i < arr.size(); ++i) {
        arr[i] = {arr[i].first, temp.extract_top()};
    }
}

#endif


