#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define WIDTH 10		//定义地图宽度 
#define HEIGHT 10		//定义地图高度 

void moveUp();			//向上移动 
void moveDown();		//向下移动 
void moveLeft();		//向左移动 
void moveRight();		//向右移动 
void initialMap();		//初始化地图 
void initialData();		//初始化数据 

int boxs = 0;		//全局变量：箱子个数
int x, y;			//全局变量：表示人的坐标 

void main()
{
	char direction;	
	initialData();
	
	while (1)
	{
		system("cls");    //清屏
		printf("=====推箱子游戏=====\n===（由w, a, s, d控制移动方向,将□推至☆）===\n");
		initialMap();
		if (!boxs)         //当箱子数为0时，break
		{
			break;
		}
		direction = _getch();
		switch (direction)    //由w, a, s, d控制移动方向
		{
		case 'w':
			moveUp();
			break;
		case 'a':
			moveLeft();
			break;
		case 's':
			moveDown();
			break;
		case 'd':
			moveRight();
			break;
		}
	}
	printf("=====游戏结束=====\n");
}

int map[WIDTH][HEIGHT] = {
		{0, 0, 0, 1, 1, 1, 0, 0, 0},
		{0, 0, 0, 1, 4, 1, 0, 0, 0},
		{1, 1, 1, 1, 0, 1, 0, 0, 0},
		{1, 0, 0, 0, 3, 1, 1, 1, 1},
		{1, 4, 0, 3, 0, 3, 0, 4, 1},
		{1, 1, 0, 0, 0, 0, 1, 1, 1},
		{0, 1, 0, 0, 0, 0, 1, 0, 0},
		{0, 1, 0, 2, 3, 0, 1, 0, 0},
		{0, 1, 0, 0, 4, 1, 1, 0, 0},
		{0, 1, 1, 1, 1, 1, 0, 0, 0}
};

void initialMap()		//初始化地图 
{
	int i, j;
	for (i = 0; i < WIDTH; i++)
	{
		for (j = 0; j < HEIGHT; j++)
		{
			switch (map[i][j])
			{
			case 0:
				printf("  ");	//0代表空地
				break;
			case 1:
				printf("■");	//1代表墙体
				break;
			case 2:
				printf("♀");	//2代表玩家(人)
				break;
			case 3:
				printf("□");	//3代表箱子
				break;
			case 4:
				printf("☆");	//4代表目的地
				break;
			case 5:
				printf("★");	//5代表已到达目的地的箱子
				break;
			case 6:
				printf("♀");	//6代表站在目的地上的人
				break;
			}
		}
		printf("\n");
	}
}

void initialData()
{
	int i, j;
	printf("游戏加载中，请稍后\n");

	//遍历地图中的数据
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			//记录人的坐标x， y
			if (map[i][j] == 2)
			{
				x = j;
				y = i;
			}
			if (map[i][j] == 3)
				boxs++;   //记录箱子的数目
		}
	}
}

void moveUp()
{

	int ux, uy;  	//定义变量存放人物上方的坐标
	if (y == 0)		//当上方没有元素时，直接return （其实人不可能在边缘）
	{
		return;
	}
	ux = x;			//记录上方坐标，x为横，y为纵，所以ux = x, uy = y - 1;
	uy = y - 1;
	if (map[uy][ux] == 0)	//如果人的前面是空地 
	{
		map[uy][ux] = 2; 	//人前方变为人 
		if (map[uy + 1][ux] == 6)    //判断初始人的位置
		{
			map[uy + 1][ux] = 4;
		}
		else
		{
			map[uy + 1][ux] = 0;
		}

	}
	if (map[uy][ux] == 1)//假设上方为墙，直接return，这个和上面的判断可以合在一起，这里为了看清楚分开写
	{
		return;
	}

	if (map[uy][ux] == 3)			//假设上方为箱子
	{
		if (map[uy - 1][ux] == 1)	//判断箱子上方是否为墙 
		{
			return;
		}
		if (map[uy - 1][ux] == 3)	//判断箱子上边是否为箱子
		{
			return;
		}
		if (map[uy - 1][ux] == 4)	//判断箱子上方是否为终点
		{
			map[uy - 1][ux] = 5;	//将箱子上面内容赋值为5★
			map[uy][ux] = 2;
			if (map[uy + 1][ux] == 6)  //判断初始人的位置
			{
				map[uy + 1][ux] = 4;
			}
			else
			{
				map[uy + 1][ux] = 0;
			}
			boxs--; 						//箱子的数目减1
		}
		else
		{
			map[uy - 1][ux] = 3;	//移动箱子
			map[uy][ux] = 2;
			if (map[uy + 1][ux] == 6)  //判断初始人的位置
			{
				map[uy + 1][ux] = 4;
			}
			else
			{
				map[uy + 1][ux] = 0;
			}
		}
	}
	if (map[uy][ux] == 4)
	{
		map[uy][ux] = 6;
		if (map[uy + 1][ux] == 6)    //判断初始人的位置
		{
			map[uy + 1][ux] = 4;
		}
		else
		{
			map[uy + 1][ux] = 0;
		}
	}

	if (map[uy][ux] == 5)			//上方为已完成的箱子
	{
		if (map[uy - 1][ux] == 4) 		//如果上方为目标 
		{
			map[uy - 1][ux] = 5;		//将上方赋值为已完成的箱子 
			map[uy][ux] = 6;		//变为被人遮盖的目标 
			if (map[uy + 1][ux] == 6)		//将原位置变空 
			{
				map[uy + 1][ux] = 4;
			}
			else
			{
				map[uy + 1][ux] = 0;
			}
		}
	}
	y = uy;		 //更新人的坐标
}

