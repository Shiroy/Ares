//
// Created by antoine on 02/08/16.
//

#ifndef ARES_NETWORKTHREAD_H
#define ARES_NETWORKTHREAD_H


#include <LockedQueue.h>
#include <memory>
#include <atomic>
#include <Ares.pb.h>


class NetworkThread {
    LockedQueue<AresProtocol::AresMessage> receptionQueue;
    LockedQueue<AresProtocol::AresMessage> sendingQueue;

    std::atomic_bool m_stop;

public:
    NetworkThread() : m_stop(false) {}

    LockedQueue<AresProtocol::AresMessage> &getReceptionQueue() {
        return receptionQueue;
    }

    LockedQueue<AresProtocol::AresMessage> &getSendingQueue() {
        return sendingQueue;
    }

    void run();

    void stop() {
        m_stop = true;
    }
};


#endif //ARES_NETWORKTHREAD_H
