#include <stdio.h>
#include <winsock.h>
#include <mysql.h>
#pragma comment (lib, "libmysql.lib")
#pragma comment (lib, "mysqlclient.lib")
int p;
int addbook(MYSQL *myDatapam)
{
	//添加图书的方法
	char bname[30], bauthor[20];
	printf("请输入书名：\n");
	scanf("%s", bname);
	printf("请输入作者：\n");
	scanf("%s", bauthor);
	char sql_insertbook[200];

	sprintf(sql_insertbook, "insert INTO bookinfo VALUES (NULL,'%s','%s',1);", bname, bauthor);
	if (mysql_query(myDatapam, sql_insertbook))
		return 0;
	else
		return 1;
}
int modifybook(MYSQL *myDatapam)
{
	//修改图书的方法
	char bname[30];
	char n_bname[30];
	char n_bauthor[30];
	char n_bstate[30];
	char sql_modifybook[200];
	int i;
	printf("请输入书名：\n");
	scanf("%s", bname);
	printf("1.书名 2.作者 3.借出状态\n请输入要修改的选项：");
	scanf("%d", &i);
	if (i == 1)
	{
		printf("请输入修改后的书名：\n");
		scanf("%s", n_bname);
		sprintf(sql_modifybook, "update bookinfo set bName='%s' where bName='%s'", n_bname,bname);
	}
	else if(i == 2)
	{
		printf("请输入修改后的作者：\n");
		scanf("%s", n_bauthor);
		sprintf(sql_modifybook, "update bookinfo set bAuthor='%s' where bName='%s'", n_bauthor, bname);
	}
	else if (i == 3)
	{
		printf("请输入修改后的状态(0:已借出 1:可借阅)：\n");
		scanf("%s", n_bstate);
		sprintf(sql_modifybook, "update bookinfo set bState='%s' where bName='%s'", n_bstate, bname);
	}

	if (mysql_query(myDatapam, sql_modifybook))
		return 0;
	else
		return 1;
}
int deletebook(MYSQL *myDatapam)
{
	//删除图书的方法
	char bname[30];
	printf("请输入书名：\n");
	scanf("%s", bname);
	char sql_deletebook[200];
	sprintf(sql_deletebook, "delete from bookinfo where bName='%s';", bname);
	if (mysql_query(myDatapam, sql_deletebook))
		return 0;
	else
		return 1;
}


int main() 
{
	char szTargetDSN[] = "bookdb"; //是数据库的名称！！！
	char szSqlText[500] = "";

	MYSQL *myData; 
	myData = mysql_init((MYSQL*)0);

	//连接数据库

	if (mysql_real_connect(myData, NULL, "root", "li,pan.264614120", szTargetDSN, MYSQL_PORT, NULL, 0)) {
		printf("数据库连接成功！\n"); //构造SQL语句

		//设置编码格式 防止乱码
		if (mysql_query(myData, "set names gbk"))
		{
			printf("设置编码格式失败,错误原因:%s", mysql_error(myData));
		}

		mysql_query(myData, "select bId,bName,bAuthor,(CASE WHEN bState=1 THEN '可借阅' ELSE '已借出' END) AS bstate from bookinfo");
		//获得结果集
		MYSQL_RES *lres = mysql_store_result(myData);
		MYSQL_ROW row;
		printf("编号\t\t书名       \t\t作者\t\t状态\n");
		while (row = mysql_fetch_row(lres))
		{
			printf("%s\t\t%-10s\t\t%s\t\t%s\n", row[0], row[1], row[2], row[3]);
		}

		//定义账号和密码
		char account[20], pwd[20];
		printf("请输入账号和密码：");
		scanf("%s", account);
		scanf("%s", pwd);
		
		char sql_login[200];
		sprintf(sql_login, "select uFlag,uId,uName from userinfo where uAccout='%s' and uPwd='%s'", account, pwd);
		if (mysql_query(myData, sql_login))
			printf("登录失败\n");
		
		MYSQL_RES *res = mysql_store_result(myData);
		int num = mysql_num_rows(res);
		if (num > 0)
		{
			printf("登陆成功\n");
			MYSQL_ROW row = mysql_fetch_row(res);
			int userid = atoi(row[1]);
			printf("uid:%d", userid);
			if ('1'==*row[0])
			{
				printf("欢迎管理员登录\n");
				do
				{
					printf("你的操作 1.添加图书 2.修改图书 3.删除图书\n请输入序号：");
					scanf("%d", &p);
					if (p == 1)
					{
						if (addbook(myData))
							printf("添加成功\n");
						else
							printf("添加图书失败\n");
					}
					else if (p == 2)
					{
						if (modifybook(myData))
							printf("修改成功\n");
						else
							printf("修改图书失败\n");
					}
					else if (p == 3)
					{
						if (deletebook(myData))
							printf("删除成功\n");
						else
							printf("删除图书失败\n");
					}
					
				} while (true);
			}
			else
			{
				printf("欢迎用户登录\n");
			}
		}
		else
			printf("用户名或者密码不正确");

	}
	mysql_close(myData);
	return TRUE;

}