void moveDown()
{

	int dx, dy;  	//定义变量存放人物下方的坐标

	dx = x;			//记录下边坐标，x为横，y为纵，所以dx = x, dy = y + 1;
	dy = y + 1;
	if (map[dy][dx] == 0)//如果人的前面是空地 
	{
		map[dy][dx] = 2; //人前方变为人 
		if (map[dy - 1][dx] == 6)
		{
			map[dy - 1][dx] = 4;
		}
		else
		{
			map[dy - 1][dx] = 0;
		}

	}
	if (map[dy][dx] == 1)//假设下方为墙，直接return，这个和上面的判断可以合在一起，这里为了看清楚分开写
	{
		return;
	}

	if (map[dy][dx] == 3)			//假设下方为箱子
	{
		if (map[dy + 1][dx] == 1)	//判断箱子下方是否为墙 
		{
			return;
		}
		if (map[dy + 1][dx] == 3)	//判断箱子下边是否为箱子
		{
			return;
		}
		if (map[dy + 1][dx] == 4)	//判断箱子下方是否为目标 
		{
			map[dy + 1][dx] = 5;	//将箱子上面内容赋值为5★
			map[dy][dx] = 2;
			if (map[dy - 1][dx] == 6)
			{
				map[dy - 1][dx] = 4;
			}
			else
			{
				map[dy - 1][dx] = 0;
			}
			boxs--; 						//箱子的数目减1
		}
		else
		{
			map[dy + 1][dx] = 3;	//移动箱子
			map[dy][dx] = 2;
			if (map[dy - 1][dx] == 6)
			{
				map[dy - 1][dx] = 4;
			}
			else
			{
				map[dy - 1][dx] = 0;
			}
		}
	}
	if (map[dy][dx] == 4)
	{
		map[dy][dx] = 6;
		if (map[dy - 1][dx] == 6)
		{
			map[dy - 1][dx] = 4;
		}
		else
		{
			map[dy - 1][dx] = 0;
		}
	}
	if (map[dy][dx] == 5)			//上方为已完成的箱子
	{
		if (map[dy + 1][dx] == 4) 		//如果上方为目标 
		{
			map[dy + 1][dx] = 5;		//将上方赋值为已完成的箱子 
			map[dy][dx] = 6;		//变为被人遮盖的目标 
			if (map[dy - 1][dx] == 6)		//将原位置变空 
			{
				map[dy - 1][dx] = 4;
			}
			else
			{
				map[dy - 1][dx] = 0;
			}
		}
	}
	y = dy;		 //更新人的坐标
}

