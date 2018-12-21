// 包含必要头文件
#include "includeheaders.h"

void outputTeacher(const teacher *t) // 输出教师信息
{
    printf("教师详情\n\n");
    printf("-----基本信息-----\n"); // 分为四个部分：基本信息，基本工资和补贴，扣款信息和合计
    printf("教师编号：%d\n教师姓名：%s\n",t->TeacherID,t->Name);
    if(t->Gender) // 通过int值判断性别
        printf("教师性别：女\n");
    else
        printf("教师性别：男\n");
    printf("单位名称：%s\n家庭住址：%s\n联系电话：%s\n\n",t->OfficeAddr,t->HomeAddr,t->PhoneNumber);
    printf("-----基本工资与补贴-----\n");
    printf("基本工资：%.5lf\n津贴：%.5lf\n生活补贴：%.5lf\n\n",t->BasicSalary,t->Adds,t->AddsLife);
    printf("-----扣款信息-----\n");
    printf("电话费：%.5lf\n水电费：%.5lf\n房租：%.5lf\n所得税：%.5lf\n卫生费：%.5lf\n公积金：%.5lf\n\n"
        ,t->TelephoneFee,t->WaterElectricityFee,t->HouseFee,t->GainTax,t->HealthFee,t->PublicFee);
    printf("-----合计-----\n");
    printf("应发工资：%.5lf\n合计扣款：%.5lf\n实发工资：%.5lf\n",t->SalaryBeforeFee,t->TotalFee,t->SalaryAfterFee);
}

void inputTeacher(teacher *t) // 输入教师信息，并通过指针修改传入的t指向的结构体变量
{
    char gen[3]; // 输入汉字的性别，默认是GBK编码，利用字符串判等判断是否是男或女
    printf("教师详情输入页\n\n");
    printf("-----基本信息-----\n");
    printf("教师编号：");
    scanf("%d",&t->TeacherID);
    printf("教师姓名：");
    scanf("%s",t->Name);
    printf("教师性别：");
    scanf("%s",gen);
    if(strcmp(gen,"男"))
        t->Gender = 0;
    else
        t->Gender = 1;
    printf("单位名称：\n");
    scanf("%s",t->OfficeAddr);
    printf("家庭住址：\n");
    scanf("%s",t->HomeAddr);
    printf("联系电话：\n");
    scanf("%s",t->PhoneNumber);
    printf("\n\n-----基本工资与补贴-----\n");
    printf("基本工资：\n");
    scanf("%lf",&t->BasicSalary);
    printf("津贴：\n");
    scanf("%lf",&t->Adds);
    printf("生活补贴：\n");
    scanf("%lf",&t->AddsLife);
    printf("\n\n-----扣款信息-----\n");
    printf("电话费：\n");
    scanf("%lf",&t->TelephoneFee);
    printf("水电费：\n");
    scanf("%lf",&t->WaterElectricityFee);
    printf("房租：\n");
    scanf("%lf",&t->HouseFee);
    printf("所得税：\n");
    scanf("%lf",&t->GainTax);
    printf("卫生费：\n");
    scanf("%lf",&t->HealthFee);
    printf("公积金：\n");
    scanf("%lf",&t->PublicFee);
    printf("-----输入完毕-----\n\n");
    
    salaryBeforeFee(t); // 输入完毕后立即计算并传递
    totalFee(t);
    salaryAfterFee(t);
    printf("-----合计-----\n");
    printf("应发工资：%.5lf\n合计扣款：%.5lf\n实发工资：%.5lf\n",t->SalaryBeforeFee,t->TotalFee,t->SalaryAfterFee);
}