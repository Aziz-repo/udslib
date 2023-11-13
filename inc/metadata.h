#pragma once

#define SERVICE_ID_SIZE              1
#define SERVICE_SUBFUNCTION_SIZE     1

#define RDBI                      0x22 // Read Data By Identifer
#define WDBI                      0x2E // Write Data By Identifer
#define ECUR                      0x11 // ECU Reset 
#define CDI                       0x14 // Clear DTC Information
#define CDS                       0x85 // Control DTC Settings
//
//
enum class ResponseCode {
  PositiveResponse = 0,
};
