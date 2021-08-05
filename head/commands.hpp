#pragma once
#include <map>
#include <string>
#include "sfr_cmd_if.hpp"

// For the interface between a command object and an SFR object.

class commands {
   public:
    commands(const std::string& json_file);
    const sfr_cmd_if operator()(const std::string& cmd_name);
    void output_map_contents() const;

   private:
    std::map<std::string, sfr_cmd_if> command_map;
};