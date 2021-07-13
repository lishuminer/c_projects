#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN sizeof(struct addritem)

//定义结构体成员//
struct addritem
{
	char name[10];
	char occu[10];
	char tel[15];
	char email[25];
	char address[20];
};

struct addritem addrinfo[100];

void input() {
	int count = 0;
	FILE *fp;
	fp = fopen("data.txt", "a+");

	printf("姓名:");
	scanf("%s", &addrinfo[count].name);
	printf("职业:");
	scanf("%s", &addrinfo[count].occu);
	printf("电话:");
	scanf("%s", &addrinfo[count].tel);
	printf("电子邮件:");
	scanf("%s", &addrinfo[count].email);
	printf("地址:");
	scanf("%s", &addrinfo[count].address);

	fwrite(&addrinfo[count], LEN, 1, fp);
	printf("录入成功！");

	system("pause");
	fclose(fp);
}

void display()
{
	FILE *fp;
	int i, count = 0;
	fp = fopen("data.txt", "rt+");

	while (!feof(fp))
	{
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	}

	printf("姓名       职业        电话        电子邮件                    地址\n");
	for (i = 0; i < count; i++)
		printf("%-10s%-10s%-15s%-25s%-20s\n", addrinfo[i].name, addrinfo[i].occu, addrinfo[i].tel, addrinfo[i].email, addrinfo[i].address);

	fclose(fp);
}

void search()
{
	FILE *fp;
	int i, count = 0;
	fp = fopen("data.txt", "rt+");

	while (!feof(fp))
	{
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	}
	char name[10];
	printf("请输入要搜索的姓名：");
	scanf("%s", name);
	for (i = 0; i < count; i++)
	{
		if (strcmp(addrinfo[i].name, name) == 0)
		{
			printf("姓名       职业        电话        电子邮件                    地址\n");
			printf("%-10s%-10s%-15s%-25s%-20s\n", addrinfo[i].name, addrinfo[i].occu, addrinfo[i].tel, addrinfo[i].email, addrinfo[i].address);
			break;
		}
	}

	fclose(fp);
}

void modify()
{
	FILE *fp;
	int i, count = 0;
	fp = fopen("data.txt", "rt+");

	while (!feof(fp))
	{
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	}
	char name[10];
	int select;
	char temp[20];
	printf("请输入要修改的姓名：");
	scanf("%s", name);
	for (i = 0; i < count; i++)
	{
		if (strcmp(addrinfo[i].name, name) == 0)
		{
			printf("%-10s%-15s%-25s%-20s\n", addrinfo[i].occu, addrinfo[i].tel, addrinfo[i].email, addrinfo[i].address);
			printf("1.职业    2.电话         3.电子邮件         4.地址\n请选择要修改的信息：");
			scanf("%d", &select);
			printf("请输入修改后的信息：");
			switch (select)
			{
			case 1:
				scanf("%s", temp);
				strcpy(addrinfo[i].occu, temp);

				break;
			case 2:
				scanf("%s", temp);
				strcpy(addrinfo[i].tel, temp);

				break;
			case 3:
				scanf("%s", temp);
				strcpy(addrinfo[i].email, temp);
				break;
			case 4:
				scanf("%s", temp);
				strcpy(addrinfo[i].address, temp);
				break;
			}
			printf("修改成功！修改后的信息为：\n");
			printf("%-10s%-10s%-15s%-25s%-20s\n", addrinfo[i].name, addrinfo[i].occu, addrinfo[i].tel, addrinfo[i].email, addrinfo[i].address);
			fclose(fp);
			FILE *fq;
			fq = fopen("data.txt", "wt+");
			int m = 0;
			while (m < count)
			{
				fwrite(&addrinfo[m++], LEN, 1, fq);
			}
			fclose(fq);
			break;
		}
	}

}

void del()
{
	char namedele[10];
	printf("输入你想要删除的用户姓名：");
	scanf("%s", &namedele);
	int count = 0, i, j;
	FILE *fp;
	fp = fopen("data.txt", "rt+");
	while (!feof(fp))
	{
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	}
	for (j = 0; j < count; j++)
	{
		if (strcmp(addrinfo[j].name, namedele) == 0)
		{
			for (i = j; i < count - 1; i++)
			{
				strcpy(addrinfo[i].name, addrinfo[i + 1].name);
				strcpy(addrinfo[i].occu, addrinfo[i + 1].occu);
				strcpy(addrinfo[i].tel, addrinfo[i + 1].tel);
				strcpy(addrinfo[i].address, addrinfo[i + 1].address);
			}
			fclose(fp);
			FILE *fq;
			fq = fopen("data.txt", "wt+");
			int m = 0;
			while (m < count - 1)
			{
				fwrite(&addrinfo[m++], LEN, 1, fq);
			}
			fclose(fq);
			printf("该用户信息删除完毕。\n");
			break;
		}
	}
}

void menu()//主菜单函数
{
	printf("0.退出 1.输入 2.搜索 3.修改 4.删除 5.显示\n choose(0-5):");
}

int main() {

	menu();
	int n;

	scanf("%d", &n);
	while (n)
	{
		switch (n)
		{
		case 1:
			input();
			break;
		case 2:
			search();
			break;
		case 3:
			modify();
			break;
		case 4:
			del();
			break;
		case 5:
			display();
			break;

		default:
			break;
		}
		menu();
		scanf("%d", &n);
	}
	system("pause");
	return 0;

}