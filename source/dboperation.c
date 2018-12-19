#include "includeheaders.h"
#include "sqlite3.h"

void checkFileProi();
sqlite3* connectDB();
int isTableExistCallback(void *,int nCount,char **cValue,char **cName);

void checkFileProi()
{
    if(!access("data.db",0)) // 是否存在
    {
        if(access("data.db",6)) // 是否可读写,不可读写直接退出。
            {
                printf("数据库文件无法读写，请检查是否有程序占用数据文件，并在占用解除后重启本程序。\n");
                system("pause");
                exit(0);
            }
    }
    else // 不存在则开始新建
    {
        printf("数据库文件丢失，3秒后新建。\n");
        Sleep(3000); // 等待三秒
        sqlite3 *teacherdb;
        sqlite3_open("data.db",&teacherdb);
        sqlite3_close(teacherdb);
    }
}

sqlite3* connectDB()
{
    sqlite3 *teacherdb;
    sqlite3_open("data.db",&teacherdb);
    char *sql="select count(*) from sqlite_master where type='table' and name = 'teacherdata';";
    char *err;
    int retc=sqlite3_exec(teacherdb,sql,isTableExistCallback,NULL,&err);
    if(retc != SQLITE_OK)
    {
        printf("连接数据库失败。错误码：%d，错误信息：%s\n",retc,err);
        exit(0);
    }
    else
        return teacherdb;

}

int isTableExistCallback(void *,int nCount,char **cValue,char **cName)
{
    
}

