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

#ifndef INTEGRALA_APPLICATION_H
#define INTEGRALA_APPLICATION_H

#include <vector>
#include <iostream>
#include <string>

#include "Module.h"
#include "iStart.h"

#include "modules/Utils/Utils.h"
#include "modules/Time/Time.h"

using namespace std;

class Application : public iStart {
private:
    string name;
    const string author = "Ian García";
    bool debug;
    float version;
    unsigned int startTime = 0;
    unsigned int finishTime = 0;
    vector<Module *> modules;
    vector<Module *> getModules();

    Utils *utils = nullptr;
    Time *time = nullptr;

public:
    Application(string name, bool debug);

    ~Application();

    void start() override;

    void end() override;

    bool isDebug() const;

    Application *getApplication();

    const Application *getApplication() const;

    string getName();

    string getAuthor();

    float getVersion();

    int getStartTime();

    int getFinishTime();

    void log(string);

    void addModule(Module *);

    Utils *getUtilsHandler();
    Time *getTimeHandler();
};


#endif //INTEGRALA_APPLICATION_H
