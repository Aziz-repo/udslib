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
  [[nodiscard]] ResponseCode getResponseCode() const { return m_code; }
  [[nodiscard]] bool isPositve() const {
    return m_code == ResponseCode::PositiveResponse ? true : false;
  }

  // operators
  friend bool ::operator==(Response &, Response &);
  friend bool ::operator!=(Response &, Response &);
  friend std::ostream & ::operator<<(std::ostream &, const Response &);

  std::vector<uint8_t> getPayload(int = 0);
  static Response fromPayload(const std::vector<uint8_t> &);

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
