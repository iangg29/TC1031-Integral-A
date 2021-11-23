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

    bool isOpen();

    const std::ifstream &getFile() const;
};

CSVFile::CSVFile(const std::string &file_name) {
    this->name = file_name;
    this->file.open(file_name);
}

bool CSVFile::isOpen() {
    return this->file.is_open();
}

const std::ifstream &CSVFile::getFile() const {
    return file;
}


#endif //INTEGRALA_CSVFILE_H