void moveLeft()
{

	int lx, ly;  	//定义变量存放人物上方的坐标

	lx = x - 1;			//记录上方坐标，x为横，y为纵，所以ux = x, uy = y - 1;
	ly = y;
	if (map[ly][lx] == 0)//如果人的前面是空地 
	{
		map[ly][lx] = 2; //人前方变为人 
		if (map[ly][lx + 1] == 6)
		{
			map[ly][lx + 1] = 4;
		}
		else
		{
			map[ly][lx + 1] = 0;
		}

	}
	if (map[ly][lx] == 1)//假设上方为墙，直接return，这个和上面的判断可以合在一起，这里为了看清楚分开写
	{
		return;
	}

	if (map[ly][lx] == 3)			//假设上方为箱子
	{
		if (map[ly][lx - 1] == 1)		//判断箱子左边是否为墙 
		{
			return;
		}
		if (map[ly][lx - 1] == 3)		//判断箱子左边是否为箱子
		{
			return;
		}
		if (map[ly][lx - 1] == 4)	//判断箱子左边是否为终点
		{
			map[ly][lx - 1] = 5;	//将箱子左边赋值为5★
			map[ly][lx] = 2;
			if (map[ly][lx + 1] == 6)
			{
				map[ly][lx + 1] = 4;
			}
			else
			{
				map[ly][lx + 1] = 0;
			}
			boxs--; 						//箱子的数目减1
		}
		else
		{
			map[ly][lx - 1] = 3;	//移动箱子
			map[ly][lx] = 2;
			if (map[ly][lx + 1] == 6)
			{
				map[ly][lx + 1] = 4;
			}
			else
			{
				map[ly][lx + 1] = 0;
			}
		}
	}
	if (map[ly][lx] == 4)
	{
		map[ly][lx] = 6;
		if (map[ly][lx + 1] == 6)
		{
			map[ly][lx + 1] = 4;
		}
		else
		{
			map[ly][lx + 1] = 0;
		}
	}
	if (map[ly][lx] == 5)			//上方为已完成的箱子
	{
		if (map[ly][lx - 1] == 4) 		//如果上方为目标 
		{
			map[ly][lx - 1] = 5;		//将上方赋值为已完成的箱子 
			map[ly][lx] = 6;		//变为被人遮盖的目标 
			if (map[ly][lx + 1] == 6)		//将原位置变空 
			{
				map[ly][lx + 1] = 4;
			}
			else
			{
				map[ly][lx + 1] = 0;
			}
		}
	}
	x = lx;		 //更新人的坐标
}

void moveRight()
{
	int rx, ry;  	//定义变量存放人物右边的坐标

	rx = x + 1;			//记录上方坐标，x为横，y为纵，所以rx = x+1, ry = y;
	ry = y;
	if (map[ry][rx] == 0)		//如果人的前面是空地 
	{
		map[ry][rx] = 2; 		//人前方变为人 
		if (map[ry][rx - 1] == 6)
		{
			map[ry][rx - 1] = 4;
		}
		else
		{
			map[ry][rx - 1] = 0;
		}

	}
	if (map[ry][rx] == 1)		//假设右边为墙，直接return，这个和上面的判断可以合在一起，这里为了看清楚分开写
	{
		return;
	}

	if (map[ry][rx] == 3)		//假设右边为箱子
	{
		if (map[ry][rx + 1] == 1)	//判断箱子右边是否为墙 
		{
			return;
		}
		if (map[ry][rx + 1] == 3)	//判断箱子右边是否为箱子
		{
			return;
		}
		if (map[ry][rx + 1] == 4)	//判断箱子上方是否为终点
		{
			map[ry][rx + 1] = 5;	//将箱子上面内容赋值为5★
			map[ry][rx] = 2;
			if (map[ry][rx - 1] == 6)
			{
				map[ry][rx - 1] = 4;
			}
			else
			{
				map[ry][rx - 1] = 0;
			}
			boxs--; 						//箱子的数目减1
		}
		else
		{
			map[ry][rx + 1] = 3;	//移动箱子
			map[ry][rx] = 2;
			if (map[ry][rx - 1] == 6)
			{
				map[ry][rx - 1] = 4;
			}
			else
			{
				map[ry][rx - 1] = 0;
			}
		}
	}
	if (map[ry][rx] == 4)
	{
		map[ry][rx] = 6;
		if (map[ry][rx - 1] == 6)
		{
			map[ry][rx - 1] = 4;
		}
		else
		{
			map[ry][rx - 1] = 0;
		}
	}
	if (map[ry][rx] == 5)			//上方为已完成的箱子
	{
		if (map[ry][rx + 1] == 4) 		//如果上方为目标 
		{
			map[ry][rx + 1] = 5;		//将上方赋值为已完成的箱子 
			map[ry][rx] = 6;		//变为被人遮盖的目标 
			if (map[ry][rx - 1] == 6)		//将原位置变空 
			{
				map[ry][rx - 1] = 4;
			}
			else
			{
				map[ry][rx - 1] = 0;
			}
		}
	}
	x = rx;		 //更新人的坐标
}
