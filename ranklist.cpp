#include "ranklist.h"
#include "ui_ranklist.h"


RankList::RankList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RankList)
{
    ui->setupUi(this);
    setWindowTitle("贪吃蛇排行榜");

    QFile file("rank.txt");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"open error!\n";
    }
    QTextStream in(&file);
    QString name[3];
    int score[3];
    in>>name[0]>>score[0]>>name[1]>>score[1]>>name[2]>>score[2];

    for(int i=0;i<3;i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(name[i]));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(score[i])));
    }
}

RankList::~RankList()
{
    delete ui;
}
