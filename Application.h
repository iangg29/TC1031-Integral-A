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

#include "Module.h"

#include "modules/Utils/Utils.h"
#include "modules/Time/Time.h"
#include "modules/Sorting/Sort.h"
#include "modules/Searching/Search.h"
#include "modules/Data/FakeData.h"

using namespace std;

class Application {
private:
    string name;
    string author;
    float version;
    bool debug;
    unsigned int startTime;
    unsigned int finishTime;
    vector<Module *> modules;

    Utils *utils = nullptr;
    Time *time = nullptr;
    Sort *sort = nullptr;
    Search *search = nullptr;
    FakeData *fakeData = nullptr;

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

    void addModule(Module *);

    Utils *getUtilsHandler();

    Time *getTimeHandler();

    Sort *getSortHandler();

    Search *getSearchHandler();

    FakeData *getFakeDataHandler();
};


#endif //INTEGRALA_APPLICATION_H
