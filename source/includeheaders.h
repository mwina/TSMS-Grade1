// 防止被重复包含的头
#ifndef INCLUDEHEADERS_H
#define INCLUDEHEADERS_H

// 主要放置基础头文件
#include <stdio.h>       // C标准输入输出
#include <stdlib.h>      // C标准库函数
#include <string.h>      // C字符串函数
#include <io.h>         // C扩展输入输出
#include <windows.h>    // C窗口
#include "sqlite3.h"
#include "utf8_gbk_mem.h"

// 定义 teacher 结构体
typedef struct Teacher
{
    int TeacherID;
    char Name[10];
    int Gender;
    char OfficeAddr[100];
    char HomeAddr[100];
    char PhoneNumber[20];
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

void salaryAfterFee(teacher *tmp);
void salaryBeforeFee(teacher *tmp);
void totalFee(teacher *tmp);

#endif