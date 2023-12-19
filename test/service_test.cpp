#include "diagService.h"
#include <cstdint>
#include <gtest/gtest.h>
#include <service.h>

namespace {

using namespace uds;
TEST(Constructor, SubFuncConstructor) {
  const SubFuncService s;

  EXPECT_EQ(s.supportSubFunc, true);
}

TEST(Constructor, NonSubFuncConstructor) {
  const NonSubFuncService s;

  EXPECT_EQ(s.supportSubFunc, false);
}

TEST(Getters, ServiceID) {
  ReadDataByIdentifer r;
  Service s(r);

  EXPECT_EQ(s.getServiceId(), 0x22);
}

TEST(Getters, ServiceName) {
  ECUReset r;
  Service s(r);

  EXPECT_EQ(s.getServiceName(), std::string("ECUReset"));
}

TEST(Getters, SubFunction) {
  ECUReset r;
  Service s(r, 0x1);

  EXPECT_EQ(s.getSubfunction(), 0x1);
}

TEST(Getters, ServiceData) {
  ReadDataByIdentifer r;
  Service s(r);

  std::vector<uint16_t> v{0xF180};

  EXPECT_EQ(s.hasData(), false);

  s.setServiceData(v);

  EXPECT_EQ(s.hasData(), true);
}

TEST(Methods, fromRequestID) {
  Service s = Service::fromRequestId(0x22);
  EXPECT_STREQ(s.getServiceName().c_str(), "ReadDataByIdentifer");
  EXPECT_EQ(s.getServiceId(), 0x22);
  EXPECT_EQ(s.getSupportSubFunction(), false);
}

} // namespace
