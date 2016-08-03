#pragma once

enum ValueType{
    NONE,
    BOOLEAN,
    STRING,
    NUMBER
};

#include <string>

class ReflectorValue {
    bool m_modified;
    ValueType type;

    std::string value_str;

    float value_number;

    bool value_boolean;

public:

    ReflectorValue(ValueType m_type = NONE);
    ReflectorValue(float value_number);
    ReflectorValue(const char* s);
    ReflectorValue(const std::string &value_str);
    ReflectorValue(bool value_boolean);

    ReflectorValue(const ReflectorValue& other) = default;

    const std::string &get_value_str() const;

    void set_value_str(const std::string &m_value_str);

    float get_value_number() const;

    void set_value_number(float m_value_number);

    bool get_value_boolean() const;

    void set_value_boolean(bool m_value_boolean);

    bool is_modified() const;

    ValueType get_value_type() const { return type; }
};
