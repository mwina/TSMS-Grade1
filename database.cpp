// 包含必要头文件
#include "includeheaders.h"
#include "datastruct.h"

// 检查数据库文件是否可读写
void checkFileProi()
{
    if(!access("data.db",0)) // 是否存在
    {
        if(!access("data.db",6)) // 是否可读写
            printf("数据库文件读取成功。\n");
        else // 不可读写直接退出。
            {
                printf("数据库文件无法读写，请检查是否有程序占用数据文件，并在占用解除后重启本程序。\n");
                system("pause");
                exit(0);
            }
    }
    else // 不存在则开始新建
    {
        printf("数据库文件丢失，3秒后新建。\n");
        Sleep(3000); // 等待三秒
        FILE *tmp=NULL;
        tmp=fopen("data.db","w");
        fprintf(tmp,"0");
        fclose(tmp);
    }
    return;          
}

void readFile()
{
    FILE *datafile=NULL; // 文件指针
    datafile=fopen("data.db","r+"); // 已可读写方式打开文件
    int teacherNUM=0;
    fscanf(datafile,"%d",&teacherNUM);
    for(int i=0;i<teacherNUM;i++)
    {
        
    }
}

/*
数据存储方式： 以下皆为1行
ID 名字长度 名字ASCII转int 电话号码 性别 家庭地址长度 家庭地址ASCII转int 单位地址长度 单位地址ASCII转int 基本工资 津贴 生活补贴 电话费 水电费 房租 所得税 卫生费 公积金 应发工资 总扣款 实发工资
*/
void addTeachertoFile(FILE *file,const teacher *t)
{
    fprintf(file,"%d ",t->TeacherID);

    int i=strlen(t->Name);
    fprintf(file,"%d ",i);
    
    for(int k=0;k<i;k++)
        fprintf(file,"%d ",(int)t->Name[k]);
    
    fprintf(file,"%d ",t->PhoneNumber);

    fprintf(file,"%d ",(int)t->Gender);
    
    i=strlen(t->HomeAddr); 
    fprintf(file,"%d ",i);
    
    for(int k=0;k<i;k++)
        fprintf(file,"%d ",(int)t->HomeAddr[k]);
        
    i=strlen(t->OfficeAddr);
    fprintf(file,"%d ",i);
    
    for(int k=0;k<i;k++)
        fprintf(file,"%d ",(int)t->OfficeAddr[k]);
        
    fprintf(file,"%.5lf ",t->BasicSalary);

    fprintf(file,"%.5lf ",t->Adds);

    fprintf(file,"%.5lf ",t->AddsLife);
    
    fprintf(file,"%.5lf ",t->TelephoneFee);

    fprintf(file,"%.5lf ",t->WaterElectricityFee);

    fprintf(file,"%.5lf ",t->HouseFee);

    fprintf(file,"%.5lf ",t->GainTax);

    fprintf(file,"%.5lf ",t->HealthFee);

    fprintf(file,"%.5lf ",t->PublicFee);
    
    fprintf(file,"%.5lf ",t->SalaryBeforeFee);
    
    fprintf(file,"%.5lf ",t->TotalFee);

    fprintf(file,"%.5lf ",t->SalaryAfterFee); 

    return;           
}

teacher readTeacherFromFile(FILE *file)
{
    teacher t;
    fscanf(file,"%d ",&t.TeacherID);

    int i=0;
    fscanf(file,"%d ",&i);

    int k=0;
    for(;k<i;k++)
        fscanf(file,"%c ",&(char)t.Name[k]);
    t.Name[k]='\0';
    
    fscanf(file,"%d ",&t.PhoneNumber);

    int tmp=0;
    fscanf(file,"%d ",&tmp);
    t.Gender = (bool)tmp;
    
    i=0;
    fscanf(file,"%d ",&i);
    
    k=0;
    for(;k<i;k++)
        fscanf(file,"%d ",(int)t->HomeAddr[k]);
        
    i=strlen(t->OfficeAddr);
    fscanf(file,"%d ",i);

    k=0;

    for(;k<i;k++)
        fscanf(file,"%d ",(int)t->OfficeAddr[k]);

    fscanf(file,"%.5lf ",&t.BasicSalary);

    fscanf(file,"%.5lf ",&t.Adds);

    fscanf(file,"%.5lf ",&t.AddsLife);
    
    fscanf(file,"%.5lf ",&t.TelephoneFee);

    fscanf(file,"%.5lf ",&t.WaterElectricityFee);

    fscanf(file,"%.5lf ",&t.HouseFee);

    fscanf(file,"%.5lf ",&t.GainTax);

    fscanf(file,"%.5lf ",&t.HealthFee);

    fscanf(file,"%.5lf ",&t.PublicFee);
    
    fscanf(file,"%.5lf ",&t.SalaryBeforeFee);
    
    fscanf(file,"%.5lf ",&t.TotalFee);

    fscanf(file,"%.5lf ",&t.SalaryAfterFee); 


    return t;
}