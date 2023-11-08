#include "request.h"
#include "service.h"
#include <cstdint>
#include <ostream>
#include <utility>
#include <variant>
#include <vector>


Request::Request(const Service& svc) : m_service(svc) {
  if(!svc.getServiceData().empty()) {
    m_data = svc.getServiceData();
  }
}

Request::Request(const Service& svc, const std::vector<uint16_t> requestData) : m_service(svc), m_data(requestData) {}

Request::Request(const Request& req) {
  m_service = req.m_service;
  m_data = req.m_data;
}

Request::Request(Request&& req) {
  std::exchange(req.m_service, Service());
  std::exchange(req.m_data, {});
}

bool operator==(const Request& req, const Request& o_req) {
  return req.m_service == o_req.m_service && req.m_data == o_req.m_data;
}

bool operator!=(const Request& req, const Request& o_req) {
  return !(req == o_req);
}

std::ostream& operator<<(std::ostream& out, const Request& req) {
  out << "<Request: [" << req.m_service.getServiceName() 
              << "] (subfunction " << +req.m_service.getSubfunction() 
              << ") - " << 2 * (req.m_data.size()) << " data bytes>";
  return out;
}

std::string Request::getPayload() {
  return m_service.serialize();
}

