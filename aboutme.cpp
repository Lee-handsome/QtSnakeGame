#include "aboutme.h"
#include "ui_aboutme.h"

aboutMe::aboutMe(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutMe)
{
    ui->setupUi(this);
}

aboutMe::~aboutMe()
{
    delete ui;
}
