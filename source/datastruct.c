#include "includeheaders.h"
#include "datastruct.h"

// 计算包含了补贴的应发工资总额
void salaryBeforeFee(teacher *tmp)
{
    tmp->SalaryBeforeFee = tmp->BasicSalary + tmp->Adds + tmp->AddsLife;
}

// 计算包含各项费用的扣除费用总额
void totalFee(teacher *tmp)
{
    tmp->TotalFee = tmp->GainTax + tmp->HealthFee + tmp->HouseFee + tmp->PublicFee + tmp->TelephoneFee + tmp->WaterElectricityFee;
}

// 相减求得实发工资总额
void salaryAfterFee(teacher *tmp)
{
    tmp->SalaryAfterFee = tmp->SalaryBeforeFee - tmp->TotalFee;
}
