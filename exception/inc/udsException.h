#pragma once

#include <exception>
#include <string>

class SyntaxException : public std::exception {
public:
  SyntaxException(const std::string &mesg = "") { this->message += mesg; }
  [[nodiscard]] const char *what() const noexcept override {
    return (this->message).c_str();
  }

private:
  std::string message = "SyntaxException: ";
};

class OutOfRangeException : public std::exception {
public:
  OutOfRangeException(const std::string &mesg = "") { this->message += mesg; }
  [[nodiscard]] const char *what() const noexcept override {
    return (this->message).c_str();
  }

private:
  std::string message = "OutOfRangeException: ";
};

class ConfigNotFoundException : public std::exception {
public:
  ConfigNotFoundException(const std::string &mesg = "") {
    this->message += mesg;
  }

  [[nodiscard]] const char *what() const noexcept override {
    return (this->message).c_str();
  }

private:
  std::string message = "ConfigNotFoundException: ";
};

class TypeException : public std::exception {
public:
  TypeException(const std::string &mesg = "") { this->message = mesg; }
  [[nodiscard]] const char *what() const noexcept override {
    return (this->message).c_str();
  }

private:
  std::string message = "TypeException: ";
};
