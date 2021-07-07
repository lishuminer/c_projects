#include <stdio.h>
void main()
{
	int i,j,flag[5]={0};
	float sum=0; 
	float price[5]={11.5,13,25,25.5,9.9};
	char dish[5][20]={"拍黄瓜","地三鲜","酸菜鱼","呛生菜","佛跳墙"};
	printf("菜单\n");
	for(i=0;i<5;i++)
	{
		printf("%5d%10s%10.1f\n",i+1,dish[i],price[i]);
	}
	while(1)
	{
		printf("点菜 or 退出(1 or 2):");
		scanf("%d",&i);
		if(i==2)
		{
			break;
		}
		else
		{
			printf("输入需点菜品:");
			scanf("%d",&j);
			if(flag[j-1]==0)
			{
				sum+=price[j-1];
				flag[j-1]=1;
			}
		}
	}
	printf("\n您的菜单：\n");
	for(i=0;i<=5;i++)
		if(flag[i-1]==1)
			printf("%5d%10s%10.1f\n",i,dish[i-1],price[i-1]);
	printf("sum=%1.1f",sum);
}
