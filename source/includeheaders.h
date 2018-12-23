// 防止被重复包含的头
#ifndef INCLUDEHEADERS_H
#define INCLUDEHEADERS_H

// 主要放置基础头文件
#include <stdio.h>       // C标准输入输出
#include <stdlib.h>      // C标准库函数
#include <string.h>      // C字符串函数
#include <io.h>         // C扩展输入输出
#include <windows.h>    // C窗口
#include "sqlite3.h"    // SQLite3的库

// 定义 teacher 结构体
typedef struct Teacher
{
    int TeacherID;
    char Name[10];
    int Gender;
    char OfficeAddr[100];
    char HomeAddr[100];
    char PhoneNumber[20]; // 电话号码位数超过int表示范围，利用字符串表示
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

void printvariables()
{
    printf("【1】.教师编号\n");
    printf("【2】.教师姓名\n");
    printf("【3】.教师性别\n");
    printf("【4】.单位名称\n");
    printf("【5】.家庭住址\n");
    printf("【6】.联系电话\n");
    printf("【7】.基本工资\n");
    printf("【8】.津贴\n");
    printf("【9】.生活补贴\n");
    printf("【10】.电话费\n");
    printf("【11】.水电费\n");
    printf("【12】.房租\n");
    printf("【13】.所得税\n");
    printf("【14】.卫生费\n");
    printf("【15】.公积金\n");
}

// 分别是计算实发工资、应发工资和合计扣款的函数定义
void salaryAfterFee(teacher *tmp);
void salaryBeforeFee(teacher *tmp);
void totalFee(teacher *tmp);

#endif