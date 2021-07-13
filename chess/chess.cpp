#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int chessboard[7][7];
int flag[7][7];
int count = 0;
void init();
void showBoard();
int judge(int flag[][7]);


void main()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (i % 2 == 0 || j % 2 == 0)
				flag[i][j] = 1;
			else
				flag[i][j] = 0;
		}
	}
	init();
	printf("=====井字棋游戏=====\n");
	
	while (true)
	{
		showBoard();
	
		if (judge(flag) == 1)
		{
			printf("=====你赢了！游戏结束=====\n");
			exit(-1);
		}
		else if(judge(flag) == -1)
		{
			printf("=====你输了。游戏结束=====\n");
			exit(-1);
		}
		if (count == 9)
		{
			printf("=====平局，游戏结束=====\n");
			exit(-1);
		}
	}

}

void init()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (flag[i][j] == 1)
				printf("* ");
			else if(flag[i][j] == 0)
				printf("  ");
		}
		printf("\n");
	}
}

void showBoard()
{
	int x, y;
	count++;
	if (count % 2)
	{
		while (true)
		{
			printf("请输入你要下棋的位置坐标（1/2/3, 1/2/3）：\n");

			scanf("%d", &x);
			scanf("%d", &y);
			if (x > 3 || x < 1 || y > 3 || y < 1)
			{
				printf("超出范围，请重新输入！");
				continue;
			}
			if (x == 2)  //1,1 1,3 1,5  3,1 3,3 3,5  5,1 5,3 5,5
				x = 3;
			else if (x == 3)
				x = 5;
			if (y == 2)
				y = 3;
			else if (y == 3)
				y = 5;
			if (flag[x][y] == 0)
			{
				flag[x][y] = 2;
				break;
			}
			else
			{
				printf("该位置已有棋子，请重新输入！\n");
				continue;
			}
		}
	}
	else
	{
		int a, b;
		while (true)
		{
			a = rand() % 3 * 2 + 1;
			b = rand() % 3 * 2 + 1;
			if (flag[a][b] == 0)
			{
				flag[a][b] = 3;
				break;
			}
		}
	}
	//打印棋盘
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (flag[i][j] == 1)
				printf("* ");
			else if (flag[i][j] == 0)
				printf("  ");
			else if (flag[i][j] == 2)
				printf("X ");
			else if (flag[i][j] == 3)
				printf("O ");
		}
		printf("\n");
	}
	printf("-----------------------------------\n");
}
int judge(int flag[][7])
{
	//判断行
	for (int i = 1; i < 7; i+=2)
	{
		if (flag[i][1] == 2 && flag[i][3] == 2 && flag[i][5] == 2)
			return 1;
	}
	for (int i = 1; i < 7; i += 2)
	{
		if (flag[i][1] == 3 && flag[i][3] == 3 && flag[i][5] == 3)
			return -1;
	}
	//判断列
	for (int i = 1; i < 7; i += 2)
	{
		if (flag[1][i] == 2 && flag[3][i] == 2 && flag[5][i] == 2)
			return 1;
	}
	for (int i = 1; i < 7; i += 2)
	{
		if (flag[1][i] == 3 && flag[3][i] == 3 && flag[5][i] == 3)
			return -1;
	}
	//判断对角线
	if (flag[1][1] == 2 && flag[3][3] == 2 && flag[5][5] == 2)
		return 1;
	if (flag[5][1] == 2 && flag[3][3] == 2 && flag[1][5] == 2)
		return 1;
	if (flag[1][1] == 3 && flag[3][3] == 3 && flag[5][5] == 3)
		return -1;
	if (flag[5][1] == 3 && flag[3][3] == 3 && flag[1][5] == 3)
		return -1;
}
