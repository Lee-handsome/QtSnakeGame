#include "snake.h"
#include "mainwindow.h"
#include <QFile>
#include <QDebug>
#include <iostream>
#include <vector>
#include <QString>

using namespace std;

MainWindow::MainWindow(QWidget * parent):
    QMainWindow(parent)
{
    setWindowTitle(tr("魔幻贪吃蛇"));
    MenuBarSize = 20;
    setFixedSize(600,600+MenuBarSize);
	dealMenu();
    info = new QLabel(this);
    info->setGeometry(5,30,60,20);

	IsDie = false;
    run = true;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
	times = 200;
	timer->start(times);
}

MainWindow::~MainWindow()
{

}

void MainWindow::timeout(void)
{
    QString str= QString::number(snake.count*10);
    info->setText("得分："+str);
    if (run == false)
	{
		timer->stop();
		return;
	}

	snake.Move();
	IsDie = snake.IsDie();
	if (IsDie)
	{
		timer->stop();
        run = false;
        IsDie = false;
        snake.Clear();
        dealRank();

        if(QMessageBox::Yes == QMessageBox::information(this, tr("Game Over"),
                "您的最终得分为"+ str +"\n再来一局？",QMessageBox::Yes,QMessageBox::No))
        {
            startGame();
        }
        else{
            close();
        }
		return;
	}
	update();
}

//获取当前成绩的排名
void MainWindow::dealRank()
{
    QFile file("rank.txt");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"open error!\n";
    }
    QTextStream in(&file);
    QString name[3];
    int score[3];
    in>>name[0]>>score[0]>>name[1]>>score[1]>>name[2]>>score[2];
    qDebug()<<"Debug:"<<name[0]<<score[0];
    for(int i=0;i<3;i++)
    {
        if(snake.count*10>=score[i])
        {
            for(int j=2;j>i;j--)
            {
                name[j]=name[j-1];
                score[j]=score[j-1];
            }
            score[i]=snake.count*10;
            name[i]=QInputDialog::getText(NULL, "排行榜登记","恭喜您登上排行榜\n请输入你的昵称",
                                                       QLineEdit::Normal);
            break;
        }
    }
    file.close();

    QFile f("rank.txt");
    if(!f.open(QIODevice::WriteOnly)){
        qDebug()<<"open error!\n";
    }
    QTextStream out(&f);
    for(int i=0;i<3;i++)
        out<<name[i]<<" "<<score[i]<<" ";
    f.close();
}


void MainWindow::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
    painter.setBrush(Qt::gray);
	painter.drawRect(0, 0, size().width(), size().height());
    if (IsDie || !run)
	{
		return;
	}
    vector<Node> snakenode;
    Node food;
    snake.OutputSnake(snakenode, food);
	//画果子
    painter.setBrush(Qt::red);
    painter.drawEllipse(20*food.x, 20*food.y+MenuBarSize, 20, 20);
	//画墙
    /*
	painter.setBrush(Qt::white);
    painter.drawRect(0, 0+MenuBarSize, 600, 10);  //上
    painter.drawRect(0, 600+MenuBarSize, 600, 10); //下
    painter.drawRect(0, 0+MenuBarSize, 10, 600); //左
    painter.drawRect(600, 0+MenuBarSize, 10, 600); //右
    */
	//画蛇，蛇头跟蛇身用不同的颜色
	//蛇头
	painter.setBrush(Qt::yellow);
    painter.drawRect(20*snakenode[0].x, 20*snakenode[0].y+MenuBarSize, 20, 20);

	painter.setBrush(Qt::blue);
    int n = snakenode.size();
	for (int i = 1; i < n; i++)
	{
        painter.drawRect(20*snakenode[i].x, 20*snakenode[i].y+MenuBarSize, 20, 20);
        //qDebug()<<snakenode[i].x<<" "<<snakenode[i].y;
	}

	QWidget::paintEvent(event);
}


void MainWindow::keyPressEvent(QKeyEvent * event)
{
	int direct = 0;
	switch (event->key())
	{
    case Qt::Key_W:
        direct = 1;
		break;
    case Qt::Key_D:
		direct = 2;
		break;
    case Qt::Key_S:
		direct = 3;
		break;
    case Qt::Key_A:
		direct = 4;
		break;
	case Qt::Key_U:
		speedUp();
		break;
    case Qt::Key_N:
		speedDown();
        break;
    case Qt::Key_P:
        pauseGame();
        break;
	default:
		break;
	}
    if(direct != 0) snake.ChangeDirector(direct);
	QWidget::keyPressEvent(event);
}

//处理菜单的函数
void MainWindow::dealMenu(void)
{
	QMenuBar * menuBar = new QMenuBar(this);
    QMenu * gameMenu = new QMenu(tr("选项"), menuBar);
	QMenu * helpMenu = new QMenu(tr("帮助"), menuBar);

    QAction * startGame = new QAction(tr("重新开始"), gameMenu);
    QAction * pauseGame = new QAction(tr("暂停"), gameMenu);
	QAction * speedUp = new QAction(tr("游戏加速"), gameMenu);
	QAction * speedDown = new QAction(tr("游戏减速"), gameMenu);
    QAction * quitGame = new QAction(tr("结束"), gameMenu);
	gameMenu->addAction(startGame);
	gameMenu->addAction(pauseGame);
	gameMenu->addAction(speedUp);
	gameMenu->addAction(speedDown);
	gameMenu->addAction(quitGame);
	menuBar->addMenu(gameMenu);
	connect(startGame, SIGNAL(triggered()), this, SLOT(startGame()));
	connect(pauseGame, SIGNAL(triggered()), this, SLOT(pauseGame()));
	connect(speedUp, SIGNAL(triggered()), this, SLOT(speedUp()));
	connect(speedDown, SIGNAL(triggered()), this, SLOT(speedDown()));
	connect(quitGame, SIGNAL(triggered()), this, SLOT(close()));

    QAction * helpGame = new QAction(tr("操作说明"), helpMenu);
	QAction * aboutGame = new QAction(tr("关于"), helpMenu);
	helpMenu->addAction(helpGame);
	helpMenu->addAction(aboutGame);
	menuBar->addMenu(helpMenu);
	connect(helpGame, SIGNAL(triggered()), this, SLOT(showHelp()));
	connect(aboutGame, SIGNAL(triggered()), this, SLOT(showAbout()));

	setMenuBar(menuBar);


}

void MainWindow::showAbout(void)
{
    QMessageBox::information(this, tr("关于贪吃蛇"),
                   tr("QT5：魔幻贪吃蛇1.0。"));
}

void MainWindow::showHelp(void)
{
    QMessageBox::information(this, tr("操作说明"),
                   tr("W上，S下，A左，D右\nU加速，N减速\nP暂停"));
}

void MainWindow::startGame(void)
{
    run = true;
    times = 200;
	timer->start(times);
    snake.count=0;
}

void MainWindow::pauseGame(void)
{
    if(run){
        run = false;
        timer->stop();
    }
    else{
        run=true;
        timer->start();
    }
}

void MainWindow::speedUp(void)
{
	times -= 20;  
	if (times <= 20)
	{
		times = 20;
	}
	timer->stop();
	timer->start(times);
}

void MainWindow::speedDown(void)
{
	times += 20;
	if (times >= 500)
	{
		times = 500;
	}
	timer->stop();
	timer->start(times);
}
