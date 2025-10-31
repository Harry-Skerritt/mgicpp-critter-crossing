//
// Created by Harry Skerritt on 23/10/2025.
//

#ifndef PASSPORTDATAMANAGER_H
#define PASSPORTDATAMANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <deque>

class PassportDataManager {
// Funcs
public:
    PassportDataManager();
    ~PassportDataManager();

    // Setup
    bool loadNameFile(std::string file_name, std::string resource_location = "../Data/Resources/");
    bool loadDistrictFile(std::string file_name, std::string resource_location = "../Data/Resources/");

    // Names
    bool getNamesLoaded();
    const std::vector<std::string>* getFirstNames();
    const std::vector<std::string>* getSurnames();
    std::string generateName();

    // Age
    int generateAge(int max_age = 96, int min_age = 10);

    // District
    bool getDistrictLoaded();
    const std::vector<std::string>* getDistricts();
    std::string generateDistrict();

private:
    std::vector<std::string> loadFile(std::string file_name, std::string resource_location = "../Data/Resources/");

// Vars
public:

private:
    // Names
    std::vector<std::string> first_names;
    std::vector<std::string> surnames;
    bool names_loaded = false;

    std::deque<std::string> recent_first_names;
    std::deque<std::string> recent_surnames;

    // Locations
    std::vector<std::string> district_names;
    bool district_loaded = false;

    std::string last_district;
};



#endif //PASSPORTDATAMANAGER_H
