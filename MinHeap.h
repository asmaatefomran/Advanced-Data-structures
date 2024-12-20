#ifndef MINHEAP_H
#define MINHEAP_H

#include <bits/stdc++.h>

using namespace std;

template<typename T>
class MinHeap {
private:
    vector<pair<int, T>> arr;
    void heapify_up(int ind);
    void heapify_down(int ind);

public:
    MinHeap();
    void insert(int prio, T a);
    T extract_mn();
    T get_mn() const;
    bool empty() const;
    void cout_mnheap() const;
};

template<typename T>
MinHeap<T>::MinHeap() {}

template<typename T>
void MinHeap<T>::heapify_up(int ind) {
    while (ind > 0) {
        int par_ind = (ind - 1) / 2;
        if (arr[ind].first < arr[par_ind].first) {
            swap(arr[ind], arr[par_ind]);
            ind = par_ind;
        } else break;
    }
}

template<typename T>
void MinHeap<T>::heapify_down(int ind) {
    int l = ind * 2 + 1, r = ind * 2 + 2, mn = ind;
    if (l < arr.size() && arr[l].first < arr[mn].first) mn = l;
    if (r < arr.size() && arr[r].first < arr[mn].first) mn = r;
    if (mn != ind) {
        swap(arr[ind], arr[mn]);
        heapify_down(mn);
    }
}

template<typename T>
void MinHeap<T>::insert(int prio, T a) {
    arr.push_back({prio, a});
    heapify_up(arr.size() - 1);
}

template<typename T>
T MinHeap<T>::extract_mn() {
    if (arr.empty()) throw out_of_range("The Heap is empty!");
    T top_value = arr[0].second;
    arr[0] = arr.back();
    arr.pop_back();
    heapify_down(0);
    return top_value;
}

template<typename T>
T MinHeap<T>::get_mn() const {
    if (arr.empty()) throw out_of_range("The Heap is empty!");
    return arr[0].second;
}

template<typename T>
bool MinHeap<T>::empty() const {
    return arr.empty();
}

template<typename T>
void MinHeap<T>::cout_mnheap() const {
    for (const auto& elem : arr) {
        cout << "[" << elem.first << ", " << elem.second << "] ";
    }
    cout << endl;
}

#endif
