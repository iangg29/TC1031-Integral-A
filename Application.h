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
#include "CSVFile.h"

class Application {
private:
    std::string name;
    float version;
    bool debug;

    static void log(const std::string &);

    void menu();

public:
    Application(const std::string &, float, bool);

    void init() const;

    const std::string &getName() const;

    float getVersion() const;

    bool isDebug() const;
};

Application::Application(const std::string &name, float version, bool debug) {
    this->name = name;
    this->version = version;
    this->debug = debug;
}

void Application::init() const {
    log("----------");
    log(getName() + " starting now...");
    log("Loading version v" + std::to_string(getVersion()));
    log((isDebug() ? "Running in DEBUG mode." : "Running in PRODUCTION."));
    log("----------");
    CSVFile seasonsFile("./data/seasons.csv");
    DList<std::string> list = seasonsFile.exportList();
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
    log("1. Pilotos");
    log("2. Circuitos");
    log("3. Escuderías");
    log("4. Carreras");
    log("5. Temporadas");
    log("6. Tiempos de vuelta");
    log("--------------");
}


#endif //INTEGRALA_APPLICATION_H
