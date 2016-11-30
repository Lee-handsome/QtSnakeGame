#include "twoplayer.h"

Twoplayer::Twoplayer(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("魔幻贪吃蛇双人模式");
    setFixedSize(600,600);
    isDie = false;
    run = true;
    time = new QTimer(this);
    connect(time, SIGNAL(timeout()), this, SLOT(timeover()));
    times = 200;
    time->start(times);
}

void Twoplayer::timeover(){
    if(!run)
    {
        time->stop();
        return;
    }
    doubleSnake.Move();
    isDie = doubleSnake.isDie();
    if(isDie){
        time->stop();
        doubleSnake.Clear();
        run = false;
        isDie = false;
        if(doubleSnake.winner==1){

            if(QMessageBox::Yes == QMessageBox::information(this, tr("Game Over"),
                    "1P获胜\n再来一局？",QMessageBox::Yes,QMessageBox::No))
            {
                startGame();
            }
            else{
                close();
            }
        }
        if(doubleSnake.winner==2){
            if(QMessageBox::Yes == QMessageBox::information(this, tr("Game Over"),
                    "2P获胜\n再来一局？",QMessageBox::Yes,QMessageBox::No))
            {
                startGame();
            }
            else{
                close();
            }
            return;
        }
    }
    update();
}
void Twoplayer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::gray);
    painter.drawRect(0, 0, size().width(), size().height());
    //画果子
    painter.setBrush(Qt::red);
    painter.drawEllipse(20*doubleSnake.Food.x, 20*doubleSnake.Food.y, 20, 20);
    //画蛇1
    painter.setBrush(Qt::yellow);
    painter.drawRect(20*doubleSnake.SnakeNode1[0].x, 20*doubleSnake.SnakeNode1[0].y, 20, 20);

    painter.setBrush(Qt::blue);
    int n = doubleSnake.SnakeNode1.size();
    for (int i = 1; i < n; i++)
    {
        painter.drawRect(20*doubleSnake.SnakeNode1[i].x, 20*doubleSnake.SnakeNode1[i].y, 20, 20);
    }
    //画蛇2
    painter.setBrush(Qt::yellow);
    painter.drawRect(20*doubleSnake.SnakeNode2[0].x, 20*doubleSnake.SnakeNode2[0].y, 20, 20);

    painter.setBrush(Qt::green);
    int n2 = doubleSnake.SnakeNode2.size();
    for (int i = 1; i < n2; i++)
    {
        painter.drawRect(20*doubleSnake.SnakeNode2[i].x, 20*doubleSnake.SnakeNode2[i].y, 20, 20);
    }
    QWidget::paintEvent(event);

}

void Twoplayer::keyPressEvent(QKeyEvent *event)
{

    int direct1=0;
    int direct2=0;
    switch (event->key()){
        case Qt::Key_W:
            direct1=1;
            break;
        case Qt::Key_D:
            direct1=2;
            break;
        case Qt::Key_S:
            direct1 = 3;
            break;
        case Qt::Key_A:
            direct1 = 4;
            break;

        case Qt::Key_Up:
            direct2=1;
            break;
        case Qt::Key_Right:
            direct2=2;
            break;
        case Qt::Key_Down:
            direct2 = 3;
            break;
        case Qt::Key_Left:
            direct2 = 4;
            break;
        default:
            break;
    }
    if(direct1){
        if (!(doubleSnake.direction1 == direct1 || doubleSnake.direction1 - direct1  == 2 ||
            doubleSnake.direction1 - direct1 == -2))
            doubleSnake.direction1 = direct1;
    }
    if(direct2)
    {
        if (!(doubleSnake.direction2 == direct2 || doubleSnake.direction2 - direct2  == 2 ||
            doubleSnake.direction2 - direct2 == -2))
            doubleSnake.direction2 = direct2;
    }
    QWidget::keyPressEvent(event);
}
void Twoplayer::startGame()
{
    run = true;
    times = 200;
    time->start(times);
    //snake.count=0;
}
