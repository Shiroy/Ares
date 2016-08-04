//
// Created by antoine on 30/07/16.
//

#include "Reflector.h"
#include <algorithm>

std::map<std::string, ReflectorValue> Reflector::getValueForUpdate() {
    std::map<std::string, ReflectorValue> result;

    for(auto it: m_value){
        if(it.second.is_modified()){
            result.insert(std::pair<std::string, ReflectorValue>(it.first, it.second));
        }
    }

    return result;
}

std::map<std::string, ReflectorValue> Reflector::getValueForCreation() {
    return m_value;
}

void Reflector::markAsClean() {
    for(auto& value: m_value){
        value.second.markClean();
    }
}
