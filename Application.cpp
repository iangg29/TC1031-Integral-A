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
#include "Application.h"

Application::Application(string name, bool debug) {
    this->name = name;
    this->debug = debug;
    this->version = 0.1;
}

Application::~Application() {
    delete getUtilsHandler();
    delete getTimeHandler();
};

void Application::start() {
    this->startTime = getTimeHandler()->getMillis();
    this->utils = new Utils(this);
    this->time = new Time(this);
    this->finishTime = getTimeHandler()->getMillis();
    log("Application started in [" + to_string((finishTime - startTime)) + "] ms.");
}

void Application::end() {
    for (Module *module: getModules()) {
        module->end();
    }
}


vector<Module *> Application::getModules() {
    return this->modules;
}

void Application::addModule(Module *module) {
    getModules().push_back(module);
}

Application *Application::getApplication() {
    return this;
}

const Application *Application::getApplication() const {
    return this;
}

bool Application::isDebug() const {
    return this->debug;
}

string Application::getName() {
    return this->name;
}

string Application::getAuthor() {
    return this->author;
}

float Application::getVersion() {
    return this->version;
}

int Application::getStartTime() {
    return this->startTime;
}

int Application::getFinishTime() {
    return this->finishTime;
}

void Application::log(string message) {
    cout << message << endl;
}

Utils *Application::getUtilsHandler() {
    return this->utils;
}

Time *Application::getTimeHandler() {
    return this->time;
}



