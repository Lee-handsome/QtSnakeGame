#ifndef ABOUTME_H
#define ABOUTME_H

#include <QDialog>

namespace Ui {
class aboutMe;
}

class aboutMe : public QDialog
{
    Q_OBJECT

public:
    explicit aboutMe(QWidget *parent = 0);
    ~aboutMe();

private:
    Ui::aboutMe *ui;
};

#endif // ABOUTME_H
