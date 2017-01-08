//
// Created by tdancois on 8/5/16.
//

#ifndef ARES_EXCEPTION_H
#define ARES_EXCEPTION_H

#include <exception>
#include <string>

class AresException {
  std::string emiter;
  std::string method;
  std::string message;

 public:
  explicit AresException(const std::string &message, const std::string &emiter = "", const std::string &method = "");

  virtual std::string what() const;

  const std::string &getEmiter() const;

  const std::string &getMethod() const;

  const std::string &getMessage() const;
};

class EntityManagerException : public AresException {
 public:
  explicit EntityManagerException(const std::string &message, const std::string &method = "");
};

#endif //ARES_EXCEPTION_H
