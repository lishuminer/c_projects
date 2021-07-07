#include <stdio.h>
#include <graphics.h>
#include <mmsystem.h>
#include <time.h>

#pragma comment(lib,"WINMM.LIB")

#define WIDTH 512
#define HEIGTH 568
#define BULLET_NUM 1500

IMAGE Player;
IMAGE Bullet;
int w, h, w3, h3, b = 0;
struct Plane
{ 
	int x;
	int y;
	bool flag;

}player,bullet[BULLET_NUM];


void Gameinit(){
	w = Player.getwidth();
	h = Player.getheight();
	w3 = Bullet.getwidth();
	h3 = Bullet.getheight();
	//初始化玩家数据
	player.x = WIDTH / 2 - 35;
	player.y = HEIGTH - h;
	player.flag = true;
	for (int i = 0; i < BULLET_NUM; i++)
	{
		bullet[i].flag = false;
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

void moveBullet(int seed) {

	for (int i = 0; i < BULLET_NUM; i++)
	{
		
		if (bullet[i].flag == true)
			bullet[i].y -= seed;
	}
	
}

void GameDraw(){
	cleardevice();
	putimage(player.x, player.y, &Player);
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (bullet[i].flag == true)
			putimage(bullet[i].x, bullet[i].y, w3 / 2, h3, &Bullet, 0, 0, SRCCOPY);
	}

}

void GameControl(int seed)
{
	if(GetAsyncKeyState(VK_UP))
		player.y -= seed;
	if (GetAsyncKeyState(VK_DOWN))
		player.y += seed;
	if (GetAsyncKeyState(VK_LEFT))
		player.x -= seed;
	if (GetAsyncKeyState(VK_RIGHT))
		player.x += seed;
	
	if (GetAsyncKeyState(VK_SPACE))
	{
		Createbullet();
	}
	
	moveBullet(15);
}


int main(){
	//加载背景音乐
	//mciSendString("open Era.mp3 alias BGM", 0, 0, 0);
	//mciSendString("play BGM",0,0,0);

	initgraph(WIDTH, HEIGTH);

	loadimage(&Player, "ZIJI600X302 .jpg");
	loadimage(&Bullet, "ZIDAN_120X25.bmp");
	Gameinit();
	//BeginBatchDraw();

	while (1)
	{
		//cleardevice();
		//FlushBatchDraw();
		GameDraw();

		GameControl(2);
		Sleep(50);
	}
	
	return 0;
}
