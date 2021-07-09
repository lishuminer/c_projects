#include <stdio.h>
#include <winsock.h>
#include <mysql.h>
#pragma comment (lib, "libmysql.lib")
#pragma comment (lib, "mysqlclient.lib")
int main() {
	char szTargetDSN[] = "bookdb"; char szSqlText[500] = "";

	MYSQL * myData; myData = mysql_init((MYSQL*)0);

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

		//插入信息
		/*
		if (mysql_query(myData, "insert ......")) 
		{
			if (mysql_query(myData, "insert booklog ")) 
			{
				printf("插入成功");
			}
		}
		else
		{
			printf("插入失败");
		}    */
	}
	mysql_close(myData);
	return TRUE;

}
