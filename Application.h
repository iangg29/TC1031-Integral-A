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

#include <fstream>
#include <limits>
#include <string>
#include <chrono>

#include "CSVFile.h"
#include "models/Extra.h"
#include "helpers/Sorts.h"

enum class IntegralType {
    A,
    B
};

class Application {
private:
    std::string name;
    float version;
    bool debug;
    bool started;
    bool dataLoaded;
    IntegralType integralType;

    LapTimeList *list = nullptr;
    CircuitsAVL *circuits = nullptr;
    DriversBST *drivers = nullptr;
    RacesList *races = nullptr;

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

    IntegralType getIntegralType() const;

    LapTimeList *getList() const;

    CircuitsAVL *getCircuits() const;

    DriversBST *getDrivers() const;

    RacesList *getRaces() const;
};

Application::Application(const std::string &name, float version, bool debug) {
    this->name = name;
    this->version = version;
    this->debug = debug;
    this->dataLoaded = false;
    this->started = false;
    log("¿Qué integral es esta? (A/B)");
    char type;
    std::cin >> type;
    switch (type) {
        case 'A':
            this->integralType = IntegralType::A;
            log("Iniciando version Integral-A");
            break;
        case 'B':
            this->integralType = IntegralType::B;
            log("Iniciando version Integral-B");
            break;
        default:
            this->integralType = IntegralType::A;
            log("Opción incorrecta, iniciando versión Integral-A");
            break;
    }
}

Application::~Application() {
    delete list;
    delete circuits;
    delete drivers;
    delete races;
}

void Application::init() {
    setStarted(true);
    log("--------------");
    log(getName() + " starting now...");
    log("Loading version v" + std::to_string(getVersion()));
    loadData();
    log((getIntegralType() == IntegralType::A ? "Data structures included: Doubly Linked List, BST, Sort."
                                              : "Data structures included: Graphs, Hash Tables, AVL Tree."));
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
    log("5. Run automated tests");
    log("6. Salir");
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
            case 1: {
                int count;
                Sorts sort;
                log("¿Cuántos tiempos de vuelta ordenados deseas observar?");
                std::cin >> count;
                std::vector<LapTime> laps = getList()->toVec(), cleaned;
                sort.mergeSort(laps);
                for (auto &lap: laps) {
                    if (lap.time.empty()) continue;
                    cleaned.push_back(lap);
                }
                for (int i = 0; i < count; ++i) {
                    std::cout << "[" << getRaces()->search(cleaned[i].raceId)->name << "] x ["
                              << getDrivers()->find(cleaned[i].driverId)->code << "] " << cleaned[i].time
                              << std::endl;
                }
                break;
            }
            case 2: {
                int count;
                log("¿Cuántas carreras deseas observar?");
                std::cin >> count;
                std::cout << getRaces()->toString(count) << std::endl;
                break;
            }
            case 3: {
                int count;
                log("¿Cuántos pilotos deseas observar?");
                std::cin >> count;
                std::cout << drivers->inorder(count) << std::endl;
                break;
            }
            case 4: {
                int count;
                log("¿Cuántos circuitos deseas observar?");
                std::cin >> count;
                std::cout << getCircuits()->inorder(count) << std::endl;
                break;
            }
            case 5: {
                unsigned int startTime, finishTime;
                startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch()).count();
                std::cout << std::endl;
                log("Running automated tests...");
                log("[!!] INTEGRAL A");
                log("-- Algoritmos de ordenamiento");
                log("-- Estructuras lineales");
                log("-- Árboles");
                log("[!!] INTEGRAL B");
                log("-- Grafos");
                log("-- Hashes");
                log("-- AVL");
                finishTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch()).count();
                std::cout << "[!] Successfully ran test cases. (Took " << (finishTime - startTime) << " ms)" << std::endl;
                std::cout << std::endl;
                break;
            }
            case 6:
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
    LapTimesFile lapTimesFile("./data/lap_times.csv");
    CircuitsFile circuitsFile("./data/circuits.csv");
    DriversFile driversFile("./data/drivers.csv");
    RacesFile racesFile("./data/races.csv");
    list = lapTimesFile.exportList();
    circuits = circuitsFile.exportAVL();
    drivers = driversFile.exportBST();
    races = racesFile.exportList();
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
    circuits->removeAll();
    races->clear();
    log("Thanks for using this application.");
    log("Application closed successfully.");
    setStarted(false);
}

LapTimeList *Application::getList() const {
    return list;
}

CircuitsAVL *Application::getCircuits() const {
    return circuits;
}

DriversBST *Application::getDrivers() const {
    return drivers;
}

IntegralType Application::getIntegralType() const {
    return integralType;
}

RacesList *Application::getRaces() const {
    return races;
}

#endif  //INTEGRALA_APPLICATION_H
