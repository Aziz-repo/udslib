#include "service.h"
#include "diagService.h"
#include <algorithm>
#include <bitset>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <exception>
#include <ostream>
#include <sstream>
#include <utility>
#include <vector>
#include <stdexcept>


Service::Service(const NonSubFuncService& service) {
    serviceId = service.serviceId;
    serviceName = service.serviceName;
    supportSubfunction = service.supportSubFunc;
    serviceData = { 0 }; 
}

Service::Service(const SubFuncService& service, uint8_t subfunction) {
    serviceId = service.serviceId;
    serviceName = service.serviceName;
    supportSubfunction = service.supportSubFunc;
    subfunction_ = subfunction;
}

Service::Service(const SubFuncService& service) {
    serviceId = service.serviceId;
    serviceName = service.serviceName;
    supportSubfunction = service.supportSubFunc;
}

Service::Service(const SubFuncService& service, uint8_t subfunction_ ,std::vector<uint16_t>& serviceData) {
    serviceId = service.serviceId;
    serviceName = service.serviceName;
    this->serviceData = serviceData;
    supportSubfunction = service.supportSubFunc;
    this->subfunction_ = subfunction_;
}

Service::Service(const NonSubFuncService& service, std::vector<uint16_t>& serviceData) {
    serviceId = service.serviceId;
    serviceName = service.serviceName;
    supportSubfunction = service.supportSubFunc;
    this->serviceData = serviceData;
} 

Service::Service(Service&& service) {  // move constructor
    serviceId = std::exchange(service.serviceId, std::uint16_t(0x0));
    serviceName = std::exchange(service.serviceName,  "");
    serviceData = std::exchange(service.serviceData, std::vector<uint16_t>{ 0 });
    subfunction_ = std::exchange(service.subfunction_, 0);
    supportSubfunction = std::exchange(service.supportSubfunction, 0);
} 

Service::Service(const Service& service) { // copy constructor 
    if (*this != service) {
      serviceId = service.serviceId;
      serviceName = service.serviceName;
      serviceData = service.serviceData;
      supportSubfunction = service.supportSubfunction;
      subfunction_ = service.subfunction_;
    }
  }

// TODO: fix this function
std::string Service::serialize() {
  std::ostringstream oss;
  oss << serviceId;
  if (supportSubfunction) { 
    oss << subfunction_;
  }
  if (!serviceData.empty()) { 
    for(const uint16_t& data : serviceData) {
      oss << data;
    }
  }
  return oss.str();
}

Service& Service::operator=(const Service& other) {
  if (*this != other) {
    this->serviceId = other.serviceId;
    this->serviceData = other.serviceData;
    this->subfunction_ = other.subfunction_;
    this->serviceName = other.serviceName;
    this->supportSubfunction = other.supportSubfunction;
  }
  return *this;
}

bool operator==(const Service& self, const Service& other) {
  if(self.supportSubfunction != other.supportSubfunction) return false;
  return (self.serviceId == other.serviceId);
}

bool operator!=(const Service& self, const Service& other) {
  return !(self == other);
}

std::ostream& operator<<(std::ostream& out, const Service& svc) {
  uint8_t sub = svc.supportSubfunction ? svc.subfunction_ : 0; 
  out << "Service ID: " << svc.serviceId 
          << "\nsubfunction: " << +sub; 
  return out;
}

Service Service::operator()(const NonSubFuncService& svc) {
  return Service(svc);
}

Service Service::operator()(const SubFuncService& svc) {
  return Service(svc);

}
