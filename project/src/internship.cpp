#include <chrono>
#include <fstream>
#include <iostream>

#include <date/date.h>
#include <nlohmann/json.hpp>

#include "internship.h"

using json = nlohmann::json;
using namespace date;
using namespace std;

namespace internship {

    // do not remove this function
void solution(const string& fileName, int elementsCount) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << "\n";
        return;
    }

    nlohmann::json data;
    file >> data;

    int count = 0;
    for (const auto& [id, product] : data.items()) {
        if (count == elementsCount) {
            break;
        }

        // Calculate number of days between release date and EOL date
        std::string releaseDateString = product["versions"][0]["releaseDate"];
        std::string eolDateString = product["versions"][0]["eol"];
        std::tm releaseDate = {}, eolDate = {};
        std::stringstream releaseDateStream(releaseDateString), eolDateStream(eolDateString);
        releaseDateStream >> std::get_time(&releaseDate, "%Y-%m-%d");
        eolDateStream >> std::get_time(&eolDate, "%Y-%m-%d");
        std::time_t releaseTime = std::mktime(&releaseDate), eolTime = std::mktime(&eolDate);
        double seconds = std::difftime(eolTime, releaseTime);
        double days = seconds / (24.0 * 3600.0);

        std::cout <<product["name"] <<" "<<product["versions"][0]["cycle"]<< " " <<days << "\n";


        ++count;
    }

    file.close();
}    //std::cout << "JSON content: " << data.dump() << std::endl;
}


