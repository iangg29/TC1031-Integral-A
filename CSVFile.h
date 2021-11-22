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
#include "structures/dlist.h"

class CSVFile {
private:
    std::string name;
    std::ifstream file;
public:
    explicit CSVFile(const std::string &);

    DList<std::string> exportList();

    bool isOpen();
};

CSVFile::CSVFile(const std::string &file_name) {
    this->name = file_name;
    this->file.open(file_name);
}

bool CSVFile::isOpen() {
    return this->file.is_open();
}

DList<std::string> CSVFile::exportList() {
    DList<std::string> lista;
    if (!isOpen()) {
        std::cout << "NO ABRE EL ARCHIVO" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string line, word;
    while (std::getline(file, line)) {
        std::stringstream s(line);
        while (std::getline(s, word, ',')) {
            std::cout << word << std::endl;
        }
        std::cout << std::endl;
    }
    return lista;
}


#endif //INTEGRALA_CSVFILE_H
