/*!
 *  @file diagService.h
 *  @author M.Aziz Hassene
 *  @brief This file contains the structures that compose the UDS services.
 *  @version v1.0.0
 *  @date  2023-12-15
 */

#pragma once

#include "metadata.h"
#include <cstdint>

namespace uds {

/*!
 * @brief a struct that represents a diagnotics service.
 *
 */
struct DiagService {
  /*!
   * @brief service name
   */
  std::string serviceName;
  /*!
   * @brief service ID(SID)
   */
  std::uint16_t serviceId;
  /*!
   * @brief support subfunction or not.
   */
  bool supportSubFunc;
};

/*!
 * @brief a struct that represents a diagnotics service that does not supports
 * subfunction.
 *
 */
struct NonSubFuncService : public DiagService {
  NonSubFuncService() { supportSubFunc = false; }
};

/*!
 * @brief a struct that represents a diagnotics service that supports
 * subfunction.
 *
 */
struct SubFuncService : public DiagService {
  SubFuncService() { supportSubFunc = true; }
};

/*!
 * @brief a struct that represents a diagnotics service.
 *
 */
struct ReadDataByIdentifer : public NonSubFuncService {
  ReadDataByIdentifer() {
    this->serviceName = "ReadDataByIdentifer";
    this->serviceId = std::uint8_t(RDBI);
    this->supportSubFunc = false;
  }
};

/*!
 * @brief a struct that represents a diagnotics service.
 *
 */
struct WriteDataByIdentifer : public NonSubFuncService {
  WriteDataByIdentifer() {
    this->serviceName = "WriteDataByIdentifer";
    this->serviceId = std::uint8_t(WDBI);
    this->supportSubFunc = false;
  }
};

/*!
 * @brief a struct that represents a diagnotics service.
 *
 */
struct ECUReset : public SubFuncService {
  ECUReset() {
    this->serviceName = "ECUReset";
    this->serviceId = std::uint8_t(ECUR);
    this->supportSubFunc = true;
  }
};

} // namespace uds
