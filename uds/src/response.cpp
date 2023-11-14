#include "response.h"
#include "metadata.h"
#include "service.h"
#include <algorithm>
#include <bits/ranges_algobase.h>
#include <cstdint>
#include <iterator>
#include <ostream>
#include <vector>
#include <ranges>

Response::Response(Service& service, ResponseCode code, std::vector<uint8_t>& data)
    : m_service(service), m_code(code), m_data(data) {}

Response::Response(Service& service, ResponseCode code) : m_service(service), m_code(code) {}

bool operator==(Response& resp, Response& other) {
  return (resp.m_service == other.m_service) 
    && (resp.m_code == other.m_code);
}

bool operator!=(Response& resp, Response& other) {
  return !(resp == other);
}

std::ostream& operator<<(std::ostream& out, const ResponseCode& code) {
  switch (code) {
    case ResponseCode::PositiveResponse:
      out << "PositiveResponse";
      break;
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, const Response& resp) {
  out << "<" << resp.m_code << ": [" << resp.m_service.getServiceName() << "] - " 
      <<  2 * resp.m_service.getServiceDataSize() << " data bytes>" ;
  return out;
}

std::vector<uint8_t> Response::getPayload(int size) {
  std::vector<uint8_t> payload; 
  int counter{0};

  if (m_code == ResponseCode::PositiveResponse) {
    payload.reserve(RESPONSE_SID_SIZE + 2 * 2 * m_service.getServiceDataSize());

    payload.push_back((RDBI + 0x40) & 0xFF);
    for (auto &did : m_service.getServiceData()) {
      // push the did
      payload.push_back((did >> 8) & 0xFF);
      payload.push_back((did) & 0xFF);
      
      // push the data
      // TODO: change it to ranges
      std::vector<uint8_t>::iterator it;
      for(it = m_data.begin() + counter; it < m_data.begin() + counter + size; it++) {
        payload.push_back((*it) & 0xFF);
      }
      counter += size;
    }
  } else {
    payload.reserve(NR_SID_SIZE + SERVICE_ID_SIZE + NACK_CODE_SIZE);
  } 

  return payload;
}



