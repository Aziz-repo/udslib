#include "response.h"
#include "metadata.h"
#include "service.h"
#include <cstdint>
#include <vector>

Response::Response(Service& service, ResponseCode code, std::vector<uint16_t>& data)
    : m_service(service), m_code(code), m_data(data) {}

std::vector<uint8_t> Response::getPayload() {
    
}
