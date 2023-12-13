#pragma once

#include "metadata.h"
#include <cstdint>
#include <mutex>
#include <string>
#include <vector>

namespace uds {
class UDSConfiguration {
protected:
  UDSConfiguration() = default;
  ~UDSConfiguration() = default;
  std::vector<DID> dids_configuration;

public:
  UDSConfiguration(UDSConfiguration &) = delete;
  void operator=(const UDSConfiguration &) = delete;

  void loadConfiguration(const std::string &);
  std::string getConfiguration(std::string &);

  // getters
  [[nodiscard]] std::vector<DID> getDidConfigurations() const {
    return dids_configuration;
  }
  [[nodiscard]] DID getDidConfiguration(uint16_t) const;

  static UDSConfiguration *getInstance();

private:
  static UDSConfiguration *instance_;
  static std::mutex mutex_;
};
} // namespace uds
