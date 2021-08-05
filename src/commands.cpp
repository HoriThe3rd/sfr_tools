#include "commands.hpp"
#include <fstream>
#include <iostream>
#include "json11.hpp"

// Create commands object.
// Load a JSON file.
// Write a logfile.
commands::commands(const std::string& json_file) {
    // Open the file.
    std::ifstream file(json_file);
    if (!file) {
        std::cout << "Failed to open a JSON command file." << std::endl;
        exit(1);
    }
    // Convert the file to string object.
    std::string buf, tmp;
    while (std::getline(file, tmp)) buf += tmp;
    // Create a JSON parser object.
    std::string err;
    auto json = json11::Json::parse(buf, err);
    auto jsonarray = json["COMMAND_LIST"].array_items();
    // Create a command map.
    int num_of_cmd = jsonarray.size();
    for (auto it : jsonarray) {
        std::string cmd = it["CMD"].string_value();
        int addr = it["ADDR"].int_value();
        int data = it["DATA"].int_value();
        command_map[cmd] = sfr_cmd_if(static_cast<unsigned char>(addr),
                                      static_cast<unsigned char>(data));
    }
    // Logfile
    output_map_contents();
}

const sfr_cmd_if commands::operator()(const std::string& cmd_name) {
    return command_map[cmd_name];
}

// Dump the contents included in command_map to a logfile.
void commands::output_map_contents() const {
    std::ofstream logfile("commands_load_log.txt", std::ios::trunc);
    logfile << "--- commands object map ---" << std::endl;
    std::cout << "--- commands object map ---" << std::endl;
    for (auto it = command_map.begin(); it != command_map.end(); ++it) {
        logfile << it->first << ", "
                << static_cast<unsigned int>(it->second.addr()) << ", "
                << static_cast<unsigned int>(it->second.data()) << std::endl;
        std::cout << it->first << ", "
                  << static_cast<unsigned int>(it->second.addr()) << ", "
                  << static_cast<unsigned int>(it->second.data()) << std::endl;
    }
    logfile.close();
    std::cout << "--------" << std::endl;
}