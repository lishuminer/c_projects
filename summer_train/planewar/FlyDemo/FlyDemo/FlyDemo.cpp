#include <stdio.h>
#include <graphics.h>
#include <mmsystem.h>
#include <time.h>
#include <math.h>
#pragma comment(lib,"WINMM.LIB")

#define WIDTH 512
#define HEIGHT 568
#define BULLET_NUM 1500
#define ENEMY_NUM 100

IMAGE Player;
IMAGE Bullet;
IMAGE i_enemy1;
IMAGE i_enemy2;//敌机图片
int w, h, w1, h1, w2, h2, w3, h3, t1, t2;
int enemynow = 0;
struct Plane
{
	int x;
	int y;
	bool flag;

}player, bullet[BULLET_NUM], enemy[ENEMY_NUM];


void Gameinit() {
	t1 = t2 = GetTickCount();
	w = Player.getwidth();
	h = Player.getheight();
	w1 = i_enemy1.getwidth();
	h1 = i_enemy1.getheight();
	w2 = i_enemy2.getwidth();
	h2 = i_enemy2.getheight();
	w3 = Bullet.getwidth();
	h3 = Bullet.getheight();
	//初始化玩家数据
	player.x = WIDTH / 2 - 35;
	player.y = HEIGHT - h;
	player.flag = true;
	//初始化子弹
	for (int i = 0; i < BULLET_NUM; i++)
	{
		bullet[i].flag = false;
	}
	//初始化敌机
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		enemy[i].flag = false;
	}
}

void Createbullet()
{
	for (int i = 0; i < BULLET_NUM; i++)
	{

		if (bullet[i].flag == false)
		{
			bullet[i].flag = true;
			bullet[i].x = player.x;
			bullet[i].y = player.y;
			break;
		}

	}

}

void CreateEnemy()
{
	if (enemynow == 0)
	{
		enemy[enemynow].flag = true;
		enemy[enemynow].x = rand() % WIDTH;
		enemy[enemynow].y = 0;
		enemynow++;
	}
	//上个敌机移动50后 下一个再产生
	if (enemy[enemynow - 1].y > 50 && enemy[enemynow - 1].flag == true) {

		enemy[enemynow].flag = true;
		enemy[enemynow].x = rand() % WIDTH;
		enemy[enemynow].y = 0;
		enemynow++;

	}
	for (int j = 0; j < ENEMY_NUM; j++)
	{
		enemy[j].y++;//敌机移动
	}
}

void moveBullet(int seed) {

	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bullet[i].flag == true)
			bullet[i].y -= seed;
		//回收子弹
		if (bullet[i].flag == true && bullet[i].y < -10)
			bullet[i].flag = false;
	}

}
float DISTANCE(float x1, float y1, float x2, float y2)
{
	return sqrt(((int)(x1 - y1)*(int)(x1 - y1)) + ((int)(x2 - y2)*(int)(x2 - y2)));
}
void kill()
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		for (int j = 0; j < ENEMY_NUM; j++)
		{
			if (enemy[j].flag && bullet[i].flag && DISTANCE(enemy[j].x, bullet[i].x, enemy[j].y, bullet[i].y) < 50)
			{
				bullet[i].flag = false;
				enemy[j].flag = false;
			}
		}
	}
}

void GameDraw() {
	cleardevice();
	putimage(player.x, player.y, &Player);//显示玩家
	//显示子弹
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bullet[i].flag == true)
			putimage(bullet[i].x, bullet[i].y, w3 / 2, h3, &Bullet, 0, 0, SRCCOPY);
	}
	//显示敌机
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].flag == true)
		{
			if (i % 2)
				putimage(enemy[i].x, enemy[i].y, w1 / 2, h1, &i_enemy1, w1 / 2, 0, SRCCOPY);
			else
				putimage(enemy[i].x, enemy[i].y, w2 / 2, h2, &i_enemy2, w2 / 2, 0, SRCCOPY);
		}
	}
}

void GameControl(int seed)
{
	if (GetAsyncKeyState(VK_UP))
		player.y -= seed;
	if (GetAsyncKeyState(VK_DOWN))
		player.y += seed;
	if (GetAsyncKeyState(VK_LEFT))
		player.x -= seed;
	if (GetAsyncKeyState(VK_RIGHT))
		player.x += seed;

	if (GetAsyncKeyState(VK_SPACE) && (t2 - t1) > 200)
	{
		t1 = t2;
		Createbullet();
	}
	t2 = GetTickCount();//上发子弹移动200ms后再产生下一发
	moveBullet(15);
}


int main() {
	//加载背景音乐
	//mciSendString("open Era.mp3 alias BGM", 0, 0, 0);
	//mciSendString("play BGM",0,0,0);

	initgraph(WIDTH, HEIGHT);

	loadimage(&Player, "ZIJI600X301.bmp");
	loadimage(&Bullet, "ZIDAN_120X25.bmp");
	loadimage(&i_enemy1, _T("321.bmp"));
	loadimage(&i_enemy2, _T("DIJI_100X37.bmp"));
	Gameinit();
	BeginBatchDraw();

	while (1)
	{
		//cleardevice();
		FlushBatchDraw();
		CreateEnemy();
		kill();
		GameDraw();
		GameControl(2);
		Sleep(50);
	}

	return 0;
}
