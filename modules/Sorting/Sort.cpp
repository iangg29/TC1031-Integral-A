//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 19/09/21.
//
// Copyright © 2021. All rights reserved.
//
//

#include "Sort.h"

void Sort::start() {}

void Sort::end() {}

void Sort::menu() {}

void Sort::mergeSort(vector<int> &v) {
    vector<int> temporal(v.size());
    mergeSplit(v, temporal, 0, v.size() - 1);
}

void Sort::mergeSplit(vector<int> &A, vector<int> &B, int low, int high) {
    if ((high - low) < 1) return;
    int mid = (high + low) / 2;
    mergeSplit(A, B, low, mid);
    mergeSplit(A, B, mid + 1, high);
    mergeVector(A, B, low, mid, high);
    copyVector(A, B, low, high);
}

void Sort::mergeVector(vector<int> &A, vector<int> &B, int low, int mid, int high) {
    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high) {
        if (A[i] < A[j]) {
            B[k] = A[i];
            ++i;
        } else {
            B[k] = A[j];
            ++j;
        }
        ++k;
    }
    if (i > mid) {
        while (j <= high) {
            B[k++] = A[j];
            ++j;
        }
    } else {
        while (i <= mid) {
            B[k++] = A[i];
            ++i;
        }
    }
}

void Sort::copyVector(vector<int> &A, vector<int> &B, int low, int high) {
    for (int i = low; i <= high; ++i) {
        A[i] = B[i];
    }
}
