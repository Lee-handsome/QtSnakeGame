/*贪食蛇类的实现*/

#include <cstdlib>
#include <ctime>
#include "snake.h"

Snake::Snake(int  w, int  h)
{

    height = h;
    width = w;
	length = 0;
	AddNode(w/2, h/2);
    AddNode(w/2,h/2+1);
    AddNode(w/2,h/2+2);
    count=0;
	PutFood();
	die = false;
    director = 1;  //初始方向向上
}

Snake::~Snake(void)
{
	SnakeNode.clear();
}

void Snake::AddNode(const int & w, const int & h)
{
	Node * newNode = new Node;
	newNode->x = w;
	newNode->y = h;
	SnakeNode.push_back(*newNode);
    length++;
}


void Snake::Judge(void)
{
	//判断是否撞墙
    if (SnakeNode[0].x < 0 || SnakeNode[0].x == width ||
        SnakeNode[0].y < 0 || SnakeNode[0].y == height)
	{
		die = true;
		return;
	}
	//判断蛇是否跟自己相撞
	for (int i = 1; i < length; i++)
	{
		if (SnakeNode[0].x == SnakeNode[i].x &&
		    SnakeNode[0].y == SnakeNode[i].y)
		{
			die = true;
			return;
		}
	}

	die = false;
}

//返回蛇的生死状态
bool Snake::IsDie(void)
{
	return die;
}

void Snake::Move(void)
{
	//记录蛇尾的位置，用来在吃到果子的时侯增加长度
	int lastX = SnakeNode[length-1].x;
	int lastY = SnakeNode[length-1].y;

	for (int i = length - 1; i > 0; i--)
	{
		SnakeNode[i].x = SnakeNode[i-1].x;
		SnakeNode[i].y = SnakeNode[i-1].y;
	}
	//根据当前方向处理蛇头
    switch (director)
	{
	case 1: //向上
		SnakeNode[0].y--;
		break;
	case 2: //向右
		SnakeNode[0].x++;
		break;
	case 3: //向下
		SnakeNode[0].y++;
		break;
	case 4: //向左
		SnakeNode[0].x--;
		break;
	default:
		break;
	}
        if (SnakeNode[0].x == Food.x && SnakeNode[0].y == Food.y)
        {
            count++;
            AddNode(lastX, lastY);
            PutFood();
        }
    Judge();
}

void Snake::ChangeDirector(const int & NewDirector)
{

    if (director == NewDirector || director - NewDirector == 2 ||
        director - NewDirector == -2)
	{
		return;
	}
    director = NewDirector;
}

void Snake::PutFood(void)
{
        int x, y;
        srand(time(NULL));
        while(1){
            bool flag=true;
            x = rand()%width;
            y = rand()%height;
            for (int i = 0; i < length; i++)
            {
                if (SnakeNode[i].x == x &&
                    SnakeNode[i].y == y)
                {
                    flag=false;
                    break;
                }
            }
            if(flag) break;
        }
        Food.x = x;
        Food.y = y;
}

//输出私有成员
void Snake::OutputSnake(vector<Node> & node,
                 Node & food)
{
	node.resize(SnakeNode.size());
	node = SnakeNode;
    food = Food;
}
void Snake::Clear(void)
{
	SnakeNode.clear();
	length = 0;
    AddNode(15, 15);
    AddNode(15, 16);
    AddNode(15, 17);
    director = 1;
}
