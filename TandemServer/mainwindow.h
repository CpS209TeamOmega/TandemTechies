#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDebug>
#include<QTcpServer>
#include<QTcpSocket>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void clientConnect();
    void dataReceived();
    void clientDisconnect();
    
private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    int connectCount;

};

#endif // MAINWINDOW_H
