#pragma once

namespace uds {

  #define SERVICE_ID_SIZE              1
  #define SERVICE_SUBFUNCTION_SIZE     1
  #define RESPONSE_SID_SIZE            1 
  #define NR_SID_SIZE                  1 
  #define NACK_CODE_SIZE               1

  #define RDBI                      0x22 // Read Data By Identifer
  #define WDBI                      0x2E // Write Data By Identifer
  #define ECUR                      0x11 // ECU Reset 
  #define CDI                       0x14 // Clear DTC Information
  #define CDS                       0x85 // Control DTC Settings

  #define NACK_CODE                 0x7F


  enum class ResponseCode {
    PositiveResponse = 0,

  };
}

