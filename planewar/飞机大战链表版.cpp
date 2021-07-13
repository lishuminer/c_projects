#include<graphics.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#define W 600
#define H 600
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
struct enemy
{
	int x;
	int y;
	int t;
	struct enemy *next;
};
struct plane
{
	int x;
	int y;
};
struct zidan
{
	int x;
	int y;
	struct zidan *next;
};
int r = 0;
RECT rr = { 500, 0, 600, 30 };
enum Direction
{
	up = 72, down = 80, left = 75, right = 77
}direct;
void CreatEnemy();
void createzidan();
void showenemy(struct enemy *penemy);
void moveenemy(struct enemy *penemy);
void showzidan();
void movezidan();
void destroy();
int chk();
IMAGE img1, img2, img3, img;
int w1, h1, w2, h2, h, w, h3, w3;
struct enemy *pEnemy = NULL;
struct zidan *pzidan = NULL;
struct plane* ple;
char mark[20];
int markk = 0;
void main()
{
	// 创建我方战斗机
	ple = (struct plane*)malloc(sizeof(struct plane));

	// 设置主战斗机初始坐标
	ple->x = 275;
	ple->y = 450;

	// 初始化窗口，设置宽度与高度
	initgraph(W, H);

	// 加载背景音乐
	mciSendString("play Era.mp3 repeat", 0, 0, 0);

	// 加载背景图片
	loadimage(NULL, "MAP_600X600.bmp");

	// 加载敌机图片至 img1 img2
	loadimage(&img1, _T("321.bmp"));
	loadimage(&img2, _T("DIJI_100X37.bmp"));

	// 我方战斗机图片 img
	loadimage(&img, _T("ZIJI600X300.bmp"));

	// 加载子弹图片 至img
	loadimage(&img3, _T("ZIDAN_120X25.bmp"));

	// 获取图片长宽大小
	w1 = img1.getwidth();
	h1 = img1.getheight();
	w2 = img2.getwidth();
	h2 = img2.getheight();
	w3 = img3.getwidth();
	h3 = img3.getheight();
	w = img.getwidth();
	h = img.getheight();

	// 设置字体颜色
	settextcolor(RED);

	//设置字体大小与内容
//	settextstyle(16, 0, _T("����"));

	//进入消息循环
	while (1)
	{
		// 检测是否按键		
		while (kbhit())
		{
			// 获取按键key值 (上下左右)	
			switch (getch())
			{
			case up:
				if (ple->y - 20 > 0)
					ple->y -= 20; break;
			case down:
				if (ple->y + 57 < 600)
					ple->y += 20; break;
			case right:
				if (ple->x + 95 < 600)
					ple->x += 20; break;
			case left:
				if (ple->x - 20 > 0)
					ple->x -= 20; break;
			}
		}
		// // 每 10 帧创建一架敌机
		if (r % 20 == 0)
		{
			CreatEnemy();
			moveenemy(pEnemy);
		}

		// 每 10 帧创建一颗子弹
		if (r % 10 == 0)
		{
			createzidan();
			movezidan();
		}

		// 更新帧数
		r++;

		// 初始化帧数
		if (r == 1000) {
			r = 0;
		}

		// 重新加载地图
		loadimage(NULL, "MAP_600X600.bmp");

		// 显示战斗机
		showenemy(pEnemy);

		// 设置战斗机图片放置的位置 
		putimage(ple->x, ple->y, w / 2, h, &img, w / 2, 0, SRCCOPY);

		// 显示子弹
		showzidan();

		// 在屏幕上打印分数
		drawtext(_T(mark), &rr, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		// 休眠 30 ms
		Sleep(30);

		// 销毁废弃子弹与敌机
		destroy();
	}
	system("pause");
	closegraph();
}

// 创建敌机
void CreatEnemy()
{
	struct enemy *pnew;
	pnew = (struct enemy*)malloc(sizeof(struct enemy));
	pnew->x = rand() % 550;
	pnew->y = 0;
	pnew->t = rand() % 2;
	pnew->next = NULL;
	if (pEnemy == NULL)
		pEnemy = pnew;
	else
	{
		pnew->next = pEnemy;
		pEnemy = pnew;
	}
}

// 显示敌机
void showenemy(struct enemy *penemy)
{
	struct enemy *p = penemy;
	while (p != NULL)
	{
		if (p->t == 1)
			putimage(p->x, p->y, w1 / 2, h1, &img1, w1 / 2, 0, SRCCOPY);
		else
			putimage(p->x, p->y, w2 / 2, h2, &img2, w2 / 2, 0, SRCCOPY);
		p = p->next;
	}
}

// 移动敌机
void moveenemy(struct enemy *penemy)
{
	struct enemy *p = penemy;
	while (p != NULL)
	{
		p->y = p->y + 37;
		p = p->next;
	}
}

// 创建子弹
void createzidan()
{
	struct zidan *pnew;
	pnew = (struct zidan*)malloc(sizeof(struct zidan));
	pnew->x = ple->x;
	pnew->y = ple->y - 20;
	pnew->next = NULL;
	if (pzidan == NULL)
		pzidan = pnew;
	else
	{
		pnew->next = pzidan;
		pzidan = pnew;
	}
}

// 显示子弹
void showzidan()
{
	struct zidan *q = pzidan;
	while (q != NULL)
	{
		putimage(q->x, q->y, w3 / 2, h3, &img3, 0, 0, SRCCOPY);
		q = q->next;
	}
}

// 移动子弹
void movezidan()
{
	struct zidan *p = pzidan;
	while (p != NULL)
	{
		p->y = p->y - 30;
		p = p->next;
	}
}

// 销毁子弹 (遍历子弹链表，清除坐标不在区域内的子弹)
void destroy()
{
	struct enemy *a, *b;
	struct zidan *c, *d;
	a = b = pEnemy;
	while (a != NULL)
	{
		c = d = pzidan;
		while (c != NULL)
		{
			if (c->x<(a->x + 50) && c->x>(a->x - 75) && c->y<(a->y + 37) && c->y>(a->y - 30))
			{
				d->next = c->next;
				if (c != pzidan)
					free(c);
				c = d;
				b->next = a->next;
				if (a != pEnemy)
					free(a);
				a = b;
				markk++;
				itoa(markk, mark, 10);
			}
			d = c;
			c = c->next;
		}
		b = a;
		if (a != NULL)
			a = a->next;
	}
	a = b = pEnemy;
	while (a != NULL)
	{
		if (a->y > 600)
		{
			b->next = a->next;
			if (a != pEnemy)
				free(a);
			a = b;
		}
		b = a;
		a = a->next;
	}
	c = d = pzidan;
	while (c != NULL)
	{
		if (c->y > 600)
		{
			d->next = c->next;
			if (c != pzidan)
				free(c);
			c = d;
		}
		d = c;
		c = d->next;
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
