#pragma once

#include "metadata.h"
#include <cstdint>
#include <optional>
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
  [[nodiscard]] std::vector<DID> getDidConfigurations() const {
    return dids_configuration;
  }
  [[nodiscard]] std::optional<DID> getDidConfiguration(uint16_t) const;

private:
  std::vector<DID> dids_configuration;
};
} // namespace uds
