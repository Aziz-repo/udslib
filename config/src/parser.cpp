#include "parser.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace uds;

void UDSConfiguration::loadConfiguration(const std::filesystem::path& config_path) {
  std::ifstream config_file(config_path);
  std::string content;
  if (config_file.is_open()) {
    while(!config_file.eof()) {
      std::string line;
      std::getline(config_file, line);
      content += line + "\n";
    }
    trimConfiguration(content);
    std::cout << content << std::endl;
  } else {
    std::cerr << "Cannot open file\n";
    return;
  }
}

// Dummy implementation
std::string UDSConfiguration::getConfiguration(std::string& s) {
  return s;
}

void UDSConfiguration::trimConfiguration(std::string& s) {
  UDSConfiguration::ltrim(UDSConfiguration::rtrim(s));
}
