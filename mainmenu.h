#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "mainwindow.h"
#include "aboutme.h"
#include "ranklist.h"
#include "twoplayer.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainMenu *ui;
    MainWindow* w;
    aboutMe* about;
    RankList * rank;
    Twoplayer * twoplayer;
};

#endif // MAINMENU_H
