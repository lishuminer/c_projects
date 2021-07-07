#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN sizeof(struct addritem)

//����ṹ���Ա//
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

	printf("����:");
	scanf("%s", &addrinfo[count].name);
	printf("ְҵ:");
	scanf("%s", &addrinfo[count].occu);
	printf("�绰:");
	scanf("%s", &addrinfo[count].tel);
	printf("�����ʼ�:");
	scanf("%s", &addrinfo[count].email);
	printf("��ַ:");
	scanf("%s", &addrinfo[count].address);

	fwrite(&addrinfo[count], LEN, 1, fp);
	printf("¼��ɹ���");

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

	printf("����       ְҵ        �绰        �����ʼ�                    ��ַ\n");
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
	printf("������Ҫ������������");
	scanf("%s", name);
	for (i = 0; i < count; i++)
	{
		if (strcmp(addrinfo[i].name, name) == 0)
		{
			printf("����       ְҵ        �绰        �����ʼ�                    ��ַ\n");
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
	printf("������Ҫ�޸ĵ�������");
	scanf("%s", name);
	for (i = 0; i < count; i++)
	{
		if (strcmp(addrinfo[i].name, name) == 0)
		{
			printf("%-10s%-15s%-25s%-20s\n", addrinfo[i].occu, addrinfo[i].tel, addrinfo[i].email, addrinfo[i].address);
			printf("1.ְҵ    2.�绰         3.�����ʼ�         4.��ַ\n��ѡ��Ҫ�޸ĵ���Ϣ��");
			scanf("%d", &select);
			printf("�������޸ĺ����Ϣ��");
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
			printf("�޸ĳɹ����޸ĺ����ϢΪ��\n");
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
	printf("��������Ҫɾ�����û�������");
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
			printf("���û���Ϣɾ����ϡ�\n");
			break;
		}
	}
}

void menu()//���˵�����
{
	printf("0.�˳� 1.���� 2.���� 3.�޸� 4.ɾ�� 5.��ʾ\n choose(0-5):");
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