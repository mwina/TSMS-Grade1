#include "includeheaders.h"

void checkFileProi();
sqlite3* connectDB();
int isTableExistCallback(void *,int nCount,char **cValue,char **cName);

void checkFileProi() // 用于检查数据库文件状态
{
    if(!access("data.db",0)) // 是否存在
    {
        if(access("data.db",6)) // 是否可读写,不可读写直接退出。
            {
                printf("数据库文件无法读写，请检查是否有程序占用数据文件，并在占用解除后重启本程序。\n"); // 输出无法读写信息
                system("pause"); // 暂停
                exit(0); // 强制退出
            }
    }
    else // 不存在则开始新建
    {
        printf("数据库文件丢失，3秒后新建。\n");
        Sleep(3000); // 等待三秒
        sqlite3 *teacherdb; // 定义数据库访问指针
        sqlite3_open("data.db",&teacherdb); // 打开数据库文件，不存在的话就会自动新建
        sqlite3_close(teacherdb); // 关闭数据库文件，新建完成
    }
}

sqlite3* connectDB() // 用于连接数据库
{
    sqlite3 *teacherdb; // 定义数据库访问指针
    sqlite3_open("data.db",&teacherdb); // 打开数据库文件
    char *sql="select count(*) from sqlite_master where type='table' and name = 'teacherdata';",*err; // 定义sql语句和错误消息变量
    int isTableExist=0; // 定义变量，是否存在表
    int retc=sqlite3_exec(teacherdb,sql,isTableExistCallback,&isTableExist,&err); // 查询数据库
    if(retc != SQLITE_OK) // 如果查询语句执行失败
    {
        printf("连接数据库失败。错误码：%d，错误信息：%s\n",retc,err); // 抛出错误
        exit(0); //强制退出
    }
    if(isTableExist== 0)
    {
        printf("未找到数据表，新建中...\n");
        char *sqlct="CREATE TABLE teacherdata(" \
                    "TeacherID      INT PRIMARY KEY NOT NULL," \
                    "Name           TEXT            NOT NULL," \
                    "Gender         INT             NOT NULL," \
                    "OfficeAddr     TEXT            NOT NULL," \
                    "HomeAddr       TEXT            NOT NULL," \
                    "PhoneNumber    INT             NOT NULL," \
                    "BasicSalary    REAL            NOT NULL," \
                    "Adds           REAL            NOT NULL," \
                    "AddsLife       REAL            NOT NULL," \
                    "TelephoneFee   REAL            NOT NULL," \
                    "WaterElectricityFee REAL       NOT NULL," \
                    "HouseFee       REAL            NOT NULL," \
                    "GainTax        REAL            NOT NULL," \
                    "HealthFee      REAL            NOT NULL," \
                    "PublicFee      REAL            NOT NULL," \
                    "SalaryBeforeFee REAL           NOT NULL," \
                    "TotalFee       REAL            NOT NULL," \
                    "SalaryAfterFee REAL            NOT NULL);";
        int retc2= sqlite3_exec(teacherdb,sqlct,NULL,NULL,&err);
        if(retc2 != SQLITE_OK)
        {
            printf("创建表失败。错误码：%d，错误信息：%s\n",retc2,err);
            exit(0);
        }
    }
    return teacherdb;

}

int isTableExistCallback(void *ret,int nCount,char **cValue,char **cName)
{
    int *retint = (int *)ret;
    if(nCount==0)
        *retint = 0;
    else
        *retint = 1;
    return SQLITE_OK;
}

void addTeacherToDB(sqlite3 *teacherdb,const teacher *t)
{
    char sql[500]="",*err;
    sprintf(sql,"INSERT INTO teacherdata VALUES (%d,\'%s\',%d,\'%s\',\'%s\',%d,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf);"
            ,t->TeacherID,t->Name,t->Gender,t->OfficeAddr,t->HomeAddr,t->PhoneNumber,t->BasicSalary,t->Adds,t->AddsLife,t->TelephoneFee,t->WaterElectricityFee
            ,t->HouseFee,t->GainTax,t->HealthFee,t->PublicFee,t->SalaryBeforeFee,t->TotalFee,t->SalaryAfterFee);
    int retc=sqlite3_exec(teacherdb,sql,NULL,NULL,&err);
    if(retc != SQLITE_OK)
        printf("添加教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
    else
        printf("添加教师数据成功。\n");
    system("pause");
}

void findTeacherinDB_TeacherID(sqlite3 *teacherdb,int id)
{
    char sql[300]="",*err;

}

