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

#ifndef INTEGRALA_EXTRA_H
#define INTEGRALA_EXTRA_H

#include <string>

/**
 * @brief LapTime structure.
 */
struct LapTime {
    unsigned int raceId;
    unsigned int driverId;
    int lap;
    int position;
    std::string time;
    long int milli;
};

/**
 * @brief Race structure.
 */
struct Race {
    unsigned int raceId;
    int year;
    int round;
    unsigned int circuitId;
    std::string name;
    std::string date;
    std::string time;
    std::string url;
};

/**
 * @brief Driver structure.
 */
struct Driver {
    unsigned int driverId;
    std::string ref;
    int number;
    std::string code;
    std::string forename;
    std::string surname;
    std::string birthdate;
    std::string nationality;
    std::string url;
};

/**
 * @brief Circuit structure.
 */
struct Circuit {
    unsigned int circuitId;
    std::string ref;
    std::string name;
    std::string location;
    std::string country;
    long int latitude;
    long int longitude;
    long int altitude;
    std::string url;
    bool enabled;
};

/**
 * @brief Constructor structure.
 */
struct Constructor {
    unsigned int constructorId;
    std::string ref;
    std::string name;
    std::string nationality;
    std::string url;
};

#endif //INTEGRALA_EXTRA_H
