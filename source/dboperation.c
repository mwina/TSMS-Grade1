// 包含必要的头文件
#include "includeheaders.h"
#include "softio.h"

// 各函数的声明
void checkFileProi();
sqlite3* connectDB();
int isTableExistCallback(void *,int nCount,char **cValue,char **cName);
void addTeacherToDB(sqlite3 *teacherdb,const teacher *t);
void findTeacherinDB_TeacherID(sqlite3 *teacherdb,int id);
void findTeacherinDB_TeacherName(sqlite3 *teacherdb,const char *name);
void findTeacherinDB_PhoneNumber(sqlite3 *teacherdb,const char *phone);
int findTeacherCallback(void *ret,int nCount,char **cValue,char **cName);

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
    char *sql="SELECT COUNT(*) FROM sqlite_master WHERE TYPE='table' AND NAME='teacherdata';",*err; // 定义sql语句和错误消息变量
    int isTableExist=0; // 定义变量，是否存在表
    int retc=sqlite3_exec(teacherdb,sql,isTableExistCallback,&isTableExist,&err); // 查询数据库
    if(retc != SQLITE_OK) // 如果查询语句执行失败
    {
        printf("连接数据库失败。错误码：%d，错误信息：%s\n",retc,err); // 抛出错误
        exit(0); //强制退出
    }
    if(isTableExist== 0) // 如果不存在数据表
    {
        printf("未找到数据表，新建中...\n"); // 提醒用户
        // 使用sql语句在当前文件中新建
        char *sqlct="CREATE TABLE teacherdata(" \
                    "TeacherID      INT PRIMARY KEY NOT NULL," \
                    "Name           TEXT            NOT NULL," \
                    "Gender         INT             NOT NULL," \
                    "OfficeAddr     TEXT            NOT NULL," \
                    "HomeAddr       TEXT            NOT NULL," \
                    "PhoneNumber    TEXT            NOT NULL," \
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
        int retc2= sqlite3_exec(teacherdb,sqlct,NULL,NULL,&err); // 调用数据表创建语句
        if(retc2 != SQLITE_OK) // 如果sql语句执行失败
        {
            printf("创建表失败。错误码：%d，错误信息：%s\n",retc2,err); // 提示用户
            exit(0); // 数据表不存在，无法执行后续操作，强制退出
        }
    }
    return teacherdb; // 返回sql连接指针，在后续操作中使用

}

int isTableExistCallback(void *ret,int nCount,char **cValue,char **cName) // 判断数据表是否存在时的回调函数
{
    int *retint = (int *)ret; // 指针强制类型转换
    if(atoi(cValue[0])==0) // 读取sql语句的返回值，执行操作
        *retint = 0;
    else
        *retint = 1;
    return SQLITE_OK; // 回调执行成功，返回0
}

void addTeacherToDB(sqlite3 *teacherdb,const teacher *t) // 将教师数据写入数据库
{
    char sql[500]="",*err; // 定义sql语句和错误指针
    sprintf(sql,"INSERT INTO teacherdata VALUES (%d,\'%s\',%d,\'%s\',\'%s\',\'%s\',%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf,%.5lf);"
            ,t->TeacherID,t->Name,t->Gender,t->OfficeAddr,t->HomeAddr,t->PhoneNumber,t->BasicSalary,t->Adds,t->AddsLife,t->TelephoneFee,t->WaterElectricityFee
            ,t->HouseFee,t->GainTax,t->HealthFee,t->PublicFee,t->SalaryBeforeFee,t->TotalFee,t->SalaryAfterFee); // 此处构造sql语句并printf到字符串中
    int retc=sqlite3_exec(teacherdb,sql,NULL,NULL,&err); // 执行sql语句
    if(retc != SQLITE_OK) // 若sql执行失败
        printf("添加教师数据失败。错误码：%d，错误信息：%s\n",retc,err); // 提醒用户
    else // 否则
        printf("添加教师数据成功。\n"); // 告知用户成功
    system("pause"); // 暂停
}

