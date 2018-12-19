// 包含必要的头文件
#include "includeheaders.h"
#include "softio.h"

void showWelcome() // 运行前先显示欢迎信息
{
    printf("               欢迎使用教师工资管理系统。\n\n");  // 欢迎语，3秒后消失。
    printf("该系统由18270112班 傅则凡 周韦彤 曹彦洋 同学制作。\n\n");
    printf("                                              最后更新：2018/01/27");
    Sleep(3000);
}

void mainMenu() // 主菜单函数
{
    system("cls"); // 清屏
    printf("教师工资管理系统 - 主菜单\n\n");
    printf("请输入您需要进行的操作前的序号，并回车。\n\n\n\n");
    printf("1. 【新增】教师信息\n\n");
    printf("2. 【修改】教师信息\n\n");
    printf("3. 【删除】教师信息\n\n");
    printf("4. 【查询】教师信息\n\n");
    printf("0. 【退出】");

    printf("请输入操作代码：");
}

void search() //查找教师信息
{
    int a,teacherID;
    char name;
    int phone;
    printf("请选择输入教师的信息类型：\n【1】.教师编号\n【2】.教师姓名\n【3】.联系电话\n");
    scanf("%d",&a);
    switch(a)
    {
        case(1):
            printf("教师编号：\n");
            scanf("%d",&teacherID);                        
            
            break;
        case(2):
            printf("教师姓名：\n");
            scanf("%s",&name);

            break;
        case(3):
            printf("联系电话：\n");
            scanf("%d",&phone);

            break;
        default:
            printf("请重新输入\n");
    }
}

