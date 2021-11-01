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

#include "Application.h"
#include "exceptions/ModuleFailedLoading.h"

Application::Application(string name, bool debug, float version) {
    this->name = name;
    this->author = "Ian García";
    this->version = version;
    this->debug = debug;
    this->startTime = 0;
    this->finishTime = 0;
    this->started = false;
}

Application::~Application() {
    delete this->utils;
    delete this->time;
    delete this->search;
    delete this->sort;
    delete this->fakeData;
    delete this->lists;
    delete this->trees;
}

void Application::init() {
    try {
        if (isDebug()) getUtilsHandler()->log(getName() + " loading ...", Level::INFO);
        this->startTime = getTimeHandler()->getMillis();
        this->started = true;
        cli = new CLI(this);
        utils = new Utils(this);
        time = new Time(this);
        sort = new Sort(this);
        search = new Search(this);
        fakeData = new FakeData(this);
        lists = new Lists(this);
        trees = new Trees(this);
        for (Module *module: modules) {
            module->start();
        }
        this->finishTime = getTimeHandler()->getMillis();
        if (isDebug())
            getUtilsHandler()->log("Application started in [" + to_string((finishTime - startTime)) + "] ms.",
                                   Level::INFO);
    } catch (ModuleFailedLoading &e) {
        getUtilsHandler()->log(e.what(), Level::ERROR);
    }
    getCLIHandler()->startMenu();
}

void Application::stop() {
    this->started = false;
    for (Module *module: modules) {
        module->end();
    }
    getUtilsHandler()->log("Application ended successfully.", Level::INFO);
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

bool Application::isDebug() {
    return this->debug;
}

Utils *Application::getUtilsHandler() {
    return this->utils;
}

Time *Application::getTimeHandler() {
    return this->time;
}

Sort *Application::getSortHandler() {
    return this->sort;
}

Search *Application::getSearchHandler() {
    return this->search;
}

FakeData *Application::getFakeDataHandler() {
    return this->fakeData;
}

Trees *Application::getTreesHandler() {
    return this->trees;
}

CLI *Application::getCLIHandler() {
    return this->cli;
}

Application *Application::getApplication() {
    return this;
}

const Application *Application::getApplication() const {
    return this;
}

void Application::addModule(Module *module) {
    modules.push_back(module);
}

void Application::setName(string name) {
    this->name = name;
}

void Application::setAuthor(string author) {
    this->author = author;
}

void Application::setVersion(float version) {
    this->version = version;
}

void Application::setDebug(bool debug) {
    this->debug = debug;
}

bool Application::isStarted() {
    return this->started;
}

