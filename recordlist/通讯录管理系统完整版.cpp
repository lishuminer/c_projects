#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#define LEN sizeof(struct addritem)//定义结构体的长度//
#define FORMAT "%-10s%-10s%-15s%-25s%-30s%\n"//这个宏规定了输出的格式//
#define DATA addrinfo[i].name,addrinfo[i].occu,addrinfo[i].tel,addrinfo[i].email,addrinfo[i].address//代表结构体数组元素中的各个成员// 
//定义结构体成员//
struct addritem
{
	char name[10];
	char occu[10];
	char tel[15];
	char email[25];
	char address[30];
};
struct addritem addrinfo[100];//定义结构体数组//
//声明程序中要用到的函数//
void input();
void search();
void update();
void del();
void display();
void sort();
void menu();

void menu()//主菜单函数//
{
	system("cls");//调用cls函数清空界面//
	printf("\n\n\n\n\n");//控制主功能菜单显示位置// 
	printf("\t\t|----------------------------------CONTACT----------------------------------------------------|\n");
	printf("\t\t|0. 退出                                                                                      |\n");
	printf("\t\t|1. 输入  信息                                                                             |\n");
	printf("\t\t|2. 搜索  信息                                                                            |\n");
	printf("\t\t|3. 修改  信息                                                                            |\n");
	printf("\t\t|4. 删除  信息                                                                            |\n");
	printf("\t\t|5. 排序                                                                                      |\n");
	printf("\t\t|6. 显示                                                                                   |\n");
	printf("\t\t|---------------------------------------------------------------------------------------------|\n");
	printf("\t\t\tchoose(0-6):");
}
void main()//主函数//
{
	int n;
	menu();//调用主菜单//
	scanf("%d", &n);//用户选择功能//
	while (n)//选择结构进入相应的功能//
	{
		switch (n)
		{
		case 1: input();  break;
		case 2: search(); break;
		case 3: update(); break;
		case 4: del();    break;
		case 5: sort();   break;
		case 6: display(); break;
		default: break;
		}
		getch();
		menu();//再次调用主菜单//
		scanf("%d", &n);
	}
}
void input()
{
	int i, count = 0;//定义一个循环变量以及记录通讯录中联系人个数的变量//
	char ch[2];//字符数组用来记录用户的输入//
	FILE *fp;//定义指向文件的指针变量//
	if ((fp = fopen("data.txt", "a+")) == NULL)//调用fopen函数创建一个新的文本来保存联系人信息//
	{
		printf("can not open!\n");
		return;
	}
	while (!feof(fp))//判断文件是否结束//
	{
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)//使用fresd函数将文件中的记录逐条读取到结构体数组//
			count++;
	}
	fclose(fp);//关闭文件//
	if (count == 0)//判断当前通讯录是否为空//
		printf("No contact record!\n");
	else
	{
		system("cls");//清屏//
		display();//显示联系人的所有信息//
	}
	if ((fp = fopen("data.txt", "wb")) == NULL)//如果打开文件失败//
	{
		printf("can not open address list!\n");
		return;
	}
	//将数据重写入磁盘//
	for (i = 0; i < count; i++)
		fwrite(&addrinfo[i], LEN, 1, fp);
	printf("请输入(y/n)");//提示用户输入//
	scanf("%s", ch);
	while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)//判断用户是否需要输入//
	{
		printf("姓名:");
		scanf("%s", &addrinfo[count].name);
		//判断用户输入姓名在通讯录中是否存在//
		for (i = 0; i < count; i++)
			if (strcmp(addrinfo[i].name, addrinfo[count].name) == 0)
			{
				printf("The name already exists,press any key to continue.");
				getch();
				fclose(fp);
				return;
			}
		printf("职业:");
		scanf("%s", &addrinfo[count].occu);
		printf("电话:");
		scanf("%s", &addrinfo[count].tel);
		printf("电子邮件:");
		scanf("%s", &addrinfo[count].email);
		printf("地址:");
		scanf("%s", &addrinfo[count].address);
		if (fwrite(&addrinfo[count], LEN, 1, fp) != 1)//将新建联系人信息保存到磁盘//
		{
			printf("can not save the record!");
			getch();
		}
		else
		{
			printf("%s saved!\n", addrinfo[count].name);
			count++;
		}
		printf("continue?(y/n):");
		scanf("%s", ch);
	}
	fclose(fp);
	printf("OK!\n");
}
void search()
{
	FILE *fp;
	int i, count = 0;
	char ch[2], name[15];//定义数组接收用户的输入信息//
	//打开磁盘，并将磁盘中的通讯录逐条读取到内存结构体数组//
	if ((fp = fopen("data.txt", "rb")) == NULL)
	{
		printf("can not open\n");
		return;
	}
	while (!feof(fp))//判断是否到达文件的尾部//
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;//count终值为通讯录条目//
	fclose(fp);
	if (count == 0)
	{
		printf("no record!\n");
		return;
	}
	printf("please input the name:");
	scanf("%s", name);
	//查找通讯录指定信息，运用字符比较函数//
	for (i = 0; i < count; i++)
		if (strcmp(name, addrinfo[i].name) == 0)
		{
			printf("find the contact,display?(y/n):");
			scanf("%s", ch);
			if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
			{
				printf("姓名          职业            电话            电子邮件                   地址  \t\n ");
				printf(FORMAT, DATA);
			}
			break;
		}
	//判断循环结束是因为没有找到联系人还是因为找到了但是没有显示联系人信息//
	if (i == count)
		printf("can not find the contact!\n");
}
void update()
{
	FILE* fp;
	int i, j, count = 0;
	char name[15];
	if ((fp = fopen("data.txt", "r+")) == NULL)
	{
		printf("can not open!\n");
		return;
	}
	while (!feof(fp))
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	if (count == 0)
	{
		printf("no record!\n");
		fclose(fp);
		return;
	}
	display();
	//修改联系人信息//
	printf("please input the name of the contact which you want to update!\n");
	printf("updata name:");
	scanf("%s", &name);
	for (i = 0; i < count; i++)
	{
		if (strcmp(name, addrinfo[i].name) == 0)
		{
			printf("find the contact!you can updata!\n");
			printf("姓名:");
			scanf("%s", &addrinfo[i].name);
			printf("职业:");
			scanf("%s", &addrinfo[i].occu);
			printf("电话:");
			scanf("%s", &addrinfo[i].tel);
			printf("电子邮件:");
			scanf("%s", &addrinfo[i].email);
			printf("地址:");
			scanf("%s", &addrinfo[i].address);
			printf("updata succeaafully!");
			//打开磁盘，将修改后的联系人信息写入磁盘//
			if ((fp = fopen("data.txt", "wb")) == NULL)
			{
				printf("can not open!\n");
				return;
			}
			for (j = 0; j < count; j++)
				if (fwrite(&addrinfo[j], LEN, 1, fp) != 1)
				{
					printf("can not save!");
					getch();
				}
			fclose(fp);
			return;
		}
	}
	printf("not find the contact!\n");//没有找到该条联系人信息//
}
void del()
{
	FILE* fp;
	int i, j, count = 0;
	char ch[2];
	char name[15];
	if ((fp = fopen("data.txt", "r+")) == NULL)
	{
		printf("can not open!\n");
		return;
	}
	while (!feof(fp))
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	fclose(fp);
	if (count == 0)
	{
		printf("no record!\n");
		return;
	}
	display();
	//删除联系人信息//
	printf("please input the name:");
	scanf("%s", &name);
	for (i = 0; i < count; i++)
	{
		if (strcmp(name, addrinfo[i].name) == 0)
		{
			printf("find the contact,del?(y/n)");
			scanf("%s", ch);
			if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
				for (j = i; j < count; j++)
					addrinfo[j] = addrinfo[j + 1];
			count--;
			//将删除后的通讯录写入对应的磁盘文件//
			if ((fp = fopen("data.txt", "wb")) == NULL)
			{
				printf("can not open!\n");
				return;
			}
			for (j = 0; j < count; j++)
				if (fwrite(&addrinfo[j], LEN, 1, fp) != 1)
				{
					printf("can not save!\n");
					getch();
				}
			fclose(fp);
			printf("del succesfully!\n");
			return;
		}
	}
	printf("not find the contact!\n");
}
void sort()
{
	FILE* fp;
	struct addritem t;
	int i = 0, j = 0, count = 0;
	if ((fp = fopen("data.txt", "r+")) == NULL)
	{
		printf("can not open!\n");
		return;
	}
	while (!feof(fp))
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	fclose(fp);
	if (count == 0)
	{
		printf("no record!\n");
		return;
	}
	for (i = 0; i < count - 1; i++)
		for (j = i + 1; j < count; j++)
			if (strcmp(addrinfo[i].name, addrinfo[j].name) > 0)
			{
				t = addrinfo[i];
				addrinfo[i] = addrinfo[j];
				addrinfo[j] = t;
			}
	if ((fp = fopen("data.txt", "wb")) == NULL)
	{
		printf("can not open!\n");
		return;
	}
	for (i = 0; i < count; i++)
		if (fwrite(&addrinfo[i], LEN, 1, fp) != 1)
		{
			printf("can not save!\n");
			getch();
		}
	fclose(fp);
	printf("save successfully!\n");
}
void display()
{
	FILE* fp;
	int i, count = 0;
	fp = fopen("data.txt", "rb");//以读写的方式打开文件//
	//读取文件通讯录//
	while (!feof(fp))
	{
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	}
	fclose(fp);//关闭文件//
	printf("姓名       职业        电话        电子邮件             地址\t\n");
	for (i = 0; i < count; i++)
		printf(FORMAT, DATA);
}
