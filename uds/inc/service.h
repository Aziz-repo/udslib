/*!
 * @file service.h
 * @author M.Aziz Hassene
 * @brief Abstracts the service structures
 * @version v1.0.0
 * @date 2023-12-15
 */
#pragma once

#include <cstddef>
#include <cstdint>
#include <diagService.h>
#include <iostream>
#include <metadata.h>
#include <ostream>
#include <string>
#include <vector>

namespace uds {
class Service;
}
bool operator==(const uds::Service &, const uds::Service &);
bool operator!=(const uds::Service &, const uds::Service &);
std::ostream &operator<<(std::ostream &, const uds::Service &);

namespace uds {

class Service {
public:
  Service() = default;
  Service(const NonSubFuncService &service);
  Service(const SubFuncService &service);
  Service(const SubFuncService &service, uint8_t subfunction);
  Service(const SubFuncService &service, uint8_t subfunction,
          std::vector<uint16_t> &serviceData);
  Service(const NonSubFuncService &service, std::vector<uint16_t> &serviceData);
  Service(Service &&service);      // move constructor
  Service(const Service &service); // copy constructor
  ~Service() = default;

  // operators
  friend bool ::operator==(const Service &, const Service &);
  friend bool ::operator!=(const Service &, const Service &);
  friend std::ostream & ::operator<<(std::ostream &, const Service &);
  Service &operator=(const Service &);
  Service operator()(const NonSubFuncService &);
  Service operator()(const SubFuncService &);

  // getter
  [[nodiscard]] uint8_t getServiceId() const { return serviceId; }
  [[nodiscard]] std::string getServiceName() const { return serviceName; }
  [[nodiscard]] std::vector<std::uint16_t> getServiceData() const {
    return serviceData;
  }
  [[nodiscard]] std::uint8_t getSubfunction() const { return subfunction_; }
  [[nodiscard]] bool getSupportSubFunction() const {
    return supportSubfunction;
  }
  [[nodiscard]] size_t getServiceDataSize() const { return serviceData.size(); }

  [[nodiscard]] bool hasData() const { return !serviceData.empty(); }

  // setter
  void setSubfunction(uint8_t subfunction) { this->subfunction_ = subfunction; }
  void setServiceData(std::vector<std::uint16_t> serviceData) {
    this->serviceData = serviceData;
  }

  /*!
   * @brief Serializes the service object.
   * @note This function is used by Request's getPayload method.
   */
  std::vector<uint8_t> serialize();

  // void deserialize();

  /*!
   * @brief Used to log the service data to the console
   * @note This method was written for pure testing reasons.
   */
  static std::string logServiceData(const Service &service) {
    std::string serviceData;
    for (auto &e : service.serviceData) {
      serviceData.append((char)*&e, sizeof(e));
    }
    return serviceData;
  }

  /*!
   * @brief Return a shollow Service object based on the service ID.
   * @note Shallow service means a service object without the service data
   * member.
   * @param serviceId The service ID.
   *
   */
  // TODO: change to static_cast
  static Service fromRequestId(uint8_t serviceId) {
    Service service;
    switch (serviceId) {
    case 0x22:
      service = Service(ReadDataByIdentifer());
      break;
    case 0x11:
      service = Service(ECUReset());
      break;
    case 0x2E:
      service = Service(WriteDataByIdentifer());
      break;
    }
    return service;
  }

  /*!
   * @brief Returns a Service object from the Response code.
   * @note This method uses the fromRequestId.
   * @param responseID The code returned by the ECU
   *
   */
  // TODO: change to treat the negative response.
  static Service fromResponseId(uint16_t responseID) {
    Service service = Service::fromRequestId((responseID - PRESPONSE_IND));
    return service;
  }

private:
  /*!
   * @brief Service ID (SID)
   */
  std::uint8_t serviceId;
  /*!
   * @brief Subfunctoin to use in the Service.
   */
  uint8_t subfunction_ = 0;
  /*!
   * @brief Defines if the Service support subfnuction or not.
   */
  bool supportSubfunction;
  /*!
   * @brief Defines the service name.
   */
  std::string serviceName;
  /*!
   * @brief Defines the trailing Service data.
   */
  std::vector<std::uint16_t> serviceData;
};
} // namespace uds
