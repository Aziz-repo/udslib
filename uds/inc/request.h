/*!
 * @file request.h
 * @author M.Aziz Hassene
 * @brief Abstracts the request payload.
 * @version v1.0.0
 * @date 2023-12-15
 *
 */
#pragma once

#include "service.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

namespace uds {
class Request;
}

bool operator==(const uds::Request &, const uds::Request &);
bool operator!=(const uds::Request &, const uds::Request &);
std::ostream &operator<<(std::ostream &, const uds::Request &);

namespace uds {

class Request {

public:
  Request() = default;
  Request(const Service &);
  Request(const Service &, std::vector<uint16_t>);
  Request(const Request &);
  Request(Request &&);
  ~Request() = default;

  // getter

  /*!
   * @brief Returns the service.
   */
  [[nodiscard]] Service getService() const { return m_service; }

  /*!
   * @brief Returns request data.
   */
  [[nodiscard]] std::vector<uint16_t> getRequestData() const { return m_data; }

  // setter

  /*!
   * @brief Set the request data.
   */
  void setRequestData(const std::vector<uint16_t> &data) { m_data = data; }
  /*!
   * @brief Set the service.
   */
  void setService(const Service &svc) { m_service = svc; }

  // operators
  friend bool ::operator==(const Request &, const Request &);
  friend bool ::operator!=(const Request &, const Request &);
  friend std::ostream & ::operator<<(std::ostream &, const Request &);

  /*!
   * @brief serialize the Request object into an UDS payload.
   *
   */
  std::vector<uint8_t> getPayload();

  /*!
   * @brief Deserialize the request payload into a Request object.
   * @param rawRequest intended to be converted to a Request object.
   *
   */
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
  /*!
   * @brief Service object corresponding to the request.
   */
  Service m_service;
  /*!
   * @brief Service data corresponding to the request.
   */
  std::vector<uint16_t> m_data;
};

} // namespace uds
