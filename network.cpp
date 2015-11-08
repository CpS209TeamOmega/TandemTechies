#include "network.h"

Network* Network::instance_ = nullptr;

Network& Network::instance() {
    if(!instance_) {
        instance_ = new Network();
    }
    return *instance_;
}

Network* Network::pointer() {
    return instance_;
}

void Network::send(QString data) {
    if(isOpen()) {
        write((data + "\n").toLocal8Bit());
    }
}
