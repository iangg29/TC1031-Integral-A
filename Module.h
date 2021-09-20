//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 18/09/21.
//
// Copyright © 2021. All rights reserved.
//
//

#pragma once

#ifndef INTEGRALA_MODULE_H
#define INTEGRALA_MODULE_H

#include <iostream>
#include <string>

#include "iStart.h"

using namespace std;

class Application;

class Module : public iStart {
private:
    Application *application;
    string name;
    int startupTime;

protected:

    void log(const string &);

    void logWarn(const string &);

    void logFatal(const string &);

public:
    Module(Application *application, string name);

    virtual void start() = 0;

    virtual void end() = 0;

    virtual void menu() = 0;

    Application *getApplication();

    string getName();

    int getStartupTime() const;
};


#endif //INTEGRALA_MODULE_H