void findTeacherinDB_TeacherID(sqlite3 *teacherdb,int id) // 通过教师id到数据库中查询教师
{
    char sql[300]="",*err;
    teacher t;
    sprintf(sql,"SELECT * FROM teacherdata WHERE TeacherID=%d",id); // 构造select语句
    int retc=sqlite3_exec(teacherdb,sql,findTeacherCallback,&t,&err);
    if(retc != SQLITE_OK)
        printf("查询教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
    else
        outputTeacher(&t);
    system("pause");
}

void findTeacherinDB_TeacherName(sqlite3 *teacherdb,const char *name)
{
    char sql[300]="",*err;
    teacher t;
    sprintf(sql,"SELECT * FROM teacherdata WHERE Name=\'%s\'",name);
    int retc=sqlite3_exec(teacherdb,sql,findTeacherCallback,&t,&err);
    if(retc != SQLITE_OK)
        printf("查询教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
    else
        outputTeacher(&t);
    system("pause");
}

void findTeacherinDB_PhoneNumber(sqlite3 *teacherdb,const char *phone)
{
    char sql[300]="",*err;
    teacher t;
    sprintf(sql,"SELECT * FROM teacherdata WHERE PhoneNumber=\'%s\'",phone);
    int retc=sqlite3_exec(teacherdb,sql,findTeacherCallback,&t,&err);
    if(retc != SQLITE_OK)
        printf("查询教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
    else
        outputTeacher(&t);
    system("pause");
}

int findTeacherCallback(void *ret,int nCount,char **cValue,char **cName) // 查询教师时的回调函数
{

    teacher *retdata=(teacher*)ret;

    retdata->TeacherID=atoi(cValue[0]);
    strcpy(retdata->Name,cValue[1]);
    retdata->Gender=atoi(cValue[2]);
    strcpy(retdata->OfficeAddr,cValue[3]);
    strcpy(retdata->HomeAddr,cValue[4]);
    strcpy(retdata->PhoneNumber,cValue[5]);
    retdata->BasicSalary=atof(cValue[6]);
    retdata->Adds=atof(cValue[7]);
    retdata->AddsLife=atof(cValue[8]);
    retdata->TelephoneFee=atof(cValue[9]);
    retdata->WaterElectricityFee=atof(cValue[10]);
    retdata->HouseFee=atof(cValue[11]);
    retdata->GainTax=atof(cValue[12]);
    retdata->HealthFee=atof(cValue[13]);
    retdata->PublicFee=atof(cValue[14]);
    retdata->SalaryBeforeFee=atof(cValue[15]);
    retdata->TotalFee=atof(cValue[16]);
    retdata->SalaryAfterFee=atof(cValue[17]);

    return SQLITE_OK;
}

void updataTeacherinDB(sqlite3 *teacherdb,int id)
{
    char sql[300]="",*err;
    int choice=0;
    int newID=id;
    char gen;
    int newgender;
    char nameAndAddr;
    double fee;
    teacher t;
    sprintf(sql,"SELECT * FROM teacherdata WHERE TeacherID=%d",id); // 构造select语句
    int retc=sqlite3_exec(teacherdb,sql,findTeacherCallback,&t,&err);
    if(retc != SQLITE_OK)
    {
        printf("查询教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
    }
    else
    {
        outputTeacher(&t);
        while(choice<=15&&choice>=0)
        {
            printf("请选择需要修改的项目：");
            printvariables();
            printf("【0】.退出修改\n");
            scanf("%d",&choice);
            switch(choice)
            {
                case(0):
                    printf("退出中\n");
                    Sleep(2000);
                    choice=16;
                    break;
                case(1):
                    printf("请输入：");
                    scanf("%d",&newID);
                    sprinf(sql,"UPDATE teacherdata SET TeacherID = %d WHERE TeacherID = %d",newID,id);
                    retc=sqlite3_exec(teacherdb,sql,0,0,&err);
                    if(retc != SQLITE_OK)
                    {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
                    }
                    break;
                case(2):
                    printf("请输入：");
                    scanf("%s",&nameAndAddr);
                    sprinf(sql,"UPDATE teacherdata SET Name = \'%s\' WHERE TeacherID = %d",nameAndAddr,id);
                    retc=sqlite3_exec(teacherdb,sql,0,0,&err);
                    if(retc != SQLITE_OK)
                    {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
                    }
                    break;
                case(3):
                    printf("请输入：");
                    scanf("%s",&gen);
                    if(strcmp(gen,"男"))
                        newgender = 0;
                    else
                        newgender = 1;
                    sprinf(sql,"UPDATE teacherdata SET Gender = %d WHERE TeacherID = %d",newgender,id);
                    retc=sqlite3_exec(teacherdb,sql,0,0,&err);
                    if(retc != SQLITE_OK)
                    {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
                    }
                    break;
                case(4):
                    printf("请输入：");
                    scanf("%s",&nameAndAddr);
                    sprinf(sql,"UPDATE teacherdata SET OfficeAddr = \'%s\' WHERE TeacherID = %d",nameAndAddr,id);
                    retc=sqlite3_exec(teacherdb,sql,0,0,&err);
                    if(retc != SQLITE_OK)
                    {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
                    }
                    break;
                case(5):
                    printf("请输入：");
                    scanf("%s",&nameAndAddr);
                    sprinf(sql,"UPDATE teacherdata SET HomeAddr = \'%s\' WHERE TeacherID = %d",nameAndAddr,id);
                    retc=sqlite3_exec(teacherdb,sql,0,0,&err);
                    if(retc != SQLITE_OK)
                    {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
                    }
                    break;
                case(6):
                    printf("请输入：");
                    scanf("%s",&nameAndAddr);
                    sprinf(sql,"UPDATE teacherdata SET PhoneNumber = \'%s\' WHERE TeacherID = %d",nameAndAddr,id);
                    retc=sqlite3_exec(teacherdb,sql,0,0,&err);
                    if(retc != SQLITE_OK)
                    {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
                    }
                    break;
                case(7):
                    printf("请输入：");
                    scanf("%lf",&fee);
                    sprinf(sql,"UPDATE teacherdata SET BasicSalary = %lf WHERE TeacherID = %d",fee,id);
                    retc=sqlite3_exec(teacherdb,sql,0,0,&err);
                    if(retc != SQLITE_OK)
                    {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
                    }
                    break;
                case(8):
                    printf("请输入：");
                    scanf("%lf",&fee);
                    sprinf(sql,"UPDATE teacherdata SET Adds = %lf WHERE TeacherID = %d",fee,id);
                    retc=sqlite3_exec(teacherdb,sql,0,0,&err);
                    if(retc != SQLITE_OK)
                    {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
                    }
                    break;
                case(9):
                    printf("请输入：");
                    scanf("%lf",&fee);
                    sprinf(sql,"UPDATE teacherdata SET AddsLife = %lf WHERE TeacherID = %d",fee,id);
                    retc=sqlite3_exec(teacherdb,sql,0,0,&err);
                    if(retc != SQLITE_OK)
                    {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
                    }
                    break;
                case(10):
                    printf("请输入：");
                    scanf("%lf",&fee);
                    sprinf(sql,"UPDATE teacherdata SET TelephoneFee = %lf WHERE TeacherID = %d",fee,id);
                    retc=sqlite3_exec(teacherdb,sql,0,0,&err);
                    if(retc != SQLITE_OK)
                    {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
                    }
                    break;
                case(11):
                    printf("请输入：");
                    scanf("%lf",&fee);
                    sprinf(sql,"UPDATE teacherdata SET WaterElectricityFee = %lf WHERE TeacherID = %d",fee,id);
                    retc=sqlite3_exec(teacherdb,sql,0,0,&err);
                    if(retc != SQLITE_OK)
                    {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
                    }
                    break;
                case(12):
                    printf("请输入：");
                    scanf("%lf",&fee);
                    sprinf(sql,"UPDATE teacherdata SET HouseFee = %lf WHERE TeacherID = %d",fee,id);
                    retc=sqlite3_exec(teacherdb,sql,0,0,&err);
                    if(retc != SQLITE_OK)
                    {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
                    }
                    break;
                case(13):
                    printf("请输入：");
                    scanf("%lf",&fee);
                    sprinf(sql,"UPDATE teacherdata SET GainTax = %lf WHERE TeacherID = %d",fee,id);
                    retc=sqlite3_exec(teacherdb,sql,0,0,&err);
                    if(retc != SQLITE_OK)
                    {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
                    }
                    break;
                case(14):
                    printf("请输入：");
                    scanf("%lf",&fee);
                    sprinf(sql,"UPDATE teacherdata SET HealthFee = %lf WHERE TeacherID = %d",fee,id);
                    retc=sqlite3_exec(teacherdb,sql,0,0,&err);
                    if(retc != SQLITE_OK)
                    {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
                    }
                    break;
                case(15):
                    printf("请输入：");
                    scanf("%lf",&fee);
                    sprinf(sql,"UPDATE teacherdata SET PublicFee = %lf WHERE TeacherID = %d",fee,id);
                    retc=sqlite3_exec(teacherdb,sql,0,0,&err);
                    if(retc != SQLITE_OK)
                    {
                        printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
                    }
                    break;
            }
            id=newID;
            salaryBeforeFee(&t);
            totalFee(&t);
            salaryAfterFee(&t);
            fee=t.SalaryBeforeFee;
            sprinf(sql,"UPDATE teacherdata SET SalaryBeforeFee = %lf WHERE TeacherID = %d",fee,id);
            retc=sqlite3_exec(teacherdb,sql,0,0,&err);
            if(retc != SQLITE_OK)
            {
                printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
            }
            fee=t.TotalFee;
            sprinf(sql,"UPDATE teacherdata SET TotalFee = %lf WHERE TeacherID = %d",fee,id);
            retc=sqlite3_exec(teacherdb,sql,0,0,&err);
            if(retc != SQLITE_OK)
            {
                printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
            }
            fee=t.SalaryAfterFee;
            sprinf(sql,"UPDATE teacherdata SET SalaryAfterFee = %lf WHERE TeacherID = %d",fee,id);
            retc=sqlite3_exec(teacherdb,sql,0,0,&err);
            if(retc != SQLITE_OK)
            {
                printf("修改教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
            }        
        }
    }
}



void deleteTeacherinDB(sqlite3 *teacherdb,int id)
{
    char sql[300]="",*err;
    teacher t;
    sprinf(sql,"SELECT * FROM teacherdata WHERE TeacherID=%d",id);
    int retc=sqlite3_exec(teacherdb,sql,findTeacherCallback,&t,&err);
    if(retc != SQLITE_OK)
    {
        printf("删除教师数据失败。错误码：%d，错误信息：%s\n",retc,err);
        printf("请先查询教师信息是否存在。\n");
    }  
    else
        printf("删除教师数据成功。\n");
    system("pause");    
}