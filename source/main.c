// 开始包含基本头文件
#include "includeheaders.h"
#include "dboperation.h"
#include "softio.h"

// 函数声明
int reDirect(int opt);
void showWelcome();
void mainMenu();
int searchMenu();
int addTeacherMenu();
int updataMenu();
int deleteMenu();

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
        while(opt==(1||2||3||4||0))
        {
            opt=reDirect(opt);
        }
        printf("叫你输入1、2、3、4、0你不输\n");//彩蛋
        Sleep(2000);
        printf("那就只能再见了\n");
        Sleep(2000);
        printf("system command: Force Quit\n");
        Sleep(2000);
        reDirect(0);
    }
    return 0;
}

int reDirect(int opt) // 依据操作码重定向函数
{
    int choice;
    switch(opt) // switch-case分支以进行条件判断
    {
        case (0): // 用户选择退出
            printf("程序将于5秒钟后退出。");
            Sleep(5000); // 等待5秒
            exit(0); // 强制退出程序
        case (1):
            choice=addTeacherMenu();
            break;
        case (2):        
            choice=updataMenu();
            break;            
        case (3):
            choice=deleteMenu();
            break;
        case (4):
            choice=searchMenu();
            break;
        default: // 输入不同于以上所有情况的操作符
            printf("无法识别的操作符，请重新输入。");
            mainMenu();//重新跳出主菜单
            scanf("%d",&choice);//返回新的opt值
            break; 
    }
    return choice;
}

int addTeacherMenu()
{
    teacher tmp;
    int choice;
    int choiceafteradd=0;
    inputTeacher(&tmp);
    addTeacherToDB(dbaccess,&tmp);
    while(choiceafteradd==(1||2||3||0))
    {
        printf("请选择在查询后的操作：\n【1】.新增\n【2】.修改\n【3】.查询\n【0】.返回主菜单\n\n输入您的选择：");
        scanf("%d",&choiceafteradd);
        switch(choiceafteradd)
        {
            case(1):
                printf("开始新增教师信息\n");
                choice=1;
                break;                                            
            case(2):
                printf("开始修改教师信息\n"); 
                choice=2;
                break;
            case(3):
                printf("开始查询下一个教师信息");
                choice=4;
                break;
            case(0):
                printf("正在返回主菜单");
                Sleep(3000);
                mainMenu();//重新跳出主菜单
                scanf("%d",&choice);//返回新的opt值
                break;            
            default:
                printf("请重新输入。\n");                                                     
        }
    }
    return choice;
}

int searchMenu() //查找教师信息
{
    int choice;
    int searchchoice=0,teacherID;
    char name[10]="",userPhoneNumber[20]="";
    int choiceaftersearch; //执行查找后的操作
    while(1)
    {
        printf("请选择输入教师的信息类型：\n【1】.教师编号\n【2】.教师姓名\n【3】.联系电话\n\n输入您的选择：");
        scanf("%d",&searchchoice);
        switch(searchchoice)
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
                scanf("%s",userPhoneNumber);
                findTeacherinDB_PhoneNumber(dbaccess,userPhoneNumber);
                break;
            default:
                printf("请重新输入。\n");
        }
    }
    while(choiceaftersearch==(1||2||3||0)) //进行查询之后的操作
    {
        printf("请选择在查询后的操作：\n【1】.修改\n【2】.删除\n【3】.查询下一个\n【0】.返回主菜单\n\n输入您的选择：");
        scanf("%d",&choiceaftersearch);
        switch(choiceaftersearch)        
        {
            case(1):
                printf("开始修改教师信息\n");                                
                choice=2;                     
                break;                                            
            case(2):
                printf("开始删除教师信息\n");
                choice=3;
                break;
            case(3):
                printf("开始查询下一个教师信息\n");
                choice=4;                        
                break;
            case(0):
                printf("正在返回主菜单\n");
                Sleep(3000);
                mainMenu();//重新跳出主菜单
                scanf("%d",&choice);//返回新的opt值
                break;            
            default:
                printf("请重新输入。\n");                                                     
        }
    }
    return choice;    
}

int updataMenu()
{
    teacher tmp;
    int teacherID;
    int choice;
    int choiceafterupdate=0;
    printf("请输入教师编号：");
    scanf("%d",teacherID);
    
    updataTeacherinDB(dbaccess,teacherID);
    
    while(choiceafterupdate==(1||2||0))
    {
        printf("请选择在修改后的操作：\n【1】.新增\n【2】.查询\n【3】.修改\n【0】.返回主菜单\n\n输入您的选择：");
        scanf("%d",&choiceafterupdate);
        switch(choiceafterupdate)
        {
            case(1):
                printf("开始新增教师信息\n");
                choice=1;
                break;                                            
            case(2):
                printf("开始查询教师信息\n");
                choice=4;
                break;
            case(3):
                printf("开始修改教师信息\n");
                choice=2;
                break;
            case(0):
                printf("正在返回主菜单\n");
                Sleep(3000);
                mainMenu();//重新跳出主菜单
                scanf("%d",&choice);//返回新的opt值
                break;            
            default:
                printf("请重新输入。\n");                                              
        }                
    }
    return choice;
}

int deleteMenu()
{
    int choice;
    int teacherID;
    int choiceafterdelete=0;    
    printf("请输入教师编号：");
    scanf("%d",&teacherID);
    deleteTeacherinDB(dbaccess,teacherID);
    while(choiceafterdelete==(1||2||0))
    {
        printf("请选择在删除后的操作：\n【1】.新增\n【2】.查询\n【0】.返回主菜单\n\n输入您的选择：");
        scanf("%d",&choiceafterdelete);        
        switch (choiceafterdelete)
        {
        case(1):
            printf("开始新增教师信息\n");
            choice=1;
            break;                                            
        case(2):
            printf("开始查询教师信息\n");
            choice=4;
            break;
        case(0):
            printf("正在返回主菜单\n");
            Sleep(3000);
            mainMenu();//重新跳出主菜单
            scanf("%d",&choice);//返回新的opt值
            break;            
        default:
            printf("请重新输入。\n");                                                     
        }
    }
    return choice;                
}
