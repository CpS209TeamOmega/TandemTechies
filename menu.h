#ifndef MENU_H
#define MENU_H

#include <QWidget>

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private slots:
    void on_btnStart_clicked();

    void on_btnLoad_clicked();

    void on_btnExit_clicked();

private:
    Ui::Menu *ui;

signals:
    void startGame();
    void loadGame();
    void exitGame();
};

#endif // MENU_H
