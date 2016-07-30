#pragma once

#include <map>
#include <string>
#include "ReflectorValue.h"

class Reflector {
    std::map<std::string, ReflectorValue> m_value;

public:
    std::map<std::string, ReflectorValue> getValueForCreation();
    std::map<std::string, ReflectorValue> getValueForUpdate();

    ReflectorValue& operator[](const std::string& key) { return m_value[key]; }
};
