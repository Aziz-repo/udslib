#include "response.h"
#include "metadata.h"
#include "service.h"
#include <cstdint>
#include <ostream>
#include <vector>

Response::Response(Service& service, ResponseCode code, std::vector<uint16_t>& data)
    : m_service(service), m_code(code), m_data(data) {}

Response::Response(Service& service, ResponseCode code) : m_service(service), m_code(code) {
  if (!m_service.getServiceData().empty()) {
    m_data = m_service.getServiceData();
  }
}

bool operator==(Response& resp, Response& other) {
  return (resp.m_service == other.m_service) 
    && (resp.m_code == other.m_code);
}

bool operator!=(Response& resp, Response& other) {
  return !(resp == other);
}

std::ostream& Response::operator<<(std::ostream& out) {
  out << "<" << m_code << ": [" << m_service.getServiceName() << "] - " 
      <<  m_service.getServiceData().size()<< " data bytes." ;
  return out;
}
