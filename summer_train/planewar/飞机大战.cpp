/*#include <stdio.h>
#include <graphics.h>
#include <mmsystem.h>
#pragma comment(lib,"WINMM.LIB")
#define WIDTH 480
#define HEIGTH 720


IMAGE Player;
IMAGE Bulletimg;
IMAGE Enemy;
IMAGE Background;

int w, h,w1,h1,w2,h2;
struct Plane
{
	int x;
	int y;
	bool flag;
}player,bullet[15];


void Gameinit() 
{
	w = Player.getwidth();
	h = Player.getheight();
	w1 = Bulletimg.getwidth();
	h1= Bulletimg.getheight();
	w2 = Enemy.getwidth();
	h2 = Enemy.getheight();
	//初始化玩家数据
	player.x = WIDTH / 2;
	player.y = HEIGTH - h;
	player.flag = true;

	for (int i = 0; i < 15; i++)
	{
		bullet[i].flag = false;
	}
}

void CreateBullet()
{
	for (int i = 0; i < 15; i++)
		if (bullet[i].flag == false)
		{
			bullet[i].flag = true;
			bullet[i].x = player.x;
			bullet[i].y = player.y;	
		}
}

void MoveBullet(int seed)
{
	for (int i = 0; i < 15; i++) 
	{
		if (bullet[i].flag == true)
			bullet[i].y -= seed;
	}
}

void GameDraw() 
{
	cleardevice();
	putimage(0, 0, &Background);
	putimage(player.x, player.y, &Player);
	//putimage(player.x, player.y, &Enemy);

	for (int i = 0; i < 15; i++)
		if (bullet[i].flag == true)
			putimage(bullet[i].x, bullet[i].y, w1/2 , h1 , &Bulletimg, 0, 0, SRCCOPY);

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
	if (GetAsyncKeyState(VK_SPACE))
		CreateBullet();
	MoveBullet(15);
}

int main() {
	//加载背景音乐
	mciSendString("open C400003292ef1doWUt.m4a alias BGM", 0, 0, 0);
	mciSendString("play BGM",0,0,0);

	initgraph(WIDTH, HEIGTH);

	loadimage(&Player, "ZIJI600X302 .jpg");
	loadimage(&Bulletimg, "ZIDAN_120X25.bmp");
	loadimage(&Enemy, "DIJI_100X37.bmp");
	loadimage(&Background, "img_bg_level_5.jpg");
	putimage(player.x, player.y, &Player);

	Gameinit();
	BeginBatchDraw();
	while(1)
	{
		FlushBatchDraw();
		GameDraw();
		GameControl(5);
		Sleep(50);
	}


	return 0;
}*/
#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<graphics.h>

#define WIDTH 10//定义二维数组宽度
#define HIGTH 14//定义二维数组高度

struct Bullet//子弹结构体
{
	int x;
	int y;
};
struct Enemy//敌机结构体
{
	int x;
	int y;
};
struct Bullet bullet[1000];//最多可同时发射1000枚子弹
struct Enemy enemy[5];//同时出现5个敌机

int map[HIGTH][WIDTH];//定义游戏地图二维数组，14行10列
int fly_x, fly_y;//表示飞机的x,y坐标
int num_bullet = 0;//用来表示发射的子弹个数
int speed = 0;//控制敌机降落速度

IMAGE i_bullet, i_hit, i_fly, i_enemy;//图片变量，用来保存子弹、飞机、敌机等图片


void show()
{
	putimage(fly_x * 50, fly_y * 50, &i_fly);//在画面上显示飞机图片
	for (int i = 0; i < 5; i++)
		putimage(enemy[i].x * 50, enemy[i].y * 50, &i_enemy);//在画面上显示敌机图片
	for (int i = 0; i < num_bullet; i++)
		putimage(bullet[i].x * 50, bullet[i].y * 50, &i_bullet);//在画面上显示子弹图片
}


void init()
{
	//初始化二维数组，全部置为0
	for (int i = 0; i < HIGTH; i++)
		for (int j = 0; j < WIDTH; j++)
			map[i][j] = 0;

	fly_x = WIDTH / 2;//初始化飞机x坐标，在二维数组的第5列
	fly_y = HIGTH - 1;//初始化飞机y坐标，在二维数组的第13行
	map[fly_y][fly_x] = 1;//飞机位置，用1表示飞机

	for (int i = 0; i < 5; i++)
	{
		enemy[i].x = rand() % WIDTH;//初始化敌机x坐标，值在0-9范围内
		enemy[i].y = rand() % 6;//初始化敌机y坐标，值在0-5范围内
		map[enemy[i].y][enemy[i].x] = 2;//敌机位置，用2表示敌机
	}
	show();
}

