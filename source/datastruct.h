#ifndef DATASTRUCT_H
#define DATASTRUCT_H


// 定义 teacher 结构体
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

void salaryAfterFee(teacher *tmp);
void salaryBeforeFee(teacher *tmp);
void totalFee(teacher *tmp);

#endif
