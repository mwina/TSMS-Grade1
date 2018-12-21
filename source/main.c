// 开始包含基本头文件
#include "includeheaders.h"
#include "dboperation.h"
#include "softio.h"

// 函数声明
void reDirect(int opt);
void showWelcome();
void mainMenu();
void search();

// 全局变量定义
extern sqlite3 *dbaccess;

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

// 程序入口点
int main()
{
    checkFileProi(); // 先检查数据文件状态
    dbaccess=connectDB(); // 连接数据库，并传递数据库连接指针
    showWelcome(); // 显示欢迎消息
    while(1)
    {
        mainMenu();
        int opt=0;
        scanf("%d",&opt);
        reDirect(opt);
    }
    return 0;
}

void reDirect(int opt) // 依据操作码重定向函数
{
    teacher tmp;
    switch(opt) // switch-case分支以进行条件判断
    {
        case 0: // 用户选择退出
            printf("程序将于5秒钟后退出。");
            Sleep(5000); // 等待5秒
            exit(0); // 强制退出程序
        case 1:
            inputTeacher(&tmp);
            addTeacherToDB(dbaccess,&tmp);
            break;
        case 2:

        case 3:

        case 4:

        default: // 输入不同于以上所有情况的操作符
            printf("无法识别的操作符，请重新输入。");
            break; // break后回到主菜单
    }
}

void search() //查找教师信息
{
    int choice,teacherID,userPhoneNumber;
    char name[10]="";
    printf("请选择输入教师的信息类型：\n【1】.教师编号\n【2】.教师姓名\n【3】.联系电话\n\n输入您的选择：");
    scanf("%d",&choice);
    switch(choice)
    {
        case(1):
            printf("教师编号：\n");
            scanf("%d",&teacherID);
            findTeacherinDB_TeacherID(dbaccess,teacherID);
            break;
        case(2):
            printf("教师姓名：\n");
            scanf("%s",name);

            break;
        case(3):
            printf("联系电话：\n");
            scanf("%d",&userPhoneNumber);

            break;
        default:
            printf("请重新输入\n");
    }
}
