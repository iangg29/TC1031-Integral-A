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

#ifndef INTEGRALA_SEARCH_H
#define INTEGRALA_SEARCH_H

#include <vector>
#include "../../Module.h"

class Search : Module {
private:
    int helper(vector<int>, int, int, int);

public:
    Search(Application *application) : Module(application, "Searching Handler") {}

    void start() override;

    void end() override;

    void menu() override;

    int binarySearch(const vector<int> &, int);
};


#endif //INTEGRALA_SEARCH_H
