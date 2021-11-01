//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 31/10/21.
//
// Copyright © 2021. All rights reserved.
//
//

#ifndef INTEGRALA_TREES_H
#define INTEGRALA_TREES_H

#include <vector>
#include "../../Module.h"
#include "bst.h"

class Trees : public Module {
private:
    vector<BST<int>> arboles;
public:
    explicit Trees(Application *application) : Module(application, "Trees Handler") {}

    void start() override;

    void end() override;

    void menu() override;
};


#endif //INTEGRALA_TREES_H
