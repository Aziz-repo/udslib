#include "response.h"
#include "metadata.h"
#include "service.h"
#include <algorithm>
#include <bits/ranges_algobase.h>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <ostream>
#include <vector>

using namespace uds;

Response::Response(Service &service, ResponseCode code,
                   std::vector<uint8_t> &data)
    : m_service(service), m_code(code), m_data(data) {}

Response::Response(Service &service, ResponseCode code)
    : m_service(service), m_code(code) {}

bool operator==(Response &resp, Response &other) {
  return (resp.m_service == other.m_service) && (resp.m_code == other.m_code);
}

bool operator!=(Response &resp, Response &other) { return !(resp == other); }

std::ostream &operator<<(std::ostream &out, const ResponseCode &code) {
  switch (code) {
  case ResponseCode::PositiveResponse:
    out << "Positive Response";
    break;
  case ResponseCode::GeneralReject:
    out << "General Reject";
    break;
  case ResponseCode::ServiceNotSupported:
    out << "Service Not Supproted";
    break;
  case ResponseCode::SubFunctionNotSupported:
    out << "Subfunction Not Supproted";
    break;
  case ResponseCode::InvalidMessageLengthOrFormat:
    out << "Invalid Message Length or Format";
    break;
  case ResponseCode::ResponseTooLong:
    out << "Response Too Long";
    break;
  case ResponseCode::BusyRepeatRequest:
    out << "Busy Repeat Request";
    break;
  case ResponseCode::ConditionsNotCorrect:
    out << "Conditions Not Correnct";
    break;
  case ResponseCode::RequestSequenceError:
    out << "Request Sequence Error";
    break;
  }
  return out;
}

std::ostream &operator<<(std::ostream &out, const Response &resp) {
  if (resp.isPositve()) {
    out << "<" << resp.m_code << ": [" << resp.m_service.getServiceName()
        << "] - " << 2 * resp.m_service.getServiceDataSize() << " data bytes>";
  } else {
    // TODO: Test this
    out << "<Negative Response: [" << resp.m_service.getServiceName() << "]"
        << " - NRC: " << resp.m_code << "]";
  }
  return out;
}

std::vector<uint8_t> Response::getPayload(int size) {
  std::vector<uint8_t> payload{};
  int counter{0};

  if (m_code == ResponseCode::PositiveResponse) {
    assert(size != 0);
    payload.reserve(RESPONSE_SID_SIZE + 2 * 2 * m_service.getServiceDataSize());
    payload.push_back((this->m_service.getServiceId() + 0x40) & 0xFF);
    for (auto &did : m_service.getServiceData()) {
      payload.push_back((did >> 8) & 0xFF);
      payload.push_back((did) & 0xFF);

      std::vector<uint8_t>::iterator it;
      for (it = m_data.begin() + counter; it < m_data.begin() + counter + size;
           it++) {
        payload.push_back((*it) & 0xFF);
      }
      counter += size;
    }
  } else {
    payload.reserve(NR_SID_SIZE + SERVICE_ID_SIZE + NACK_CODE_SIZE);
    // push the negative response code
    payload.push_back((NACK_CODE & 0xFF));

    // push the SID
    payload.push_back((this->m_service.getServiceId()) & 0xFF);

    // push the NACK code
    payload.push_back(static_cast<uint8_t>(this->m_code));
  }

  return payload;
}

Response Response::fromPayload(const std::vector<uint8_t> &payload) {
  Response response;
  uint8_t code = payload.at(0);
  if (code != NACK_CODE) {
    response.m_code = ResponseCode::PositiveResponse;
    // TODO: fill the service object
    response.m_service = Service::fromResponseId(code);
    int padding{0};
    if (response.m_service.getSupportSubFunction()) {
      padding = RESPONSE_SID_SIZE + SERVICE_SUBFUNCTION_SIZE;
    } else {
      padding = RESPONSE_SID_SIZE;
    }
    std::copy(payload.begin() + padding, payload.end(),
              std::back_inserter(response.m_data));
  } else {
    // TODO: in case of negative response
    response.m_code = Response::toResponseCode(payload.at(2)); // 3rd Byte = NRC
  }

  return response;
}
