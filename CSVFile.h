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

class CSVFile {
private:
    std::string name;
public:
    explicit CSVFile(const std::string &);
};

CSVFile::CSVFile(const std::string &file_name) {
    this->name = file_name;
}


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
    std::vector<std::vector<std::string>> lista;
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
    std::vector<std::vector<std::string>> lista;
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


#endif //INTEGRALA_CSVFILE_H
