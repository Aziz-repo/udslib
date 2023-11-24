#pragma once

#include "metadata.h"
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iterator>
#include <map>
#include <string>
#include <vector>

namespace uds {
class UDSConfiguration {
public:
  UDSConfiguration() = default;
  ~UDSConfiguration() = default;

  void loadConfiguration(const std::string &);
  std::string getConfiguration(std::string &);

  // getters
  std::vector<DID> getDidConfiguration() const { return dids_configuration; }

private:
  std::vector<DID> dids_configuration;
};
} // namespace uds
