//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 29/11/21.
//
// Copyright © 2021. All rights reserved.
//
//

#ifndef INTEGRALA_SORTS_H
#define INTEGRALA_SORTS_H

#include <vector>

#include "../models/Extra.h"

/**
 * @brief The Sorts class
 */
class Sorts {
private:
    void mergeSplit(std::vector<LapTime> &, std::vector<LapTime> &, int, int);

    static void mergeArray(std::vector<LapTime> &, std::vector<LapTime> &, int, int, int);

    static void copyArray(std::vector<LapTime> &, std::vector<LapTime> &, int, int);

public:
    void mergeSort(std::vector<LapTime> &);
};

/**
 * @brief Merge sort algorithm for a vector of LapTimes
 * 
 * @param v 
 */
void Sorts::mergeSort(std::vector<LapTime> &v) {
    std::vector<LapTime> temp(v.size());
    mergeSplit(v, temp, 0, v.size() - 1);
}

/**
 * @brief Merge sort helper function
 * 
 * @param A 
 * @param B 
 * @param low 
 * @param high 
 */
void Sorts::mergeSplit(std::vector<LapTime> &A, std::vector<LapTime> &B, int low, int high) {
    if ((high - low) < 1) return;
    int mid = (high + low) / 2;
    mergeSplit(A, B, low, mid);
    mergeSplit(A, B, mid + 1, high);
    mergeArray(A, B, low, mid, high);
    copyArray(A, B, low, high);
}

/**
 * @brief Function that merges two arrays
 * 
 * @param A 
 * @param B 
 * @param low 
 * @param mid 
 * @param high 
 */
void Sorts::mergeArray(std::vector<LapTime> &A, std::vector<LapTime> &B, int low, int mid, int high) {
    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high) {
        if (A[i].milli < A[j].milli) {
            B[k] = A[i];
            i++;
        } else {
            B[k] = A[j];
            j++;
        }
        k++;
    }
    if (i < mid) {
        while (j <= high) {
            B[k++] = A[j];
            j++;
        }
    } else {
        while (i <= mid) {
            B[k++] = A[i];
            i++;
        }
    }
}

/**
 * @brief Copy the elements of B into A
 * 
 * @param A 
 * @param B 
 * @param low 
 * @param high 
 */
void Sorts::copyArray(std::vector<LapTime> &A, std::vector<LapTime> &B, int low, int high) {
    for (int i = low; i <= high; ++i) {
        A[i] = B[i];
    }
}


#endif //INTEGRALA_SORTS_H
