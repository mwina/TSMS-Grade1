// 防止头文件被重复包含
#ifndef SALARYCALC_H
#define SALARYCALC_H

#include "includeheaders.h"
#include "datastruct.h"

void salaryAfterFee(teacher *tmp);
void salaryBeforeFee(teacher *tmp);
void totalFee(teacher *tmp);

#endif
