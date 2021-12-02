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

#ifndef INTEGRALA_CSVFILE_H
#define INTEGRALA_CSVFILE_H

#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include "structures/LapTimeList.h"
#include "structures/CircuitsAVL.h"
#include "structures/DriversBST.h"
#include "structures/RacesList.h"
#include "structures/ConstructorsHash.h"

class CSVFile {
private:
    std::string name;
public:
    explicit CSVFile(const std::string &);
};

CSVFile::CSVFile(const std::string &file_name) {
    this->name = file_name;
}

// ------------------------------------------------

class LapTimesFile : public CSVFile {
private:
    std::ifstream file;

public:
    explicit LapTimesFile(const std::string &file_name);

    LapTimeList *exportList();

    bool isOpen();
};

LapTimesFile::LapTimesFile(const std::string &file_name) : CSVFile(file_name) {
    this->file.open(file_name);
}

LapTimeList *LapTimesFile::exportList() {
    auto *lapTimeList = new LapTimeList;
    int count = 0;
    if (!isOpen()) {
        std::cout << "NO ABRE EL ARCHIVO" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<std::string> pj;
    std::string line, word;
    while (std::getline(this->file, line)) {
        count++;
        if (count == 1) continue;
        std::stringstream s(line);
        LapTime lapTime;
        std::vector<std::string> newRecord;
        while (std::getline(s, word, ',')) {
            newRecord.push_back(word);
        }
        lapTime.raceId = std::stoi(newRecord[0]);
        lapTime.driverId = std::stoi(newRecord[1]);
        lapTime.lap = std::stoi(newRecord[2]);
        lapTime.position = std::stoi(newRecord[3]);
        lapTime.time = newRecord[4];
        lapTime.milli = std::stol(newRecord[5]);
        lapTimeList->insert(lapTime);
        newRecord.clear();
    }
    return lapTimeList;
}

bool LapTimesFile::isOpen() {
    return this->file.is_open();
}

// ------------------------------------------------

class CircuitsFile : public CSVFile {
private:
    std::ifstream file;

public:
    explicit CircuitsFile(const std::string &file_name);

    CircuitsAVL *exportAVL();

    bool isOpen();
};

CircuitsFile::CircuitsFile(const std::string &file_name) : CSVFile(file_name) {
    this->file.open(file_name);
}

CircuitsAVL *CircuitsFile::exportAVL() {
    auto *circuitsAVL = new CircuitsAVL;
    int count = 0;
    if (!isOpen()) {
        std::cout << "NO ABRE EL ARCHIVO" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<std::string> pj;
    std::string line, word;
    while (std::getline(this->file, line)) {
        count++;
        if (count == 1) continue;
        std::stringstream s(line);
        Circuit circuit;
        std::vector<std::string> newRecord;

        while (std::getline(s, word, ',')) {
            newRecord.push_back(word);
        }

        circuit.circuitId = std::stoi(newRecord[0]);
        circuit.ref = newRecord[1];
        circuit.name = newRecord[2];
        circuit.location = newRecord[3];
        circuit.country = newRecord[4];
        circuit.latitude = std::stol(newRecord[5]);
        circuit.longitude = std::stol(newRecord[6]);
        circuit.altitude = std::stol(newRecord[7]);
        circuit.url = newRecord[8];


        circuitsAVL->add(circuit);
        newRecord.clear();
    }
    return circuitsAVL;
}

bool CircuitsFile::isOpen() {
    return this->file.is_open();
}

// ------------------------------------------------

class DriversFile : public CSVFile {
private:
    std::ifstream file;

public:
    explicit DriversFile(const std::string &file_name);

    DriversBST *exportBST();

    bool isOpen();
};

DriversFile::DriversFile(const std::string &file_name) : CSVFile(file_name) {
    this->file.open(file_name);
}

DriversBST *DriversFile::exportBST() {
    auto *driversBST = new DriversBST;
    int count = 0;
    if (!isOpen()) {
        std::cout << "NO ABRE EL ARCHIVO" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<std::string> pj;
    std::string line, word;
    while (std::getline(this->file, line)) {
        count++;
        if (count == 1) continue;
        std::stringstream s(line);
        Driver driver;
        std::vector<std::string> newRecord;

        while (std::getline(s, word, ',')) {
            newRecord.push_back(word);
        }

        driver.driverId = std::stoi(newRecord[0]);
        driver.ref = newRecord[1];
        driver.number = (newRecord[2] == "\\N" ? -1 : std::stoi(newRecord[2]));
        driver.code = newRecord[3];
        driver.forename = newRecord[4];
        driver.surname = newRecord[5];
        driver.birthdate = newRecord[6];
        driver.nationality = newRecord[7];
        driver.url = newRecord[8];

        driversBST->add(driver);
        newRecord.clear();
    }
    return driversBST;
}

bool DriversFile::isOpen() {
    return this->file.is_open();
}

// ------------------------------------------------

class RacesFile : public CSVFile {
private:
    std::ifstream file;

public:
    explicit RacesFile(const std::string &file_name);

    RacesList *exportList();

    bool isOpen();
};

RacesFile::RacesFile(const std::string &file_name) : CSVFile(file_name) {
    this->file.open(file_name);
}

RacesList *RacesFile::exportList() {
    auto *racesList = new RacesList;
    int count = 0;
    if (!isOpen()) {
        std::cout << "NO ABRE EL ARCHIVO" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<std::string> pj;
    std::string line, word;
    while (std::getline(this->file, line)) {
        count++;
        if (count == 1) continue;
        std::stringstream s(line);
        Race race;
        std::vector<std::string> newRecord;

        while (std::getline(s, word, ',')) {
            newRecord.push_back(word);
        }

        race.raceId = std::stoi(newRecord[0]);
        race.year = std::stoi(newRecord[1]);
        race.round = std::stoi(newRecord[2]);
        race.circuitId = std::stoi(newRecord[3]);
        race.name = newRecord[4];
        race.date = newRecord[5];
        race.time = newRecord[6];
        race.url = newRecord[7];

        racesList->insert(race);
        newRecord.clear();
    }
    return racesList;
}

bool RacesFile::isOpen() {
    return this->file.is_open();
}

// ------------------------------------------------

unsigned int constructorsHashFunc(const std::string s) {
    unsigned int acum = 0;
    for (unsigned int i = 0; i < s.size(); i++) {
        acum += (int) s[i];
    }
    return acum;
}


class ConstructorsFile : public CSVFile {
private:
    std::ifstream file;

public:
    explicit ConstructorsFile(const std::string &file_name);

    ConstructorsHash<std::string, std::string> *exportHash();

    bool isOpen();
};

ConstructorsFile::ConstructorsFile(const std::string &file_name) : CSVFile(file_name) {
    this->file.open(file_name);
}

ConstructorsHash<std::string, std::string> *ConstructorsFile::exportHash() {
    auto *constructorsHash = new ConstructorsHash<std::string, std::string>(211, std::string("empty"),
                                                                            constructorsHashFunc);
    int count = 0;
    if (!isOpen()) {
        std::cout << "NO ABRE EL ARCHIVO" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::vector<std::string> pj;
    std::string line, word;
    while (std::getline(this->file, line)) {
        count++;
        if (count == 1) continue;
        std::stringstream s(line);
        Constructor constructor;
        std::vector<std::string> newRecord;

        while (std::getline(s, word, ',')) {
            newRecord.push_back(word);
        }
        constructor.constructorId = std::stoi(newRecord[0]);
        constructor.ref = newRecord[1];
        constructor.name = newRecord[2];
        constructor.nationality = newRecord[3];
        constructor.url = newRecord[4];

        constructorsHash->put(constructor.ref, constructor.url);
        newRecord.clear();
    }
    return constructorsHash;
}

bool ConstructorsFile::isOpen() {
    return this->file.is_open();
}


#endif //INTEGRALA_CSVFILE_H
