#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <bits/stdc++.h>
#include "Heap.h"

using namespace std;

template<typename T>
class PriorityQueue {
private:
    Heap<T> pq;

public:
    PriorityQueue(bool isMaxHeap = true);
    void push(int priority, T value);
    T top();
    void pop();
    bool empty() const;
};

template<typename T>
PriorityQueue<T>::PriorityQueue(bool isMaxHeap) : pq(isMaxHeap) {}

template<typename T>
void PriorityQueue<T>::push(int priority, T value) {
    pq.insert(priority, value);
}

template<typename T>
T PriorityQueue<T>::top() {
    if (pq.empty()) throw out_of_range("The PriorityQueue is empty!");
    return pq.get_top();
}

template<typename T>
void PriorityQueue<T>::pop() {
    if (pq.empty()) throw out_of_range("The PriorityQueue is empty!");
    pq.extract_top();
}

template<typename T>
bool PriorityQueue<T>::empty() const {
    return pq.empty();
}

#endif

