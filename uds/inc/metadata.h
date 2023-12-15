#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace uds {

#define SERVICE_ID_SIZE 1
#define SERVICE_SUBFUNCTION_SIZE 1
#define RESPONSE_SID_SIZE 1
#define NR_SID_SIZE 1
#define NACK_CODE_SIZE 1

#define RDBI 0x22 // Read Data By Identifer
#define WDBI 0x2E // Write Data By Identifer
#define ECUR 0x11 // ECU Reset
#define CDI 0x14  // Clear DTC Information
#define CDS 0x85  // Control DTC Settings

#define NACK_CODE 0x7F
#define PRESPONSE_IND 0x40

#define NAME "name"
#define SIZE "size"
#define DESCRIPTION "description"
#define ID "id"
#define SESSION "session"

enum class ResponseCode {
  PositiveResponse = 0,
  GeneralReject = 0x10,
  ServiceNotSupported = 0x11,
  SubFunctionNotSupported = 0x12,
  InvalidMessageLengthOrFormat = 0x13,
  ResponseTooLong = 0x14,
  BusyRepeatRequest = 0x21,
  ConditionsNotCorrect = 0x22,
  RequestSequenceError = 0x24,
};

struct DID {
  std::string name;
  std::string description;
  uint16_t id;
  int size;
  std::vector<uint8_t> sessions;

  bool operator==(const uint16_t &id) const { return this->id == id; }
};
} // namespace uds
