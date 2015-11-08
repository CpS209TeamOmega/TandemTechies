#ifndef NETWORK_H
#define NETWORK_H

#include <QTcpSocket>

class Network : public QTcpSocket {

private:
    static Network* instance_;

public:
    static Network& instance();
    static Network* pointer();

    void send(QString data);
};

#endif // NETWORK_H
