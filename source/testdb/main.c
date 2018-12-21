#include <stdio.h>
#include "sqlite3.h"

sqlite3 *dbaccess;

int callback(void *para,int nCount,char **cValue,char **cName)
{
    printf("nCount=%d\ncValue[0]=%s",nCount,cValue[0]);
    return SQLITE_OK;
}

int main() {
    sqlite3_open("data.db",&dbaccess);
    char *sql="select count(*) from sqlite_master where type='table' and name = 'teacherdata';",*err; // 定义sql语句和错误消息变量
    int retc=sqlite3_exec(dbaccess,sql,callback,NULL,&err); // 查询数据库
    if(retc != SQLITE_OK) // 如果查询语句执行失败
        printf("连接数据库失败。错误码：%d，错误信息：%s\n",retc,err); // 抛出错误
     return 0;
}