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

#ifndef INTEGRALA_SORT_H
#define INTEGRALA_SORT_H

#include "../../Module.h"
#include <vector>

class Sort : Module {
private:
    void copyVector(vector<int> &, vector<int> &, int, int);

    void mergeVector(vector<int> &, vector<int> &, int, int, int);

    void mergeSplit(vector<int> &, vector<int> &, int, int);

public:
    Sort(Application *application) : Module(application, "Sorting Handler") {}

    void start() override;

    void end() override;

    void menu() override;

    void mergeSort(vector<int> &);
};


#endif //INTEGRALA_SORT_H
