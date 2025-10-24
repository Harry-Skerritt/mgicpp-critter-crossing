//
// Created by Harry Skerritt on 23/10/2025.
//

#include "PassportDataManager.h"

PassportDataManager::PassportDataManager() {

}

PassportDataManager::~PassportDataManager() = default;

// --- Setup ---
void PassportDataManager::loadNameFile(std::string file_name, std::string resource_location) {
    names_loaded = false;

    std::vector<std::string> file_lines = loadFile(file_name, resource_location);
    if (file_lines.empty()) {
        return;
    }

    for (const std::string& line : file_lines) {
        std::stringstream ss(line);
        std::string first_name, last_name;

        if (std::getline(ss, first_name, ',') && std::getline(ss, last_name)) {
            if (!first_name.empty() && first_name.front() == ' ') first_name.erase(0, 1);
            if (!last_name.empty() && last_name.front() == ' ') last_name.erase(0, 1);

            first_names.push_back(first_name);
            surnames.push_back(last_name);
        }
    }

    names_loaded = true;
}

void PassportDataManager::loadDistrictFile(std::string file_name, std::string resource_location) {
    district_loaded = true;

    district_names = loadFile(file_name, resource_location);

    if (district_names.empty()) {
        district_loaded = false;
    }

}


// --- Generators ---
std::string PassportDataManager::generateName() {
    if (!names_loaded || first_names.empty() || surnames.empty()) {
        std::cerr << "PassportDataManager: No names loaded!" << std::endl;
        return "";
    }

    std::string first;
    std::string last;

    // First name
    do {
        first = first_names[rand() % first_names.size()];
    } while (std::find(recent_first_names.begin(), recent_first_names.end(), first) != recent_first_names.end());

    // Unique first name?
    recent_first_names.push_back(first);
    if (recent_first_names.size() > 5) {
        recent_first_names.pop_front();
    }


    // Last name
    do {
        last = surnames[rand() % surnames.size()];
    } while (std::find(recent_surnames.begin(), recent_surnames.end(), last) != recent_surnames.end());

    // Unique first name?
    recent_surnames.push_back(last);
    if (recent_surnames.size() > 5) {
        recent_surnames.pop_front();
    }

    // Combine and return
    std::string name;
    name = first + " " + last;

    return name;
}

int PassportDataManager::generateAge(int max_age, int min_age) {
    return min_age + rand() % (max_age - min_age + 1);
}

std::string PassportDataManager::generateDistrict() {
    if (!district_loaded || district_names.empty() ) {
        std::cerr << "PassportDataManager: No districts loaded!" << std::endl;
        return "";
    }

    std::string district;

    do {
        district = district_names[rand() % district_names.size()];
    } while (district == last_district);

    // Unqiue district
    last_district = district;

    return district;
}


// --- Getters ---
// Names
bool PassportDataManager::getNamesLoaded() {
    return names_loaded;
}

const std::vector<std::string> *PassportDataManager::getFirstNames() {
    return &first_names;
}

const std::vector<std::string> *PassportDataManager::getSurnames() {
    return &surnames;
}

// District
bool PassportDataManager::getDistrictLoaded() {
    return district_loaded;
}

const std::vector<std::string> *PassportDataManager::getDistricts() {
    return &district_names;
}


// --- PRIVATE ---
std::vector<std::string> PassportDataManager::loadFile(std::string file_name, std::string resource_location) {
    std::string file_path = resource_location + file_name;
    std::ifstream file(file_path);

    std::vector<std::string> file_lines;

    if (!file.is_open()) {
        std::cerr << "PassportDataManager: Failed to open file " << file_path << std::endl;
        return file_lines;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            file_lines.push_back(line);
        }
    }

    return file_lines;
}



