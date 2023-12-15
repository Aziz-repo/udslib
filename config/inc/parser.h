/*!
 * @file parser.h
 * @author M.Aziz Hassene
 * @brief Holds the configuration file parser
 * @version v1.0.0
 * @date 2023-12-15
 */

#pragma once

#include "metadata.h"
#include <cstdint>
#include <mutex>
#include <string>
#include <vector>

namespace uds {

/*!
 * @brief Reperesents the configuration parser.
 * @note This class was designed as a Singleton for performance increasing.
 *
 */
class UDSConfiguration {
protected:
  UDSConfiguration() = default;
  ~UDSConfiguration() = default;
  /*!
   * @brief vector holds the DID configuration.
   */
  std::vector<DID> dids_configuration;

public:
  UDSConfiguration(UDSConfiguration &) = delete;
  void operator=(const UDSConfiguration &) = delete;
  /*!
   * @brief Loads the DID configuration into a member object (vector)
   */
  void loadConfiguration(const std::string &);

  /*!
   * @brief Get a specific configuration.
   * @param config Reperesents the config to retrieve.
   * @note Still under development
   */
  std::string getConfiguration(std::string &config);
  // getters

  /*!
   * @brief Getter method to get all configuration.
   */
  [[nodiscard]] std::vector<DID> getDidConfigurations() const {
    return dids_configuration;
  }

  /*!
   * @brief Getter method to get one single DID configurations.
   * @note This function may throw ConfigNotFoundException.
   */
  [[nodiscard]] DID getDidConfiguration(uint16_t) const;
  /*!
   * @brief The intermidiate constructor for the UDSConfiguration object.
   * @note This is method is used in place of the consutructor as this class
   * is written as a Singleton.
   */
  static UDSConfiguration *getInstance();

private:
  static UDSConfiguration *instance_;
  static std::mutex mutex_;
};
} // namespace uds
