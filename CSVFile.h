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
#include "structures/Graph.h"

/**
 * @brief Class that represents a CSV file.
 */
class CSVFile {
private:
    std::string name;
public:
    explicit CSVFile(const std::string &);

    const std::string &getName() const {
        return name;
    }
};

/**
 * @brief Construct a new CSVFile::CSVFile object
 * 
 * @param file_name Nombre del archivo CSV
 */
CSVFile::CSVFile(const std::string &file_name) {
    this->name = file_name;
}

// ------------------------------------------------

/**
 * @brief Class that represents a LapTime CSV.
 */
class LapTimesFile : public CSVFile {
private:
    std::ifstream file;

public:
    explicit LapTimesFile(const std::string &file_name);

    LapTimeList *exportList();

    bool isOpen();
};

/**
 * @brief Construct a new Lap Times File:: Lap Times File object
 * 
 * @param file_name Nombre del archivo CSV
 */
LapTimesFile::LapTimesFile(const std::string &file_name) : CSVFile(file_name) {
    this->file.open(file_name);
}

/**
 * @brief Export a list of LapTimes from the CSV file.
 * 
 * @return LapTimeList* 
 */
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

/**
 * @brief Check if the file is open.
 * 
 * @return true The file is open.
 * @return false The file is closed.
 */
bool LapTimesFile::isOpen() {
    return this->file.is_open();
}

// ------------------------------------------------

/**
 * @brief Class that represents a Drivers CSV.
 */
class CircuitsFile : public CSVFile {
private:
    std::ifstream file;

public:
    explicit CircuitsFile(const std::string &file_name);

    CircuitsAVL *exportAVL();

    bool isOpen();
};

/**
 * @brief Construct a new Circuits File:: Circuits File object
 * 
 * @param file_name Nombre del archivo CSV
 */
CircuitsFile::CircuitsFile(const std::string &file_name) : CSVFile(file_name) {
    this->file.open(file_name);
}

/**
 * @brief Export a AVL of Circuits from the CSV file.
 * 
 * @return CircuitsAVL* 
 */
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
        circuit.enabled = (newRecord[9] == "1");


        circuitsAVL->add(circuit);
        newRecord.clear();
    }
    return circuitsAVL;
}

/**
 * @brief Check if the file is open.
 * 
 * @return true The file is open.
 * @return false The file is closed.
 */
bool CircuitsFile::isOpen() {
    return this->file.is_open();
}

// ------------------------------------------------

/**
 * @brief Class that represents a Drivers CSV.
 */
class DriversFile : public CSVFile {
private:
    std::ifstream file;

public:
    explicit DriversFile(const std::string &file_name);

    DriversBST *exportBST();

    bool isOpen();
};

/**
 * @brief Construct a new Drivers File:: Drivers File object
 * 
 * @param file_name Nombre del archivo CSV
 */
DriversFile::DriversFile(const std::string &file_name) : CSVFile(file_name) {
    this->file.open(file_name);
}

/**
 * @brief Export a BST of Drivers from the CSV file.
 * 
 * @return DriversBST* 
 */
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

/**
 * @brief Check if the file is open.
 * 
 * @return true The file is open.
 * @return false The file is closed.
 */
bool DriversFile::isOpen() {
    return this->file.is_open();
}

// ------------------------------------------------

/**
 * @brief Class that represents a RaceFile CSV.
 */
class RacesFile : public CSVFile {
private:
    std::ifstream file;

public:
    explicit RacesFile(const std::string &file_name);

    RacesList *exportList();

    bool isOpen();
};

/**
 * @brief Construct a new Races File:: Races File object
 * 
 * @param file_name Nombre del archivo
 */
RacesFile::RacesFile(const std::string &file_name) : CSVFile(file_name) {
    this->file.open(file_name);
}

/**
 * @brief Exports a RaceList from CSV file.
 * 
 * @return RacesList* 
 */
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

/**
 * @brief Check if the file is open.
 * 
 * @return true The file is open.
 * @return false The file is closed.
 */
bool RacesFile::isOpen() {
    return this->file.is_open();
}

// ------------------------------------------------

/**
 * @brief Function that allows hashing a string.
 * 
 * @param s String to hash.
 * @return unsigned int 
 */
unsigned int constructorsHashFunc(const std::string s) {
    unsigned int acum = 0;
    for (unsigned int i = 0; i < s.size(); i++) {
        acum += (int) s[i];
    }
    return acum;
}

/**
 * @brief Class that represents a Constructors CSV.
 * 
 */
class ConstructorsFile : public CSVFile {
private:
    std::ifstream file;

public:
    explicit ConstructorsFile(const std::string &file_name);

    ConstructorsHash<std::string, std::string> *exportHash();

    bool isOpen();
};

/**
 * @brief Construct a new Constructors File:: Constructors File object
 * 
 * @param file_name Nombe del archivo
 */
ConstructorsFile::ConstructorsFile(const std::string &file_name) : CSVFile(file_name) {
    this->file.open(file_name);
}

/**
 * @brief Exports a ConstructorsHash from CSV file.
 * 
 * @return ConstructorsHash<std::string, std::string>* 
 */
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

/**
 * @brief Check if the file is open.
 * 
 * @return true The file is open.
 * @return false The file is closed.
 */
bool ConstructorsFile::isOpen() {
    return this->file.is_open();
}

// ------------------------------------------------

/**
 * @brief Class that represents a Graph from CSV.
 *
 */
class GraphFile : public CSVFile {
private:
    std::ifstream file;

public:
    explicit GraphFile(const std::string &file_name);

    Graph *exportGraph();

    bool isOpen();
};

/**
 * @brief Construct a new Constructors File:: Constructors File object
 *
 * @param file_name Nombe del archivo
 */
GraphFile::GraphFile(const std::string &file_name) : CSVFile(file_name) {
    this->file.open(file_name);
}

/**
 * @brief Exports a ConstructorsHash from CSV file.
 *
 * @return ConstructorsHash<std::string, std::string>*
 */
Graph *GraphFile::exportGraph() {
    auto *graph = new Graph();
    graph->loadGraphList(getName(), 41);
    return graph;
}

/**
 * @brief Check if the file is open.
 *
 * @return true The file is open.
 * @return false The file is closed.
 */
bool GraphFile::isOpen() {
    return this->file.is_open();
}


#endif //INTEGRALA_CSVFILE_H
