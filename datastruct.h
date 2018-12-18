#ifndef DATASTRUCT_H
#define DATASTRUCT_H


// 定义 teacher 结构体
struct teacher
{
    int TeacherID;
    char Name[10];
    bool Gender;
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
};

// 设置别名，便于定义
typedef struct teacher Teacher;


#endif
