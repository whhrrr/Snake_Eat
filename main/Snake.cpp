#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<algorithm>
#include<ctime>
#include<graphics.h>
#include<Windows.h>
#define MAX 100
typedef struct Point//�������
{
	int x;
	int y;
}MYPOINT;
//�ߵ�����
struct mySnake 
{
	int num;			//�ߵĽ���
	MYPOINT xy[MAX];	//��¼�ߵ�ÿһ�ڵ�����
	char postion;       //�߷���
}snake;
//ʳ������
struct myFood 
{
	MYPOINT fdxy;    //ʳ������
	int flag;		 //ʳ���Ƿ���ڱ��
	int eatgrade;	 //�Ե�ʳ���ܹ���ȡ�ķ���
}food;
//ö������
enum MovePostion{up = 80,down = 77,left = 75,right = 72};//���巽��
//2�����̷���
//�ߵĹ���
void initSnake();//��ʼ����
void drawSnake();//����
void moveSnake();//�ƶ���
void keyDown();  //�������ƶ�
//��ʼ��ʳ��
void initFood();	//��ʼ��ʳ��
void drawFood();	//��ʳ��
//3���߼�����
//��ʳ��
void eatFood();		//��ʳ��
//��ʲôʱ��GameOver
bool GameOver();	//��Ϸ����
void gamePause();	//��ͣ
int main() 
{
	srand((unsigned int)time(NULL));//ʱ������
	HWND hwnd = initgraph(650, 480);//���ڴ�С
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
		while (_kbhit()) //kbhit������������
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

void initSnake()//��ʼ����
{
	snake.xy[2].x = 0;     //��ʼ������
	snake.xy[2].y = 0;

	snake.xy[1].x = 10;
	snake.xy[1].y = 0;

	snake.xy[0].x = 20;
	snake.xy[0].y = 0;
	snake.num = 3;			//��ʼ���ߵĽ���Ϊ3
	snake.postion = right; //��ʼ��������
	food.flag = 0;

}
void drawSnake()//����
{
	for (int i = 0; i < snake.num; i++) 
	{
		setlinecolor(BLACK);
		setfillcolor(RGB(rand() % 255,rand() % 255, rand() % 255));
		fillrectangle(snake.xy[i].x, snake.xy[i].y, snake.xy[i].x + 10, snake.xy[i].y + 10);

	}
}
void moveSnake()//�ƶ���
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
void keyDown()//�������ƶ�
{
	char ch = '0';
	ch = _getch();
	switch(ch)//???����switchѭ������֮��ѧϰ�����ƶ�����������
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
void initFood() //��ʼ��ʳ��
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
void drawFood() //��ʳ��
{
	setlinecolor(BLACK);
	setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
	fillrectangle(food.fdxy.x, food.fdxy.y, food.fdxy.x + 10, food.fdxy.y + 10);
	
}
void eatFood()//��ʳ��
{
	if (food.fdxy.x == snake.xy[0].x && food.fdxy.y == snake.xy[0].y) 
	{
		snake.num++;
		food.eatgrade += 10;
		food.flag = 0;
	}
}
bool GameOver()//����ײǽ����ײ�Լ�ʱ��Ϸ����
{
	//ײǽ
	if (snake.xy[0].x < 0 || snake.xy[0].y < 0 || snake.xy[0].x > 640 || snake.xy[0].y > 480)
	{
		outtextxy(320,240,TEXT("��ײǽ��!"));
		MessageBox(initgraph(650, 480), TEXT("��Ϸ����"), TEXT("ײǽ�ˣ�"), 0);
		return true;
	}
	for (int i = 1; i < snake.num; i++) 
	{
		if (snake.xy[0].x == snake.xy[i].x && snake.xy[0].y == snake.xy[i].y) 
		{
			outtextxy(320, 240, TEXT("��ײ�Լ���!GameOver"));
			MessageBox(initgraph(650, 480), TEXT("��Ϸ����"), TEXT("ײ�Լ��ˣ�"),0);
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