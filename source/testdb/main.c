#include <stdio.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <string.h>
#include "utf8_gbk_mem.h"

typedef struct Teacher
{
    int TeacherID;
    char Name[10];
    int Gender;
    char OfficeAddr[100];
    char HomeAddr[100];
    int PhoneNumber;
    double BasicSalary;
    double Adds;
    double AddsLife;
    double TelephoneFee;
    double WaterElectricityFee;
    double HouseFee;
    double GainTax;
    double HealthFee;
    double PublicFee;
    double SalaryBeforeFee;
    double TotalFee;
    double SalaryAfterFee;
} teacher;

sqlite3 *dbaccess;

void outputTeacher(const teacher *t)
{
    printf("教师详情\n\n");
    printf("-----基本信息-----\n");
    printf("教师编号：%d\n教师姓名：%s\n",t->TeacherID,t->Name);
    if(t->Gender)
        printf("教师性别：女\n");
    else
        printf("教师性别：男\n");
    printf("单位名称：%s\n家庭住址：%s\n联系电话：%d\n\n",t->OfficeAddr,t->HomeAddr,t->PhoneNumber);
    printf("-----基本工资与补贴-----\n");
    printf("基本工资：%.5lf\n津贴：%.5lf\n生活补贴：%.5lf\n\n",t->BasicSalary,t->Adds,t->AddsLife);
    printf("-----扣款信息-----\n");
    printf("电话费：%.5lf\n水电费：%.5lf\n房租：%.5lf\n所得税：%.5lf\n卫生费：%.5lf\n公积金：%.5lf\n\n"
            ,t->TelephoneFee,t->WaterElectricityFee,t->HouseFee,t->GainTax,t->HealthFee,t->PublicFee);
    printf("-----合计-----\n");
    printf("应发工资：%.5lf\n合计扣款：%.5lf\n实发工资：%.5lf\n",t->SalaryBeforeFee,t->TotalFee,t->SalaryAfterFee);
}

int callback(void *ret,int nCount,char **cValue,char **cName)
{
    teacher *retdata=(teacher*)ret;

    retdata->TeacherID=atoi(cValue[0]);
    utf82gbk_(cValue[1],retdata->Name);
    retdata->Gender=atoi(cValue[2]);
    utf82gbk_(cValue[3],retdata->OfficeAddr);
    utf82gbk_(cValue[4],retdata->HomeAddr);
    retdata->PhoneNumber=atoi(cValue[5]);
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

    outputTeacher(retdata);
    return SQLITE_OK;
}

int main() {
    sqlite3_open("data.db",&dbaccess);
    teacher t;
    char *sql="SELECT * FROM teacherdata WHERE TeacherID=10000;",*err; // 定义sql语句和错误消息变量
    int retc=sqlite3_exec(dbaccess,sql,callback,&t,&err); // 查询数据库
    if(retc != SQLITE_OK) // 如果查询语句执行失败
        printf("连接数据库失败。错误码：%d，错误信息：%s\n",retc,err); // 抛出错误
     return 0;
}