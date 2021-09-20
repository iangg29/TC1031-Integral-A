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

#include "FakeData.h"
#include <stdlib.h>

void FakeData::start() {
    for (int i = 0; i < 100; ++i) {
        this->data.push_back(rand() % 100 + 1);
    }
}

void FakeData::end() {
    this->data.clear();
}

void FakeData::menu() {}


void FakeData::generateNewData() {
    this->data.clear();
    for (int i = 0; i < 100; ++i) {
        this->data.push_back(rand() % 100 + 1);
    }
}
