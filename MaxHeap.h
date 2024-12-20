#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <bits/stdc++.h>

using namespace std;

template<typename T>
class MaxHeap {
private:
    vector<pair<int, T>> arr;
    void heapify_up(int ind);
    void heapify_down(int ind);

public:
    MaxHeap();
    void insert(int prio, T a);
    T extract_mx();
    T get_mx() const;
    bool empty() const;
    void cout_mxheap() const;
};

template<typename T>
MaxHeap<T>::MaxHeap() {}

template<typename T>
void MaxHeap<T>::heapify_up(int ind) {
    while (ind > 0) {
        int par_ind = (ind - 1) / 2;
        if (arr[ind].first > arr[par_ind].first) {
            swap(arr[ind], arr[par_ind]);
            ind = par_ind;
        } else break;
    }
}

template<typename T>
void MaxHeap<T>::heapify_down(int ind) {
    int l = ind * 2 + 1, r = ind * 2 + 2, mx = ind;
    if (l < arr.size() && arr[l].first > arr[mx].first) mx = l;
    if (r < arr.size() && arr[r].first > arr[mx].first) mx = r;
    if (mx != ind) {
        swap(arr[ind], arr[mx]);
        heapify_down(mx);
    }
}

template<typename T>
void MaxHeap<T>::insert(int prio, T a) {
    arr.push_back({prio, a});
    heapify_up(arr.size() - 1);
}

template<typename T>
T MaxHeap<T>::extract_mx() {
    if (arr.empty()) throw out_of_range("The Heap is empty!");
    T top_value = arr[0].second;
    arr[0] = arr.back();
    arr.pop_back();
    heapify_down(0);
    return top_value;
}

template<typename T>
T MaxHeap<T>::get_mx() const {
    if (arr.empty()) throw out_of_range("The Heap is empty!");
    return arr[0].second;
}

template<typename T>
bool MaxHeap<T>::empty() const {
    return arr.empty();
}

template<typename T>
void MaxHeap<T>::cout_mxheap() const {
    for (const auto& elem : arr) {
        cout << "[" << elem.first << ", " << elem.second << "] ";
    }
    cout << endl;
}

#endif


