#include "database.h"
#include <fstream>
#include <iostream>
#include <sstream>

Database::Database() {
    nlohmann::json j;
    std::string configuration;
    std::stringstream configStream;
    std::ifstream readStream("config.json");

    if (!readStream.is_open()) {
        std::cerr << "ERROR: Could not open config.json\n";
        return;
    }

    configStream << readStream.rdbuf();
    configuration = configStream.str();
    
    j = nlohmann::json::parse(configuration);

    readStream.close(); 
}

Database::~Database() {}