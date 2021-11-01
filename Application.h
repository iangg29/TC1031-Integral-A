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
#pragma once

#ifndef INTEGRALA_APPLICATION_H
#define INTEGRALA_APPLICATION_H

#include <iostream>
#include <string>
#include <vector>
#include <modules/Trees/Trees.h>
#include <modules/CLI/Cli.h>

#include "Module.h"

#include "modules/Utils/Utils.h"
#include "modules/Time/Time.h"
#include "modules/Sorting/Sort.h"
#include "modules/Searching/Search.h"
#include "modules/Data/FakeData.h"
#include "modules/Lists/Lists.h"

using namespace std;

class Application {
private:
    string name;
    string author;
    float version;
    bool debug;
    bool started = false;
    unsigned int startTime;
    unsigned int finishTime;
    vector<Module *> modules;

    CLI *cli = nullptr;
    Utils *utils = nullptr;
    Time *time = nullptr;
    Sort *sort = nullptr;
    Search *search = nullptr;
    FakeData *fakeData = nullptr;
    Lists *lists = nullptr;
    Trees *trees = nullptr;

    string getName();

    string getAuthor();

    float getVersion();

    Application *getApplication();

    const Application *getApplication() const;

    void setName(string);

    void setAuthor(string);

    void setVersion(float);

    void setDebug(bool);

public:
    Application(string, bool, float);

    ~Application();

    void init();

    void stop();

    bool isDebug();

    bool isStarted();

    void addModule(Module *);

    CLI *getCLIHandler();

    Utils *getUtilsHandler();

    Time *getTimeHandler();

    Sort *getSortHandler();

    Search *getSearchHandler();

    FakeData *getFakeDataHandler();

    Trees *getTreesHandler();
};


#endif //INTEGRALA_APPLICATION_H
