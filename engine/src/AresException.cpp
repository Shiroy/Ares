//
// Created by tdancois on 8/5/16.
//

#include "AresException.h"

AresException::AresException(const std::string &message,
                             const std::string &emiter,
                             const std::string &method)
    : emiter(emiter),
      method(method),
      message(message) {}

std::string AresException::what() const {
  std::string err;

  if (emiter != "") err += emiter;
  if (method != "") err += ", " + method;
  err += message;

  return err;
}

const std::string &AresException::getEmiter() const {
  return emiter;
}

const std::string &AresException::getMethod() const {
  return method;
}

const std::string &AresException::getMessage() const {
  return message;
}

EntityManagerException::EntityManagerException(const std::string &message,
                                               const std::string &method)
    : AresException("EntityManager", method, message) {}
