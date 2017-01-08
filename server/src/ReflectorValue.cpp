//
// Created by antoine on 30/07/16.
//

#include <cassert>
#include "ReflectorValue.h"

ReflectorValue::ReflectorValue(ValueType m_type) : type(m_type), m_modified(false) {}

const std::string &ReflectorValue::get_value_str() const {
  assert(type == STRING);
  return value_str;
}

void ReflectorValue::set_value_str(const std::string &m_value_str) {
  if (type == NONE) {
    type = STRING;
  }

  assert(type == STRING);
  m_modified = true;
  ReflectorValue::value_str = m_value_str;
}

float ReflectorValue::get_value_number() const {
  assert(type == NUMBER);
  return value_number;
}

void ReflectorValue::set_value_number(float m_value_number) {
  if (type == NONE) {
    type = NUMBER;
  }

  assert(type == NUMBER);
  m_modified = true;
  ReflectorValue::value_number = m_value_number;
}

bool ReflectorValue::get_value_boolean() const {
  assert(type == BOOLEAN);
  return value_boolean;
}

void ReflectorValue::set_value_boolean(bool m_value_boolean) {
  if (type == NONE) {
    type = BOOLEAN;
  }

  assert(type == BOOLEAN);
  m_modified = true;
  ReflectorValue::value_boolean = m_value_boolean;
}

bool ReflectorValue::is_modified() const {
  return m_modified;
}

ReflectorValue::ReflectorValue(float value_number) : value_number(value_number), type(NUMBER) {}

ReflectorValue::ReflectorValue(const std::string &value_str) : value_str(value_str), type(STRING) {}

ReflectorValue::ReflectorValue(const char *s) : ReflectorValue(std::string(s)) {}

ReflectorValue::ReflectorValue(bool value_boolean) : value_boolean(value_boolean), type(BOOLEAN) {}
