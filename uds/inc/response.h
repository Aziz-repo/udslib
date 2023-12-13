#pragma once

#include "metadata.h"
#include "service.h"
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

  // operators
  friend bool ::operator==(Response &, Response &);
  friend bool ::operator!=(Response &, Response &);
  friend std::ostream & ::operator<<(std::ostream &, const Response &);

  std::vector<uint8_t> getPayload(int size);
  static Response fromPayload();

private:
  Service m_service;
  ResponseCode m_code;
  std::vector<uint8_t> m_data;
};

} // namespace uds
