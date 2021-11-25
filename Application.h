//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 22/11/21.
//
// Copyright © 2021. All rights reserved.
//
//

#ifndef INTEGRALA_APPLICATION_H
#define INTEGRALA_APPLICATION_H

#include <string>
#include <fstream>

#include "CSVFile.h"
#include "models/Extra.h"

class Application {
private:
    std::string name;
    float version;
    bool debug;
    bool started;
    bool dataLoaded;

    LapTimeList *list = nullptr;

    static void log(const std::string &);

    static void menu();

    void launchCLI();

    void loadData();

public:
    Application(const std::string &, float, bool);

    ~Application();

    void init();

    void end();

    const std::string &getName() const;

    float getVersion() const;

    bool isDebug() const;

    bool isDataLoaded() const;

    void setDataLoaded(bool loaded);

    bool isStarted() const;

    void setStarted(bool appStarted);

    LapTimeList *getList() const;
};

Application::Application(const std::string &name, float version, bool debug) {
    this->name = name;
    this->version = version;
    this->debug = debug;
    this->dataLoaded = false;
    this->started = false;
}

Application::~Application() {
    delete list;
}

void Application::init() {
    setStarted(true);
    log("--------------");
    log(getName() + " starting now...");
    log("Loading version v" + std::to_string(getVersion()));
    loadData();
    log((isDebug() ? "Running in DEBUG mode." : "Running in PRODUCTION."));
    log("--------------");
    launchCLI();
}

const std::string &Application::getName() const {
    return this->name;
}

float Application::getVersion() const {
    return this->version;
}

bool Application::isDebug() const {
    return this->debug;
}

void Application::log(const std::string &message) {
    std::cout << "[*] " << message << std::endl;
}

void Application::menu() {
    log("---- MENU ----");
    log("Selecciona una opción:");
    log("1. Tiempos de vuelta");
    log("2. Carreras");
    log("3. Pilotos");
    log("4. Circuitos");
    log("5. Salir");
    log("--------------");
}

void Application::launchCLI() {
    if (!isDataLoaded()) log("Data hasn't been loaded completely yet.");
    int option;
    do {
        menu();
        std::cin >> option;
        while (!std::cin.good()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        switch (option) {
            case 1:
                log("Estos son los tiempos de vuelta.");
                std::cout << getList()->toStringForward() << std::endl;
                break;
            case 2:
                log("Estos son las carreras.");
                break;
            case 3:
                log("Estos son los pilotos.");
                break;
            case 4:
                log("Estos son los circuitos.");
                break;
            case 5:
                end();
                break;
            default:
                log("Opción inválida.");
                break;
        }
    } while (isStarted() && isDataLoaded());
}

bool Application::isDataLoaded() const {
    return this->dataLoaded;
}

void Application::setDataLoaded(bool loaded) {
    Application::dataLoaded = loaded;
}

void Application::loadData() {
    LapTimesFile seasonsFile("./data/lap_times.csv");
    list = seasonsFile.exportList();
    setDataLoaded(true);
}

bool Application::isStarted() const {
    return started;
}

void Application::setStarted(bool appStarted) {
    Application::started = appStarted;
}

void Application::end() {
    list->clear();
    log("Thanks for using this application.");
    log("Application closed successfully.");
    setStarted(false);
}

LapTimeList *Application::getList() const {
    return list;
}


#endif //INTEGRALA_APPLICATION_H
