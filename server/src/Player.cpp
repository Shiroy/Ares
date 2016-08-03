//
// Created by antoine on 30/07/16.
//

#include "Player.h"

Player::Player(unsigned int m_id, const std::string &m_name, std::shared_ptr<Client> client) : Entity(m_id, m_name), client(client) {

}

void Player::addToWorld() {
    AresProtocol::AresMessage addMessage;
    AresProtocol::ModifyObject *modifyObject = addMessage.mutable_modifyobject();

    modifyObject->set_id(getId());

    AresProtocol::ModifyObject_CreateObject* createObject = modifyObject->mutable_create();
    createObject->set_myself(true);
    createObject->mutable_position()->set_x(1000.0f);
    createObject->mutable_position()->set_y(1000.0f);
    createObject->set_type(AresProtocol::ModifyObject_CreateObject_ObjectType_PLAYER);

    auto reflectors = m_reflectors.getValueForCreation();
    for(auto reflectorValue : reflectors) {
        AresProtocol::ModifyObject_ReflectorMap* pktReflector = createObject->add_reflector();
        pktReflector->set_key(reflectorValue.first);

        switch (reflectorValue.second.get_value_type()) {
            case ValueType::BOOLEAN :
                pktReflector->set_boolean(reflectorValue.second.get_value_boolean());
                break;
            case ValueType::NUMBER :
                pktReflector->set_number(reflectorValue.second.get_value_number());
                break;
            case ValueType::STRING :
                pktReflector->set_string(reflectorValue.second.get_value_str());
                break;
            default:
                continue;
        }
    }

    client->sendPacket(addMessage);
}

