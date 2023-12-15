/*!
 * @file udsException.h
 * @author M.Aziz Hassene
 * @brief Holds the exception related to this project.
 * @version v1.0.0
 * @date 2023-12-15
 */
#pragma once

#include <exception>
#include <string>

namespace uds {

/*!
 * @brief Raises when the config file does not response the TOML standard.
 * @note Wrapper over the syntax_error exception in the toml11 external library.
 *
 */
class SyntaxException : public std::exception {
public:
  /*!
   * @brief Constructor
   */
  SyntaxException(const std::string &mesg = "") { this->message += mesg; }
  /*!
   * @brief Return the exception message.
   */
  [[nodiscard]] const char *what() const noexcept override {
    return (this->message).c_str();
  }

private:
  std::string message = "SyntaxException: ";
};

/*!
 * @brief Raises when the required element does not exists in the config file.
 * @note Wrapper over the out_of_range_error exception in the toml11 external
 * library.
 *
 */
class OutOfRangeException : public std::exception {
public:
  /*!
   * @brief Constructor
   */
  OutOfRangeException(const std::string &mesg = "") { this->message += mesg; }
  /*!
   * @brief Return the exception message.
   */

  [[nodiscard]] const char *what() const noexcept override {
    return (this->message).c_str();
  }

private:
  std::string message = "OutOfRangeException: ";
};

/*!
 * @brief Raises when the required config does not exists in the config file.
 */
class ConfigNotFoundException : public std::exception {
public:
  /*!
   * @brief Constructor
   */
  ConfigNotFoundException(const std::string &mesg = "") {
    this->message += mesg;
  }
  /*!
   * @brief Return the exception message.
   */

  [[nodiscard]] const char *what() const noexcept override {
    return (this->message).c_str();
  }

private:
  std::string message = "ConfigNotFoundException: ";
};

/*!
 * @brief Raises when the required element does not mathc the specified type.
 * @note Wrapper over the type_error exception in thz roml11 external library.
 *
 */
class TypeException : public std::exception {
public:
  /*!
   * @brief Constructor
   */
  TypeException(const std::string &mesg = "") { this->message = mesg; }
  /*!
   * @brief Return the exception message.
   */
  [[nodiscard]] const char *what() const noexcept override {
    return (this->message).c_str();
  }

private:
  std::string message = "TypeException: ";
};
}; // namespace uds
