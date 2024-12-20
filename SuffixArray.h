#ifndef SUFFIXARRAY_H
#define SUFFIXARRAY_H

#include <iostream>
#include <cstring>

using namespace std;

class SuffixArray {
private:
    int n;
    char* s;
    int* indx, *ord, *curr;
    auto comp(int a, int b, int nxt);
    void manualsort(int* v, int l, int r, int nxt);

public:
    SuffixArray(char* ss);
    void build();
    void print();
    ~SuffixArray();
};

#endif
