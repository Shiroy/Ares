//
// Created by antoine on 30/07/16.
//

#include "Player.h"
#include "Server.h"

Player::Player(unsigned int m_id, const std::string &m_name, std::shared_ptr<Client> client) : Entity(m_id, m_name),
                                                                                               client(client) {

}

void Player::addToWorld() {
    sendCreationMessage();
    m_reflectors.markAsClean();
}

void Player::sendCreationMessage() {
    AresProtocol::AresMessage addMessage = getCreationMessage();
    client->sendPacket(addMessage);
    addMessage.mutable_modifyobject()->mutable_create()->set_myself(false);
    Server::getInstance().broadcast(addMessage, client);
}

AresProtocol::AresMessage Player::getCreationMessage() {
    AresProtocol::AresMessage addMessage;
    AresProtocol::ModifyObject *modifyObject = addMessage.mutable_modifyobject();

    modifyObject->set_id(getId());

    AresProtocol::ModifyObject_CreateObject *createObject = modifyObject->mutable_create();
    createObject->set_myself(true);
    createObject->mutable_position()->set_x(1000.0f);
    createObject->mutable_position()->set_y(1000.0f);
    createObject->set_type(AresProtocol::ModifyObject_CreateObject_ObjectType_PLAYER);

    auto reflectors = m_reflectors.getValueForCreation();
    for (auto reflectorValue : reflectors) {
        AresProtocol::ModifyObject_ReflectorMap *pktReflector = createObject->add_reflector();
        pktReflector->set_key(reflectorValue.first);

        switch (reflectorValue.second.get_value_type()) {
            case BOOLEAN :
                pktReflector->set_boolean(reflectorValue.second.get_value_boolean());
                break;
            case NUMBER :
                pktReflector->set_number(reflectorValue.second.get_value_number());
                break;
            case STRING :
                pktReflector->set_string(reflectorValue.second.get_value_str());
                break;
            default:
                continue;
        }
    }
    return addMessage;
}

