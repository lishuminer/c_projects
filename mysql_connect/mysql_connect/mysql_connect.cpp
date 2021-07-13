#include <stdio.h>
#include<winsock.h>
#include<mysql.h>
#include <string.h>
#pragma comment (lib, "libmysql.lib")
#pragma comment (lib, "mysqlclient.lib")
int p;
void SelectBooklist(MYSQL *myData);
int addBook(MYSQL *myDatapam);
int updateBook(MYSQL *myDatapam);
int IsHaveBook(MYSQL *myData, char bid[20]);
int DeleteBook(MYSQL *myDatapam);
char r[20];
void searchBook(MYSQL *myDatapam)
{
	char bid[20];
	printf("请输入要查询的图书编号：\n");
	scanf("%s", bid);
	if (IsHaveBook(myDatapam, bid)) {
		char sql_searchbook[200];

		sprintf(sql_searchbook, "select bId,bName,bAuthor,(CASE WHEN bState=1 THEN '可借阅' ELSE '已借出' END) AS bstate from bookinfo where bId='%s';", bid);
		mysql_query(myDatapam, sql_searchbook);

		MYSQL_RES *lres = mysql_store_result(myDatapam);

		MYSQL_ROW row;
		printf("编号\t\t书名        \t\t作者\t\t状态\n");
		while (row = mysql_fetch_row(lres))
		{
			printf("%s\t\t%-10s\t\t%s\t\t%s\n", row[0], row[1], row[2], row[3]);
		}
	}
}

int main() 
{
	char szTargetDSN[] = "bookdb"; char szSqlText[500] = "";
	MYSQL * myData; myData = mysql_init((MYSQL*)0);
	//连接数据库
	if (mysql_real_connect(myData, NULL, "root", "li,pan.264614120", szTargetDSN, MYSQL_PORT, NULL, 0)) 
	{
		printf("数据库连接成功\n"); //构造SQL语句

		//设置编码格式  防止乱码
		if (mysql_query(myData, "set names gbk"))
			printf("设置编码格式失败,错误原因:%s", mysql_error(myData));

		SelectBooklist(myData);

		//定义账户和密码
		char account[20], pwd[20];
		do
		{

			printf("请输入账户和密码:\n");
			scanf("%s", account);
			scanf("%s", pwd);
			char sql_login[200];

			sprintf(sql_login, "select uFlag,uId,uName from userinfo where uAccout='%s' and Upwd='%s'", account, pwd);

			if (mysql_query(myData, sql_login)) 
				printf("登录失败");

			MYSQL_RES *res = mysql_store_result(myData);

			int num = mysql_num_rows(res);

			if (num > 0) 
			{
				printf("登录成功");
				MYSQL_ROW row = mysql_fetch_row(res);
				int userid = atoi(row[1]);

				printf("uid:%d", userid);

				if ('1' == *row[0]) 
				{
					printf("欢迎管理员登录\n");
					do
					{
						printf("请输入你的操作 1.添加图书 2.修改图书 3.删除图书 4.查询图书 5.退出\n");
						printf("请输入序号：");
						scanf("%d", &p);
						do
						{
							//添加图书
							if (p == 1) {

								if (addBook(myData)) 
								{
									printf("添加图书成功\n");
									printf("继续添加（Y\\N）");
									scanf("%s", r);
									if ((!strcmp("Y", r)) || (!strcmp("y", r))) 
										continue;									
									else
									{
										SelectBooklist(myData);
										break;
									}
								}
								else
								{
									printf("添加图书失败\n");
									printf("继续添加（Y\\N）");
									if ((!strcmp("Y", r)) || (!strcmp("y", r)))
										continue;
									else
									{
										SelectBooklist(myData);
										break;
									}
								}

							}
							//修改图书
							else if (p == 2) 
							{
								if (updateBook(myData)) 
								{
									printf("修改图书成功\n");
									printf("继续修改（Y\\N）");
									scanf("%s", r);
									if ((!strcmp("Y", r)) || (!strcmp("y", r)))
										continue;
									else
									{
										SelectBooklist(myData);
										break;
									}
								}
								else
								{
									printf("修改图书失败\n");
									printf("继续添加（Y\\N）");
									if ((!strcmp("Y", r)) || (!strcmp("y", r)))
										continue;
									else
									{
										SelectBooklist(myData);
										break;
									}
								}
							}
							//删除图书
							else if (p == 3) {
								if (DeleteBook(myData)) 
								{
									printf("删除图书成功\n");
									printf("继续删除（Y\\N）");

									scanf("%s", r);
									if ((!strcmp("Y", r)) || (!strcmp("y", r)))
										continue;
									else
									{
										SelectBooklist(myData);
										break;
									}
								}
								else
								{
									printf("删除图书失败\n");
									printf("继续删除（Y\\N）");
									if ((!strcmp("Y", r)) || (!strcmp("y", r)))
										continue;
									else
									{
										SelectBooklist(myData);
										break;
									}
								}
							}
							else if (p == 4)
							{
								searchBook(myData);
								printf("查询图书成功\n");
								printf("继续查询（Y\\N）");
								scanf("%s", r);
								if ((!strcmp("Y", r)) || (!strcmp("y", r)))
									continue;
								else
								{
									SelectBooklist(myData);
									break;
								}
							}
							else if (p == 5)
								exit(-1);
						} while (true);

					} while (true);
				}
				else
					printf("欢迎用户登录");
			}
			else
			{
				printf("用户名或者密码不正确,是否重试（Y\\N）");
				char r[20];
				scanf("%s", r);
				if ((!strcmp("Y", r)) || (!strcmp("y", r))) 
					continue;
				else
					break;
			}
		} while (true);
	}
	printf("%s\n", mysql_error(myData));
	system("pause");
	mysql_close(myData);
	return TRUE;
}

