#pragma once

#include "metadata.h"
#include "service.h"
#include <cstdint>
#include <vector>

class Response {
public:
  Response() = default;
  Response(Service&, ResponseCode, std::vector<uint16_t>&);
  Response(Response &&) = default;
  Response(const Response &) = default;
  Response &operator=(Response &&) = default;
  Response &operator=(const Response &) = default;
  ~Response() = default;

  // getters
  ResponseCode getResponseCode() const { return m_code; }

  std::vector<uint8_t> getPayload();
  static Response fromPayload() {

  }

private:
  Service m_service;
  ResponseCode m_code;
  std::vector<uint16_t> m_data;
  
};


