#include "diagService.h"
#include "service.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

class Request {

public:
  Request() = default;
  Request(const Service&);
  Request(const Service&, std::vector<uint16_t>);
  Request(const Request&);
  Request(Request&&);
  ~Request() = default;

  // getter 
  Service getService() const { return m_service; }
  std::vector<uint16_t> getRequestData() const { return m_data; }

  // setter
  void setRequestData(const std::vector<uint16_t>& data) { m_data = data; }
  void setService(const Service& svc) { m_service = svc; } 
  
  // operators
  friend bool operator==(const Request&, const Request&);
  friend bool operator!=(const Request&, const Request&);
  friend std::ostream& operator<<(std::ostream&, const Request&);
  
  std::vector<uint8_t> getPayload();
  
  static Request fromPayload(std::string rawRequest) {
    Request req;
    uint8_t Id = std::atoi(rawRequest.substr(0, 2).c_str());
    Service service = Service::fromRequestId(Id);    
    // set the subfunction if exists
    if (service.getSupportSubFunction()) {
      uint8_t subfunction = std::atoi(rawRequest.substr(2, 1).c_str());
      service.setSubfunction(subfunction);
    }
    req.setService(service);
    return req;
  }

private:
  Service m_service;
  std::vector<uint16_t> m_data;
};
