#ifndef TWOSNAKE_H
#define TWOSNAKE_H

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "snake.h"
using namespace std;


class Twosnake
{
private:
    int width;
    int height;
public:
    bool die;
    vector<Node> SnakeNode1;
    vector<Node> SnakeNode2;
    Node Food;
    int direction1;
    int direction2;
    int winner;


public:
    Twosnake(int w=30,int h=30);
    bool isDie();
    void Move();
    void PutFood();
    void Judge();
    void AddNode(vector<Node>& SnakeNode, const int & w, const int & h);
    void Clear();

};

#endif // TWOSNAKE_H
