#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectCount = 0;

    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(clientConnect()));
    if (!server->listen(QHostAddress::Any, 5000)){
        qDebug() << "Cant connect.";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clientConnect(){
    QTcpSocket *sock = server->nextPendingConnection();

    if(connectCount == 1) {
        for(QObject *obj : server->children()) {
            QTcpSocket *tempsock = dynamic_cast<QTcpSocket*>(obj);
            if(tempsock && (tempsock != sock)) {
                tempsock->write(QString("Connect 1\n").toLocal8Bit());
            }
        }
        sock->write(QString("Connect 2\n").toLocal8Bit());
    }


    connect(sock, SIGNAL(disconnected()), this, SLOT(clientDisconnect()));
    connect(sock, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    ui->label_num->setText(QString::number(++connectCount));
}

void MainWindow::dataReceived(){
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());
    while(sock->canReadLine()){
        QString str = sock->readLine();
        ui->text->append(" "+str);

        for(QObject *obj : server->children()){
            QTcpSocket *tempsock = dynamic_cast<QTcpSocket*>(obj);
            if(tempsock && (tempsock != sock)){
                tempsock->write(str.toLocal8Bit());
            }
        }
    }
}

void MainWindow::clientDisconnect(){
    ui->label_num->setText(QString::number(--connectCount));
}
