/*!
 * @file response.h
 * @author M.Aziz Hassene
 * @brief Abstracts the response payload.
 * @version v1.0.0
 * @date 2023-12-15
 *
 * */
#pragma once

#include "metadata.h"
#include "service.h"
#include <cstdint>
#include <ostream>
#include <vector>

namespace uds {
class Response;
}

bool operator==(uds::Response &, uds::Response &);
bool operator!=(uds::Response &, uds::Response &);
std::ostream &operator<<(std::ostream &, const uds::Response &);

namespace uds {

class Response {
public:
  Response() = default;
  Response(Service &, ResponseCode, std::vector<uint8_t> &);
  Response(Service &, ResponseCode);
  Response(Response &&) = default;
  Response(const Response &) = default;
  Response &operator=(Response &&) = default;
  Response &operator=(const Response &) = default;
  ~Response() = default;

  // getters

  /*!
   * @brief Returns the response code
   */
  [[nodiscard]] ResponseCode getResponseCode() const { return m_code; }

  /*!
   * @brief Checks if the response is positve or not.
   */
  [[nodiscard]] bool isPositve() const {
    return m_code == ResponseCode::PositiveResponse ? true : false;
  }

  // operators
  friend bool ::operator==(Response &, Response &);
  friend bool ::operator!=(Response &, Response &);
  friend std::ostream & ::operator<<(std::ostream &, const Response &);

  /*!
   * @brief Serialize the Response object into an UDS payload.
   * @param size of the intended data. (Default to 0 in case of negative
   * response)
   */
  std::vector<uint8_t> getPayload(int size = 0);
  /*!
   * @brief Deserialize the response payload into a Response object.
   * @param payload intended to be converted to a Response object.
   */
  static Response fromPayload(const std::vector<uint8_t> &payload);

private:
  Service m_service;
  ResponseCode m_code;
  std::vector<uint8_t> m_data;

  // TODO:finish the implementation of this method
  static ResponseCode toResponseCode(uint8_t code) {
    auto code_ = static_cast<ResponseCode>(code);
    return code_;
  }
};

} // namespace uds
