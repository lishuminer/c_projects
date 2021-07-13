#include <graphics.h> //包含easyx图形库文件
#include <conio.h>
#include <stdio.h>
#include <math.h>
#define WIDTH 800
#define HEIGHT 480
#define FOOD_NUM 500
#define MAP_WIDTH (WIDTH*3)
#define MAP_HEIGHT (HEIGHT*3)
struct Ball {
	int x;
	int y;
	int r;
	bool flag;
	DWORD color;
	int      type;
} player, food[500];

void CreateFood(int i)
{
/*	food[i].x = rand() % MAP_WIDTH;
	food[i].y = rand() % MAP_HEIGHT;
	food[i].r = rand() % 5 + 1;
	food[i].flag = true;
	food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
*/
	if (food[i].flag == 1)
	{
		setfillcolor(food[i].color);
		if (food[i].type == 0)
		{
			solidellipse((int)food[i].x, (int)food[i].y, (int)(food[i].x + food[i].r), (int)(food[i].y + food[i].r));
		}
		else if (food[i].type == 1)
		{
			solidpie((int)food[i].x, (int)food[i].y, (int)(food[i].x + food[i].r), (int)(food[i].y + food[i].r), 0.0, 1.5);
		}
		else
		{
			solidcircle(int(food[i].x), int(food[i].y), int(food[i].r));
		}
	}
	else
	{
		food[i].x = (float)(rand() % MAP_WIDTH);
		food[i].y = (float)(rand() % MAP_HEIGHT);
		food[i].r = (float)(rand() % 5 + 1);
		food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);  // 随机颜色
		food[i].flag = 1;
		food[i].type = rand() % 3;
	}
}
//初始化游戏
void Gameinit() {
	//setbkcolor(WHITE);
	player.x = 400;
	player.y = 240;
	player.r = 10;
	for (int i = 0; i < FOOD_NUM; i++)
	{
		food[i].x = (float)(rand() % MAP_WIDTH);
		food[i].y = (float)(rand() % MAP_HEIGHT);
		food[i].r = (float)(rand() % 5 + 1);
		food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);  // 随机颜色
		food[i].flag = 1;
		//food[i].type = rand() % 3;
	}
	
}
float distance(Ball food, Ball player)
{
	return sqrtl((food.x - player.x)*(food.x - player.x) + (food.y - player.y)*(food.y - player.y));
}
void EatFood()
{
	for (int i = 0; i < FOOD_NUM; i++)
	{
		if (food[i].flag == 1 && distance(food[i], player) < player.r)
		{
			food[i].flag = 0;
			player.r += food[i].r/2;
			CreateFood(i);
		}
		
	}
}

//游戏动态加载
void GameDraw() {
	setbkcolor(WHITE);
	cleardevice();
	setlinecolor(RGB(230, 231, 239));
	for (int i = 0; i < MAP_WIDTH; i += 10)
	{
		line(i, 0, i, MAP_HEIGHT);
		line(0, i, MAP_WIDTH, i);
	}
	//绘制食物
	for (int i = 0; i < FOOD_NUM; i++)
	{
		setfillcolor(food[i].color);
		solidcircle(food[i].x, food[i].y, food[i].r);
	}
	//绘制玩家
	setfillcolor(RED);
	solidcircle(player.x, player.y, player.r); // 画填充圆
	SetWorkingImage();
}

void MovePlayer() {
	if (GetAsyncKeyState(VK_UP))
	{
		//player.y -= 2;
		for(int i=0;i<FOOD_NUM;i++)
			food[i].y += 2;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		//player.y += 2;
		for (int i = 0; i < FOOD_NUM; i++)
			food[i].y -= 2;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		//player.x -= 2;
		for (int i = 0; i < FOOD_NUM; i++)
			food[i].x += 2;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		//player.x += 2;
		for (int i = 0; i < FOOD_NUM; i++)
			food[i].x -= 2;
	}
		
	
}

int main()
{
	initgraph(800, 480);       // 创建绘图窗口
	Gameinit();
	BeginBatchDraw();
	while (1)
	{
		GameDraw();
		EatFood();
		FlushBatchDraw();
		MovePlayer();
		Sleep(10);
	}

	closegraph();              // 关闭绘图窗口
	return 0;
}