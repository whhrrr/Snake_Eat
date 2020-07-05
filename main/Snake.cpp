#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<algorithm>
#include<ctime>
#include<graphics.h>
#include<Windows.h>
#define MAX 100
typedef struct Point//坐标组成
{
	int x;
	int y;
}MYPOINT;
//蛇的属性
struct mySnake 
{
	int num;			//蛇的节数
	MYPOINT xy[MAX];	//记录蛇的每一节的坐标
	char postion;       //蛇方向
}snake;
//食物属性
struct myFood 
{
	MYPOINT fdxy;    //食物坐标
	int flag;		 //食物是否存在标记
	int eatgrade;	 //吃掉食物能够获取的分数
}food;
//枚举类型
enum MovePostion{up = 80,down = 77,left = 75,right = 72};//定义方向
//2、过程分析
//蛇的过程
void initSnake();//初始化蛇
void drawSnake();//画蛇
void moveSnake();//移动蛇
void keyDown();  //控制蛇移动
//初始化食物
void initFood();	//初始化食物
void drawFood();	//画食物
//3、逻辑分析
//吃食物
void eatFood();		//吃食物
//蛇什么时候GameOver
bool GameOver();	//游戏结束
void gamePause();	//暂停
int main() 
{
	srand((unsigned int)time(NULL));//时间种子
	HWND hwnd = initgraph(650, 480);//窗口大小
	setbkcolor(WHITE);
	cleardevice();
	initSnake();
	while (1)
	{
		cleardevice();
		if (food.flag == 0) 
		{
			initFood();
		}
		drawFood();
		drawSnake();
		if (GameOver()) {
			break;
		}
		eatFood();
		moveSnake();
		while (_kbhit()) //kbhit按键处理？？？
		{
			gamePause();
			keyDown();

		}
		Sleep(100);
	}
	getchar();
	closegraph();
	return 0;
}

void initSnake()//初始化蛇
{
	snake.xy[2].x = 0;     //初始化三节
	snake.xy[2].y = 0;

	snake.xy[1].x = 10;
	snake.xy[1].y = 0;

	snake.xy[0].x = 20;
	snake.xy[0].y = 0;
	snake.num = 3;			//初始化蛇的节数为3
	snake.postion = right; //初始化向右走
	food.flag = 0;

}
void drawSnake()//画蛇
{
	for (int i = 0; i < snake.num; i++) 
	{
		setlinecolor(BLACK);
		setfillcolor(RGB(rand() % 255,rand() % 255, rand() % 255));
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);

	}
}
void moveSnake()//移动蛇
{
	for (int i = snake.num - 1; i > 0; i--) 
	{
		snake.xy[i].x = snake.xy[i - 1].x;
		snake.xy[i].y = snake.xy[i - 1].y;
	}
	switch(snake.postion)
	{
	case right:
		snake.xy[0].x += 10;
		break;
	case left:
		snake.xy[0].x -= 10;
		break;
	case down:
		snake.xy[0].y += 10;
		break;
	case up:
		snake.xy[0].y -= 10;
		break;
	default:
		break;
	}
}
void keyDown()//控制蛇移动
{
	char ch = '0';
	ch = _getch();
	switch(ch)//???这里switch循环不懂之后学习根据移动蛇来分析代
	{
	case right:
		if (snake.postion != down)
		{
			snake.postion = up;
		}
		break;
	case left:
		if (snake.postion != right) 
		{
			snake.postion = left; 
		}
		break;
	case down:
		if (snake.postion != left)
		{
			snake.postion = right;
		}
		break;
	case up:
		if (snake.postion != up)
		{
			snake.postion = down;
		}
		break;
	default:
		break;
	}
}
void initFood() //初始化食物
{
	food.fdxy.x = rand() % 65 * 10;
	food.fdxy.y = rand() % 48 * 10;
	food.flag = 1;
	for (int i = 0; i < snake.num; i++) 
	{
		if (food.fdxy.x == snake.xy[i].x && food.fdxy.y == snake.xy[i].y) 
		{
			food.fdxy.x = rand() % 65 * 10;
			food.fdxy.y = rand() % 48 * 10;
		}
	}
}
void drawFood() //画食物
{
	setlinecolor(BLACK);
	setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
	fillrectangle(food.fdxy.x, food.fdxy.y, food.fdxy.x + 10, food.fdxy.y + 10);
	
}
void eatFood()//吃食物
{
	if (food.fdxy.x == snake.xy[0].x && food.fdxy.y == snake.xy[0].y) 
	{
		snake.num++;
		food.eatgrade += 10;
		food.flag = 0;
	}
}
bool GameOver()//当蛇撞墙或者撞自己时游戏结束
{
	//撞墙
	if (snake.xy[0].x < 0 || snake.xy[0].y < 0 || snake.xy[0].x > 640 || snake.xy[0].y > 480)
	{
		outtextxy(320,240,TEXT("您撞墙了!"));
		MessageBox(initgraph(650, 480), TEXT("游戏结束"), TEXT("撞墙了！"), 0);
		return true;
	}
	for (int i = 1; i < snake.num; i++) 
	{
		if (snake.xy[0].x == snake.xy[i].x && snake.xy[0].y == snake.xy[i].y) 
		{
			outtextxy(320, 240, TEXT("您撞自己了!GameOver"));
			MessageBox(initgraph(650, 480), TEXT("游戏结束"), TEXT("撞自己了！"),0);
			return true;
		}
	}
	return false;
}
void gamePause() 
{
	if (_getch() == 32) 
	{
		while (_getch() != 32);
	}
}