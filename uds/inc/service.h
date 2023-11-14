#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <ostream>
#include <bitset>
#include "diagService.h"

class Service {
public:
  Service() = default;
  Service(const NonSubFuncService& service);
  Service(const SubFuncService& service);
  Service(const SubFuncService& service, uint8_t subfunction);
  Service(const SubFuncService& service, uint8_t subfunction ,std::vector<uint16_t>& serviceData);
  Service(const NonSubFuncService& service, std::vector<uint16_t>& serviceData);
  Service(Service&& service);  // move constructor
  Service(const Service& service); // copy constructor 
  ~Service() = default;

  // operators
  friend bool operator==(const Service&, const Service&);
  friend bool operator!=(const Service&, const Service&);
  Service& operator=(const Service&);
  friend std::ostream& operator<<(std::ostream&, const Service&);
  Service operator()(const NonSubFuncService&);
  Service operator()(const SubFuncService&);


  // getter 
  uint8_t getServiceId() const { return serviceId; }
  std::string getServiceName() const { return serviceName; }
  std::vector<std::uint16_t> getServiceData() const { return serviceData; }
  std::uint8_t getSubfunction() const { return subfunction_; }
  bool getSupportSubFunction() const { return supportSubfunction; }
  size_t getServiceDataSize() const { return serviceData.size(); }
  
  bool hasData() const { return serviceData.empty(); }

  // setter
  void setSubfunction(uint8_t subfunction) { this->subfunction_ = subfunction; }
  void setServiceData(std::vector<std::uint16_t> serviceData) { this->serviceData = serviceData; }

  // serialize and deserialize
  std::vector<uint8_t> serialize();

  void deserialize();

  static std::string logServiceData(const Service& service) {
    std::string serviceData;
    for (auto &e : service.serviceData) {
      serviceData.append((char)*&e, sizeof(e)); 
    }
    return serviceData;
  } 

  static Service fromRequestId(uint16_t serviceId) {
    Service service;
    switch (serviceId) {
      case 0x22: service = Service(ReadDataByIdentifer()); break;
      case 0x11: service =  Service(ECUReset()); break;
      case 0x2E: service =  Service(WriteDataByIdentifer()); break;
    }
    return service;
  }

private:
  std::uint8_t serviceId;
  uint8_t subfunction_ = 0;
  bool supportSubfunction;
  std::string serviceName;
  std::vector<std::uint16_t> serviceData;
  
};

