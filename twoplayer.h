#ifndef TWOPLAYER_H
#define TWOPLAYER_H

//#include <QWidget>
#include <QtWidgets>
#include "twosnake.h"

class Twoplayer : public QMainWindow
{
    Q_OBJECT
public:
    explicit Twoplayer(QWidget *parent = 0);
    void startGame();

protected:
    void keyPressEvent(QKeyEvent * event);
    void paintEvent(QPaintEvent * event);

public slots:
    void timeover();
private:
    Twosnake doubleSnake;
    QTimer * time;
    int times;
    bool isDie;
    bool run;
};

#endif // TWOPLAYER_H