void beginLoad()
{
	loadimage(&i_bullet, _T("hero_bullet_7.jpg"), 20, 20);  //加载热狗的图片
	loadimage(&i_hit, _T("bomb-2.jpg"), 50, 50);//加载王校长吃热狗的图片
	loadimage(&i_fly, _T("v2-deaea3a224d6724c507f53019aeeeae9_720w.jpg"), 50, 50);//加载飞机的图片
	loadimage(&i_enemy, _T("img-plane_2.jpg"), 50, 50);//加载王校长的图片
}

void control()
{
	map[fly_y][fly_x] = 0;//修改飞机坐标前，先将原位置清零
	char input;
	if (kbhit())
	{
		input = getch();
		switch (input)
		{
		case 'w':fly_y--; break;
		case 's':fly_y++; break;
		case 'a':fly_x--; break;
		case 'd':fly_x++; break;
		case ' ':
		{
			bullet[num_bullet].x = fly_x;			//子弹的x坐标与飞机的x坐标相同
			bullet[num_bullet].y = fly_y - 1;		//子弹的y坐标等于飞机的y坐标减一
			num_bullet++;							//飞机每发射一枚子弹，num_bullet加1
		}
		break;
		default: break;
		}
	}
	map[fly_y][fly_x] = 1;							//修改飞机坐标后，将新位置置为1
}


void update()
{
	if (speed % 7 == 0)								//speed加7次，敌机才降落一步
	{
		for (int i = 0; i < 5; i++)					//依次循环每个敌机
		{
			map[enemy[i].y][enemy[i].x] = 0;		//修改敌机坐标前，先将原位置清零
			enemy[i].y++;							//敌机的y坐标加一
			if (enemy[i].y > HIGTH - 1)				//如果敌机飞到最下面
			{
				enemy[i].y = 0;						//将敌机重新移动到第一排
				enemy[i].x = rand() % WIDTH;		//在0-9的范围内随机生成x坐标
			}
			map[enemy[i].y][enemy[i].x] = 2;		//修改飞机坐标后，将新位置置为2
		}
	}
	speed++;
	for (int i = 0; i < num_bullet; i++)			//依次循环每颗子弹
	{
		map[bullet[i].y][bullet[i].x] = 0;			//修改子弹坐标前，先将原位置清零			
		bullet[i].y--;								//子弹坐标减一
													//如果子弹飞出画面或击中敌机
		if (bullet[i].y < 0)
		{
													//将后面的子弹在数组中依次前移一位
			for (int j = i; j < num_bullet - 1; j++)
			{
				bullet[j].x = bullet[j + 1].x;
				bullet[j].y = bullet[j + 1].y;
			}
			num_bullet--;							//删除数组中最后一位
		}
		map[bullet[i].y][bullet[i].x] = 3;			//修改子弹坐标后，将新位置置为3
	}
}


void ishit()
{
	for (int i = 0; i < num_bullet; i++)			//检测子弹是否击中敌机
	{
		for (int j = 0; j < 5; j++)
		{
			if ((bullet[i].x == enemy[j].x&&bullet[i].y == enemy[j].y) || (bullet[i].x == enemy[j].x&&bullet[i].y == enemy[j].y + 1))
			{
				map[enemy[j].y][enemy[j].x] = 0;						//敌机在地图上消失
				map[bullet[i].y][bullet[i].x] = 0;						//子弹在地图上消失
				putimage(enemy[j].x * 50, enemy[j].y * 50, &i_hit);		//在画面上显示爆炸图片
				Sleep(50);												//暂停0.05s
																		//重新生成一个新的敌机的x,y坐标
				enemy[j].y = 0;											//敌机y坐标为地图第一排
				enemy[j].x = rand() % WIDTH;							//在0-9的范围内随机生成x坐标
				bullet[i].y = 0;			//将击中敌机子弹的y坐标置为0，执行control()函数后，将在数组中删除此子弹
			}
		}
	}
	for (int i = 0; i < 5; i++)				//检测敌机是否撞上我方飞机
	{
		if (enemy[i].x == fly_x && enemy[i].y == fly_y)
		{
			//system("pause");	//暂停游戏
			exit(0);			//退出游戏
		}
	}
}


int main()
{
	beginLoad();			//加载图片函数   
	initgraph(500, 700);
	setbkcolor(WHITE);		//设置背景为白色
	init();					//初始化函数
	while (1)				//无限循环
	{
		cleardevice();		//清屏函数
		ishit();			//检测碰撞函数
		control();			//键盘控制函数
		update();			//更新子弹及敌机函数
		show();				//显示界面函数	
		Sleep(100);
	}
	return 0;
}