int addBook(MYSQL *myDatapam) 
{
	char bname[30], bauthor[20];
	printf("请输入书名：\n");
	scanf("%s", bname);
	printf("请输入作者：\n");
	scanf("%s", bauthor);
	char sql_insertbook[200];

	sprintf(sql_insertbook, "insert INTO bookinfo VALUES (NULL,'%s','%s',1);", bname, bauthor);

	if (!mysql_query(myDatapam, sql_insertbook)) 
		return 1;
	else
		return 0;
}


int updateBook(MYSQL *myDatapam) 
{
	char bid[20], bname[30], bauthor[20];
	printf("请输入要修改的图书编号：\n");
	scanf("%s", bid);
	if (IsHaveBook(myDatapam, bid)) {

		printf("该编号图书存在，请输入修改信息\n");
		printf("请输入书名：\n");
		scanf("%s", bname);
		printf("请输入作者：\n");
		scanf("%s", bauthor);
		char sql_updatebook[200];

		sprintf(sql_updatebook, "update bookinfo set bName='%s',bAuthor='%s' where bId='%s'", bname, bauthor, bid);

		if (!mysql_query(myDatapam, sql_updatebook)) 
			return 1;
		else
			return 0;
	}
	else
	{
		printf("该图书不存在");
		return 0;
	}
}

int DeleteBook(MYSQL *myDatapam) 
{
	char bid[20];
	printf("请输入要删除的数据编号：\n");
	scanf("%s", bid);
	if (IsHaveBook(myDatapam, bid)) {

		printf("该编号图书存在，是否确定删除(Y|N)\n");
		char r[20];
		scanf("%s", r);
		if ((!strcmp("Y", r)) || (!strcmp("y", r))) 
		{
			char sql_deletebook[200];

			sprintf(sql_deletebook, "delete from bookinfo where bId='%s'", bid);

			if (!mysql_query(myDatapam, sql_deletebook)) 
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else
	{
		printf("该图书不存在");
		return 0;
	}
}

void SelectBooklist(MYSQL *myData) {

	mysql_query(myData, "select bId,bName,bAuthor,(CASE WHEN bState=1 THEN '可借阅' ELSE '已借出' END) AS 	bstate from bookinfo");

	//获得结果集
	MYSQL_RES *lres = mysql_store_result(myData);

	MYSQL_ROW row;
	printf("编号\t\t书名        \t\t作者\t\t状态\n");
	while (row = mysql_fetch_row(lres))
	{
		printf("%s\t\t%-10s\t\t%s\t\t%s\n", row[0], row[1], row[2], row[3]);
	}
	printf("\n");
}

int IsHaveBook(MYSQL *myData, char bid[20]) {
	char sql_ishavebook[200];

	sprintf(sql_ishavebook, "select bId from bookinfo where bid='%s'", bid);

	mysql_query(myData, sql_ishavebook);
	MYSQL_RES *res = mysql_store_result(myData);

	int num = mysql_num_rows(res);

	if (num > 0) 
		return 1;
	else
		return 0;
}