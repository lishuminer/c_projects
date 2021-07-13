#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
#define LEN sizeof(struct addritem)//����ṹ��ĳ���//
#define FORMAT "%-10s%-10s%-15s%-25s%-30s%\n"//�����涨������ĸ�ʽ//
#define DATA addrinfo[i].name,addrinfo[i].occu,addrinfo[i].tel,addrinfo[i].email,addrinfo[i].address//����ṹ������Ԫ���еĸ�����Ա// 
//����ṹ���Ա//
struct addritem
{
	char name[10];
	char occu[10];
	char tel[15];
	char email[25];
	char address[30];
};
struct addritem addrinfo[100];//����ṹ������//
//����������Ҫ�õ��ĺ���//
void input();
void search();
void update();
void del();
void display();
void sort();
void menu();

void menu()//���˵�����//
{
	system("cls");//����cls������ս���//
	printf("\n\n\n\n\n");//���������ܲ˵���ʾλ��// 
	printf("\t\t|----------------------------------CONTACT----------------------------------------------------|\n");
	printf("\t\t|0. �˳�                                                                                      |\n");
	printf("\t\t|1. ����  ��Ϣ                                                                             |\n");
	printf("\t\t|2. ����  ��Ϣ                                                                            |\n");
	printf("\t\t|3. �޸�  ��Ϣ                                                                            |\n");
	printf("\t\t|4. ɾ��  ��Ϣ                                                                            |\n");
	printf("\t\t|5. ����                                                                                      |\n");
	printf("\t\t|6. ��ʾ                                                                                   |\n");
	printf("\t\t|---------------------------------------------------------------------------------------------|\n");
	printf("\t\t\tchoose(0-6):");
}
void main()//������//
{
	int n;
	menu();//�������˵�//
	scanf("%d", &n);//�û�ѡ����//
	while (n)//ѡ��ṹ������Ӧ�Ĺ���//
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
		menu();//�ٴε������˵�//
		scanf("%d", &n);
	}
}
void input()
{
	int i, count = 0;//����һ��ѭ�������Լ���¼ͨѶ¼����ϵ�˸����ı���//
	char ch[2];//�ַ�����������¼�û�������//
	FILE *fp;//����ָ���ļ���ָ�����//
	if ((fp = fopen("data.txt", "a+")) == NULL)//����fopen��������һ���µ��ı���������ϵ����Ϣ//
	{
		printf("can not open!\n");
		return;
	}
	while (!feof(fp))//�ж��ļ��Ƿ����//
	{
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)//ʹ��fresd�������ļ��еļ�¼������ȡ���ṹ������//
			count++;
	}
	fclose(fp);//�ر��ļ�//
	if (count == 0)//�жϵ�ǰͨѶ¼�Ƿ�Ϊ��//
		printf("No contact record!\n");
	else
	{
		system("cls");//����//
		display();//��ʾ��ϵ�˵�������Ϣ//
	}
	if ((fp = fopen("data.txt", "wb")) == NULL)//������ļ�ʧ��//
	{
		printf("can not open address list!\n");
		return;
	}
	//��������д�����//
	for (i = 0; i < count; i++)
		fwrite(&addrinfo[i], LEN, 1, fp);
	printf("������(y/n)");//��ʾ�û�����//
	scanf("%s", ch);
	while (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)//�ж��û��Ƿ���Ҫ����//
	{
		printf("����:");
		scanf("%s", &addrinfo[count].name);
		//�ж��û�����������ͨѶ¼���Ƿ����//
		for (i = 0; i < count; i++)
			if (strcmp(addrinfo[i].name, addrinfo[count].name) == 0)
			{
				printf("The name already exists,press any key to continue.");
				getch();
				fclose(fp);
				return;
			}
		printf("ְҵ:");
		scanf("%s", &addrinfo[count].occu);
		printf("�绰:");
		scanf("%s", &addrinfo[count].tel);
		printf("�����ʼ�:");
		scanf("%s", &addrinfo[count].email);
		printf("��ַ:");
		scanf("%s", &addrinfo[count].address);
		if (fwrite(&addrinfo[count], LEN, 1, fp) != 1)//���½���ϵ����Ϣ���浽����//
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
	char ch[2], name[15];//������������û���������Ϣ//
	//�򿪴��̣����������е�ͨѶ¼������ȡ���ڴ�ṹ������//
	if ((fp = fopen("data.txt", "rb")) == NULL)
	{
		printf("can not open\n");
		return;
	}
	while (!feof(fp))//�ж��Ƿ񵽴��ļ���β��//
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;//count��ֵΪͨѶ¼��Ŀ//
	fclose(fp);
	if (count == 0)
	{
		printf("no record!\n");
		return;
	}
	printf("please input the name:");
	scanf("%s", name);
	//����ͨѶ¼ָ����Ϣ�������ַ��ȽϺ���//
	for (i = 0; i < count; i++)
		if (strcmp(name, addrinfo[i].name) == 0)
		{
			printf("find the contact,display?(y/n):");
			scanf("%s", ch);
			if (strcmp(ch, "Y") == 0 || strcmp(ch, "y") == 0)
			{
				printf("����          ְҵ            �绰            �����ʼ�                   ��ַ  \t\n ");
				printf(FORMAT, DATA);
			}
			break;
		}
	//�ж�ѭ����������Ϊû���ҵ���ϵ�˻�����Ϊ�ҵ��˵���û����ʾ��ϵ����Ϣ//
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
	//�޸���ϵ����Ϣ//
	printf("please input the name of the contact which you want to update!\n");
	printf("updata name:");
	scanf("%s", &name);
	for (i = 0; i < count; i++)
	{
		if (strcmp(name, addrinfo[i].name) == 0)
		{
			printf("find the contact!you can updata!\n");
			printf("����:");
			scanf("%s", &addrinfo[i].name);
			printf("ְҵ:");
			scanf("%s", &addrinfo[i].occu);
			printf("�绰:");
			scanf("%s", &addrinfo[i].tel);
			printf("�����ʼ�:");
			scanf("%s", &addrinfo[i].email);
			printf("��ַ:");
			scanf("%s", &addrinfo[i].address);
			printf("updata succeaafully!");
			//�򿪴��̣����޸ĺ����ϵ����Ϣд�����//
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
	printf("not find the contact!\n");//û���ҵ�������ϵ����Ϣ//
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
	//ɾ����ϵ����Ϣ//
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
			//��ɾ�����ͨѶ¼д���Ӧ�Ĵ����ļ�//
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
	fp = fopen("data.txt", "rb");//�Զ�д�ķ�ʽ���ļ�//
	//��ȡ�ļ�ͨѶ¼//
	while (!feof(fp))
	{
		if (fread(&addrinfo[count], LEN, 1, fp) == 1)
			count++;
	}
	fclose(fp);//�ر��ļ�//
	printf("����       ְҵ        �绰        �����ʼ�             ��ַ\t\n");
	for (i = 0; i < count; i++)
		printf(FORMAT, DATA);
}
