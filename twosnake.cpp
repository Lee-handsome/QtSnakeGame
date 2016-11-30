#include "twosnake.h"

Twosnake::Twosnake(int w,int h)
{
    die = false;
    height = h;
    width = w;
    direction1 = 1;
    direction2 = 1;
    AddNode(SnakeNode1,10,h/2);
    AddNode(SnakeNode1,10,h/2+1);
    AddNode(SnakeNode1,10,h/2+2);

    AddNode(SnakeNode2,20,h/2);
    AddNode(SnakeNode2,20,h/2+1);
    AddNode(SnakeNode2,20,h/2+2);
    PutFood();
}
void Twosnake::AddNode(vector<Node>& SnakeNode,const int & w, const int & h)
{
    Node * newNode = new Node;
    newNode->x = w;
    newNode->y = h;
    SnakeNode.push_back(*newNode);
}
bool Twosnake::isDie()
{
    return die;
}
void Twosnake::Move()
{
    int length1 = SnakeNode1.size();
    int lastX = SnakeNode1[length1-1].x;
    int lastY = SnakeNode1[length1-1].y;
    for (int i = length1 - 1; i > 0; i--)
    {
        SnakeNode1[i].x = SnakeNode1[i-1].x;
        SnakeNode1[i].y = SnakeNode1[i-1].y;
    }
    switch (direction1)
    {
    case 1: //向上
        SnakeNode1[0].y--;
        break;
    case 2: //向右
        SnakeNode1[0].x++;
        break;
    case 3: //向下
        SnakeNode1[0].y++;
        break;
    case 4: //向左
        SnakeNode1[0].x--;
        break;
    default:
        break;
    }

    int length2 = SnakeNode2.size();
    int lastX2 = SnakeNode2[length2-1].x;
    int lastY2 = SnakeNode2[length2-1].y;
    for (int i = length2 - 1; i > 0; i--)
    {
        SnakeNode2[i].x = SnakeNode2[i-1].x;
        SnakeNode2[i].y = SnakeNode2[i-1].y;
    }
    switch (direction2)
    {
    case 1: //向上
        SnakeNode2[0].y--;
        break;
    case 2: //向右
        SnakeNode2[0].x++;
        break;
    case 3: //向下
        SnakeNode2[0].y++;
        break;
    case 4: //向左
        SnakeNode2[0].x--;
        break;
    default:
        break;
    }

    if (SnakeNode1[0].x == Food.x && SnakeNode1[0].y == Food.y)
    {
        //count++;
        Node * newNode = new Node;
        newNode->x=lastX;
        newNode->y=lastY;
        SnakeNode1.push_back(*newNode);
        PutFood();
    }
    if (SnakeNode2[0].x == Food.x && SnakeNode2[0].y == Food.y)
    {
        //count++;
        Node* newNode = new Node;
        newNode->x=lastX2;
        newNode->y=lastY2;
        SnakeNode2.push_back(*newNode);
        PutFood();
    }
    Judge();
}
void Twosnake::Judge()
{
    int length1 = SnakeNode1.size();
    int length2 = SnakeNode2.size();

    //蛇1 判断是否撞墙
    if (SnakeNode1[0].x < 0 || SnakeNode1[0].x == width ||
        SnakeNode1[0].y < 0 || SnakeNode1[0].y == height)
    {
        die = true;
        winner = 2;
        return;
    }
    //判断蛇是否跟自己相撞
    for (int i = 1; i < length1; i++)
    {
        if (SnakeNode1[0].x == SnakeNode1[i].x &&
            SnakeNode1[0].y == SnakeNode1[i].y)
        {
            die = true;
            winner = 2;
            return;
        }
    }
    //蛇2
    if (SnakeNode2[0].x < 0 || SnakeNode2[0].x == width ||
        SnakeNode2[0].y < 0 || SnakeNode2[0].y == height)
    {
        die = true;
        winner = 1;
        return;
    }
    //判断蛇是否跟自己相撞
    for (int i = 1; i < length2; i++)
    {
        if (SnakeNode2[0].x == SnakeNode2[i].x &&
            SnakeNode2[0].y == SnakeNode2[i].y)
        {
            die = true;
            winner = 1;
            return;
        }
    }
    //判断两蛇相撞
    for (int i = 1; i < length2; i++)
    {
        if (SnakeNode1[0].x == SnakeNode2[i].x &&
            SnakeNode1[0].y == SnakeNode2[i].y)
        {
            die = true;
            winner = 2;
            return;
        }
    }
    for (int i = 1; i < length1; i++)
    {
        if (SnakeNode2[0].x == SnakeNode1[i].x &&
            SnakeNode2[0].y == SnakeNode1[i].y)
        {
            die = true;
            winner = 1;
            return;
        }
    }
    die = false;
}

void Twosnake::PutFood()
{
    int length1 = SnakeNode1.size();
    int length2 = SnakeNode2.size();
    int x, y;
    srand(time(NULL));
    while(1){
        bool flag=true;
        x = rand()%width;
        y = rand()%height;
        for (int i = 0; i < length1; i++)
        {
            if (SnakeNode1[i].x == x &&
                SnakeNode1[i].y == y)
            {
                flag=false;
                break;
            }
        }
        for (int i = 0; i < length2; i++)
        {
            if (SnakeNode2[i].x == x &&
                SnakeNode2[i].y == y)
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
void Twosnake::Clear()
{
    SnakeNode1.clear();
    SnakeNode2.clear();
    direction1 = 1;
    direction2 = 1;
    AddNode(SnakeNode1,10,15);
    AddNode(SnakeNode1,10,16);
    AddNode(SnakeNode1,10,17);
    AddNode(SnakeNode2,20,15);
    AddNode(SnakeNode2,20,16);
    AddNode(SnakeNode2,20,17);
}
