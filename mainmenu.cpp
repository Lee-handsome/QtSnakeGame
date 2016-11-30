#include "mainmenu.h"
#include "ui_mainmenu.h"


MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    setWindowTitle("魔幻贪吃蛇");
    about=new aboutMe(this);

}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_pushButton_clicked()
{
    w=new MainWindow(this);
    w->show();
}

void MainMenu::on_pushButton_4_clicked()
{
    about->show();
}

void MainMenu::on_pushButton_3_clicked()
{

    rank=new RankList();
    rank->show();
}

void MainMenu::on_pushButton_2_clicked()
{
    twoplayer = new Twoplayer(this);
    twoplayer->show();
}
