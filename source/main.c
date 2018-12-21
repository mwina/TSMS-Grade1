// 开始包含基本头文件
#include "includeheaders.h"
#include "dboperation.h"
#include "softio.h"

// 函数声明
void reDirect(int opt);
void showWelcome();
void mainMenu();
void searchMenu();
void addTeacherMenu();
void updataMenu();
void deleteMenu();

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
    
    switch(opt) // switch-case分支以进行条件判断
    {
        case (0): // 用户选择退出
            printf("程序将于5秒钟后退出。");
            Sleep(5000); // 等待5秒
            exit(0); // 强制退出程序
        case (1):
            addTeacherMenu();
            break;
        case (2):        
            updataMenu();
            break;            
        case (3):
            deleteMenu();
            break;
        case (4):
            searchMenu();
            break;
        default: // 输入不同于以上所有情况的操作符
            printf("无法识别的操作符，请重新输入。");
            break; // break后回到主菜单
    }
}

void addTeacherMenu()
{
    teacher tmp;
    int choiceafteradd;
    inputTeacher(&tmp);
    addTeacherToDB(dbaccess,&tmp);
    while(1)
    {
        printf("请选择在查询后的操作：\n【1】.新增\n【2】.修改\n【3】.查询\n【0】.返回主菜单\n\n输入您的选择：");
        scanf("%d",&choiceafteradd);
        switch(choiceafteradd)
        {
            case(1):
                addTeacherMenu();
                break;                                            
            case(2):
                updataMenu();
                break;
            case(3):
                printf("开始查询下一个教师信息");
                searchMenu();
                break;
            case(0):
                printf("正在返回主菜单");
                Sleep(3000);
                break;            
            default:
                printf("请重新输入。\n");                                                     
        }
    }
}

void searchMenu() //查找教师信息
{
    int choice,teacherID,userPhoneNumber;
    char name[10]="";
    int choiceaftersearch; //执行查找后的操作
    while(1)
    {
        printf("请选择输入教师的信息类型：\n【1】.教师编号\n【2】.教师姓名\n【3】.联系电话\n\n输入您的选择：");
        scanf("%d",&choice);
        switch(choice)
        {
            case(1): //输入教师编号以查询
                printf("教师编号：");
                scanf("%d",&teacherID);
                findTeacherinDB_TeacherID(dbaccess,teacherID);
                break;
            case(2): //输入教师姓名以查询
                printf("教师姓名：");
                scanf("%s",name);
                findTeacherinDB_TeacherName(dbaccess,name);
                break;
            case(3): //输入教师联系电话以查询
                printf("联系电话：");
                scanf("%d",&userPhoneNumber);
                findTeacherinDB_PhoneNumber(dbaccess,userPhoneNumber);
                break;
            default:
                printf("请重新输入。\n");
        }
    }
    while(1) //进行查询之后的操作
    {
        printf("请选择在查询后的操作：\n【1】.修改\n【2】.删除\n【3】.查询下一个\n【0】.返回主菜单\n\n输入您的选择：");
        scanf("%d",&choiceaftersearch);
        switch(choiceaftersearch)        
        {
            case(1):                                
                updataMenu();                        
                break;                                            
            case(2):
                deleteMenu();
                break;
            case(3):
                printf("开始查询下一个教师信息");
                searchMenu();                                    
                break;
            case(0):
                printf("正在返回主菜单");
                Sleep(3000);
                break;            
            default:
                printf("请重新输入。\n");                                                     
        }
    }    
}

void updataMenu()
{
    teacher tmp;
    int choiceafterupdate;
    
    //修改函数
    
    while(1)
    {
        printf("请选择在修改后的操作：\n【1】.新增\n【2】.查询\n【0】.返回主菜单\n\n输入您的选择：");
        scanf("%d",&choiceafterupdate);
        switch(choiceafterupdate)
        {
            case(1):
                printf("开始新增教师信息");
                addTeacherMenu();
            break;                                            
            case(2):
                printf("开始查询教师信息");
                searchMenu();
                break;
            case(0):
                printf("正在返回主菜单");
                Sleep(3000);
                break;            
            default:
                printf("请重新输入。\n");                                              
        }                
    }
}

void deleteMenu()
{
    teacher tmp;
    int choiceafterdelete;    
    //删除函数
    while(1)
    {
        printf("请选择在删除后的操作：\n【1】.新增\n【2】.查询\n【0】.返回主菜单\n\n输入您的选择：");
        scanf("%d",&choiceafterdelete);        
        switch (choiceafterdelete)
        {
        case(1):
            printf("开始新增教师信息");
            addTeacherMenu();
            break;                                            
        case(2):
            printf("开始查询教师信息");
            searchMenu();
            break;
        case(0):
            printf("正在返回主菜单");
            Sleep(3000);
            break;            
        default:
            printf("请重新输入。\n");                                                     
        }
    }                
}
