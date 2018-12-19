#include "includeheaders.h"
#include "datastruct.h"
#include "salarycalculate.h"

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
    system("pause");
}

void inputTeacher(teacher *t)
{
    char gen[3];
    printf("教师详情输入页\n\n");
    printf("-----基本信息-----\n");
    printf("教师编号：");
    scanf("%d",&t->TeacherID);
    printf("教师姓名：");
    scanf("%s",t->Name);
    printf("教师性别：");
    scanf("%s",gen);
    if(gen == "男")
        t->Gender = 0;
    else
        t->Gender = 1;
    printf("单位名称：\n");
    scanf("%s",t->OfficeAddr);
    printf("家庭住址：\n");
    scanf("%s",t->HomeAddr);
    printf("联系电话：\n");
    scanf("%d",&t->PhoneNumber);
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
    
    salaryBeforeFee(t);
    totalFee(t);
    salaryAfterFee(t);
    printf("-----合计-----\n");
    printf("应发工资：%.5lf\n合计扣款：%.5lf\n实发工资：%.5lf\n",t->SalaryBeforeFee,t->TotalFee,t->SalaryAfterFee);
}