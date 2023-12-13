#include "parser.h"
#include "metadata.h"
#include "toml/comments.hpp"
#include "toml/exception.hpp"
#include "toml/get.hpp"
#include "toml/parser.hpp"
#include "toml/value.hpp"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <toml.hpp>
#include <udsException.h>
#include <vector>

using namespace uds;
// Greedy
void UDSConfiguration::loadConfiguration(const std::string &config_path) {
  try {
    const auto &config_file = toml::parse<toml::discard_comments>(config_path);
    // extract the dids
    const auto &dids = toml::find<std::vector<toml::table>>(config_file, "did");
    for (auto &elt : dids) {
      std::string name = elt.find(NAME)->second.as_string();
      int size = elt.find(SIZE)->second.as_integer();
      std::string description = elt.find(DESCRIPTION)->second.as_string();
      std::uint16_t id = static_cast<uint16_t>(
          elt.find(ID)->second.as_integer()); // ensure written on 2 bytes
      auto &sessions = elt.find(SESSION)->second.as_array();
      // construct the did
      DID did = {
          .name = name,
          .description = description,
          .id = id,
          .size = size,
      };
      std::transform(
          sessions.cbegin(), sessions.cend(),
          std::back_inserter<decltype(did.sessions)>(did.sessions),
          [](auto &c) { return static_cast<uint8_t>(c.as_integer()); });
      did.sessions.shrink_to_fit();
      // push the did to the configuration member
      dids_configuration.push_back(did);
    }
    // TODO: add custom exception
  } catch (const toml::syntax_error &e) {
    throw SyntaxException(std::string(e.what()));
  } catch (const toml::type_error &e) {
    throw TypeException(std::string(e.what()));
  } catch (const std::out_of_range &e) {
    throw OutOfRangeException(std::string(e.what()));
  } catch (const std::runtime_error &e) {
    std::cout << "Runtime Error"
              << "Reason: " << e.what() << std::endl;
  }
}

std::string UDSConfiguration::getConfiguration(std::string &s) { return s; }

DID UDSConfiguration::getDidConfiguration(uint16_t id) const {
  auto found =
      (std::find_if(dids_configuration.begin(), dids_configuration.end(),
                    [&id](const DID &did) { return did.id == id; }));
  if (found == dids_configuration.end()) {
    throw ConfigNotFoundException("DID not found in the config file\n");
  }
  return *found;
}
