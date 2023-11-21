#pragma once

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iterator>
#include <map>
#include <string>

namespace uds {
class UDSConfiguration {
public:
  UDSConfiguration() = default;
  ~UDSConfiguration() = default;

  void loadConfiguration(const std::filesystem::path &);
  std::string getConfiguration(std::string &);
  void trimConfiguration(std::string &);

private:

  static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    [](int c) { return !std::isspace(c); }));
    return s;
  }

  static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](int c) { return !std::isspace(c); })
                .base(),
            s.end());
    return s;
  }

  std::map<std::string, std::string> configuration_options_;
};
} // namespace uds
