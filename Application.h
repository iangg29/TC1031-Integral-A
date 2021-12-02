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
    ConstructorsHash<std::string, std::string> *constructors = nullptr;

    static void log(const std::string &);

    void menu();

    void launchCLI();

    void loadData();

    void runTests();

    void assertResult(std::string &, std::string &);

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

    IntegralType getIntegralType();

    LapTimeList *getList() const;

    CircuitsAVL *getCircuits() const;

    DriversBST *getDrivers() const;

    RacesList *getRaces() const;

    ConstructorsHash<std::string, std::string> *getConstructors() const;
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
    delete constructors;
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
    if (getIntegralType() == IntegralType::A) {
        log("1. Tiempos de vuelta");
        log("2. Carreras");
        log("3. Pilotos");
    } else {
        log("1. Circuitos");
        log("2. Escuderías");
        log("3. Grafos");
    }
    log("4. Run automated tests");
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
        if (getIntegralType() == IntegralType::A) {
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
                case 4:
                    runTests();
                    break;
                case 5:
                    end();
                    break;
                default:
                    log("Opción inválida.");
                    break;
            }
        } else {
            switch (option) {
                case 1: {
                    int count;
                    log("¿Cuántos circuitos deseas observar?");
                    std::cin >> count;
                    std::cout << getCircuits()->inorder(count) << std::endl;
                    break;
                }
                case 2: {
                    std::string in;
                    log("¿Qué escudería te gustaría observar?");
                    std::cin >> in;
                    if (!getConstructors()->contains(in)) {
                        log("No es posible encontrar esa escudería.");
                        break;
                    }
                    std::cout << "[RESULT] " << getConstructors()->get(in) << std::endl;
                    break;
                }
                case 3:
                    break;
                case 4: {
                    runTests();
                    break;
                }
                case 5:
                    end();
                    break;
                default:
                    log("Opción inválida.");
                    break;
            }
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
    ConstructorsFile constructorsFile("./data/constructors.csv");
    list = lapTimesFile.exportList();
    circuits = circuitsFile.exportAVL();
    drivers = driversFile.exportBST();
    races = racesFile.exportList();
    constructors = constructorsFile.exportHash();
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

IntegralType Application::getIntegralType() {
    return integralType;
}

RacesList *Application::getRaces() const {
    return races;
}

void Application::assertResult(std::string &result, std::string &expected) {
    if (expected == result) {
        log("[RESULT] SUCCESS");
    } else {
        log("[RESULT] FAILED (Result and Expected do not match).");
    }
    if (isDebug()) {
        std::cout << "[DEBUG] ESPERADA:" << std::endl << expected << std::endl;
        std::cout << "[DEBUG] PROGRAMA:" << std::endl << result << std::endl;
    }
}

ConstructorsHash<std::string, std::string> *Application::getConstructors() const {
    return constructors;
}

void Application::runTests() {
    unsigned int startTime, finishTime;
    startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << std::endl;
    log("Running automated tests...");
    log("[!] INTEGRAL A");
    log("-- Algoritmos de ordenamiento");
    std::string result, expected;
    std::vector<LapTime> laps = getList()->toVec(), cleaned;
    Sorts sorts;
    sorts.mergeSort(laps);
    for (auto &lap: laps) {
        if (lap.time.empty()) continue;
        cleaned.push_back(lap);
    }
    for (int i = 0; i < 5; ++i) {
        result.append("[" + getRaces()->search(cleaned[i].raceId)->name + "] x [" +
                      getDrivers()->find(cleaned[i].driverId)->code + "] " + cleaned[i].time + "\n");
    }
    expected = "[\"Sakhir Grand Prix\"] x [\"RUS\"] \"0:55.404\"\n[\"Sakhir Grand Prix\"] x [\"RUS\"] \"0:56.319\"\n[\"Sakhir Grand Prix\"] x [\"RUS\"] \"0:56.393\"\n[\"Sakhir Grand Prix\"] x [\"RUS\"] \"0:56.442\"\n[\"Sakhir Grand Prix\"] x [\"RUS\"] \"0:56.499\"\n";
    assertResult(result, expected);
    log("-- Estructuras lineales");
    result = getRaces()->toString(5);
    expected = "1. \"Australian Grand Prix\" (2009)\n2. \"Malaysian Grand Prix\" (2009)\n3. \"Chinese Grand Prix\" (2009)\n4. \"Bahrain Grand Prix\" (2009)\n5. \"Spanish Grand Prix\" (2009)\n";
    assertResult(result, expected);
    log("-- Árboles");
    result = getDrivers()->inorder(5);
    expected = "\n1. \"Lewis\" \"Hamilton\" [\"HAM\"] #44\n2. \"Nick\" \"Heidfeld\" [\"HEI\"]\n3. \"Nico\" \"Rosberg\" [\"ROS\"] #6\n4. \"Fernando\" \"Alonso\" [\"ALO\"] #14\n5. \"Heikki\" \"Kovalainen\" [\"KOV\"]";
    assertResult(result, expected);
    log("[!] INTEGRAL B");
    log("-- Grafos");
    // TODO: Graphs test cases.
    log("-- Hashes");
    result = getConstructors()->get("\"mercedes\"");
    expected = "\"http://en.wikipedia.org/wiki/Mercedes-Benz_in_Formula_One\"";
    assertResult(result, expected);
    result = getConstructors()->get("\"red_bull\"");
    expected = "\"http://en.wikipedia.org/wiki/Red_Bull_Racing\"";
    assertResult(result, expected);
    log("-- AVL");
    result = getCircuits()->inorder(5);
    expected = "\n1. \"Albert Park Grand Prix Circuit\" (\"Melbourne\", \"Australia\")\n2. \"Sepang International Circuit\" (\"Kuala Lumpur\", \"Malaysia\")\n3. \"Bahrain International Circuit\" (\"Sakhir\", \"Bahrain\")\n4. \"Circuit de Barcelona-Catalunya\" (\"Montmeló\", \"Spain\")\n5. \"Istanbul Park\" (\"Istanbul\", \"Turkey\")";
    assertResult(result, expected);
    finishTime = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << "[!] Successfully ran test cases. (Took " << (finishTime - startTime) << " ms)"
              << std::endl;
    std::cout << std::endl;
}

#endif  //INTEGRALA_APPLICATION_H
