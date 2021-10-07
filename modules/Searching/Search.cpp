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

#include "Search.h"

void Search::start() {}

void Search::end() {}

void Search::menu() {}

int Search::binarySearch(const vector<int> &v, int target) {
    vector<int> vec(v);
    return helper(vec, 0, vec.size() - 1, target);
}

int Search::helper(vector<int> v, int low, int high, int target) {
    if (low < high) {
        int mid = (high + low) / 2;
        if (target == v[mid]) {
            return mid;
        } else if (target < v[mid]) {
            return helper(v, low, mid - 1, target);
        } else if (target > v[mid]) {
            return helper(v, mid + 1, high, target);
        }
    }
    return -1;
}