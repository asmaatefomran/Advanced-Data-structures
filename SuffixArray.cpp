#include "SuffixArray.h"

SuffixArray::SuffixArray(char* ss) {
    n = strlen(ss);
    s = new char[n + 1];
    for (int i = 0; i < n; ++i)
        s[i] = ss[i];
    s[n] = '\0';
    indx = new int[n];
    ord = new int[n];
    curr = new int[n];
}

auto SuffixArray::comp(int a, int b, int nxt) {
    if (ord[a] != ord[b])
        return ord[a] < ord[b];
    int ri = (a + nxt < n) ? ord[a + nxt] : -1;
    int rj = (b + nxt < n) ? ord[b + nxt] : -1;
    return ri < rj;
}

void SuffixArray::manualsort(int* v, int l, int r, int nxt) {
    if (l >= r) return;

    int mid = (l + r) / 2;
    manualsort(v, l, mid, nxt);
    manualsort(v, mid + 1, r, nxt);

    int* vv = new int[r - l + 1];
    int i = l, j = mid + 1, k = 0;

    while (i <= mid && j <= r) {
        if (comp(v[i], v[j], nxt)) {
            vv[k] = v[i];
            i++; k++;
        } else {
            vv[k] = v[j];
            j++; k++;
        }
    }
    while (i <= mid) {
        vv[k] = v[i];
        k++; i++;
    }
    while (j <= r) {
        vv[k] = v[j];
        k++; j++;
    }

    for (int i = 0; i < k; ++i) {
        v[l + i] = vv[i];
    }

    delete[] vv;
}

void SuffixArray::build() {
    for (int i = 0; i < n; ++i) {
        indx[i] = i;
        ord[i] = s[i] - 'A';
    }

    for (int nxt = 1; nxt < n; nxt *= 2) {
        manualsort(indx, 0, n - 1, nxt);
        curr[indx[0]] = 0;
        for (int i = 1; i < n; ++i) {
            curr[indx[i]] = curr[indx[i - 1]] + (comp(indx[i - 1], indx[i], nxt) ? 1 : 0);
        }
        for (int i = 0; i < n; ++i) {
            ord[i] = curr[i];
        }
    }
}


void SuffixArray::print() {
    for (int i = 0; i < n; ++i) {
        cout << indx[i] << ' ';
    }
    cout << endl;
}


SuffixArray::~SuffixArray() {
    delete[] s;
    delete[] indx;
    delete[] ord;
    delete[] curr;
}
