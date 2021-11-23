//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 23/11/21.
//
// Copyright © 2021. All rights reserved.
//
//

#ifndef INTEGRALA_FILES_H
#define INTEGRALA_FILES_H

#include <iostream>
#include <string>

#include "../CSVFile.h"
#include "../models/Extra.h"

class Seasons : public CSVFile {
private:
    std::string name;
public:
    Seasons(const std::string &);

    DList<Season> exportList();
};

Seasons::Seasons(const std::string &file_name) : CSVFile(file_name) {
    this->name = file_name;
}

DList<Season> Seasons::exportList() {
    DList<Season> lista;
    if (!isOpen()) {
        std::cout << "NO ABRE EL ARCHIVO" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string line, word;
    /*
    while (std::getline(this->getFile(), line)) {
        Season season;
        std::stringstream s(line);
        while (std::getline(s, word, ',')) {
            std::cout << word << std::endl;
        }
        std::cout << std::endl;
        lista.insert(season);
    }*/
    return lista;
}

#endif //INTEGRALA_FILES_H
