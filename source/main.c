// 开始包含基本头文件
#include "includeheaders.h"
#include "datastruct.h"
#include "dboperation.h"
#include "softio.h"
#include "menu.h"

void reDirect(int opt);

// 程序入口点
int main()
{
    checkFileProi(); // 先检查数据文件状态
    connectDB();
    showWelcome();
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
        case 0: // 用户选择退出
            printf("程序将于5秒钟后退出。");
            Sleep(5000); // 等待5秒
            exit(0); // 强制退出程序
        case 1:
            teacher t;
            inputTeacher(&t);
            addTeachertoFile(&t);
            system("pause");
            break;
        case 2:

        case 3:

        case 4:

        default: // 输入不同于以上所有情况的操作符
            printf("无法识别的操作符，请重新输入。");
            break; // break后回到主菜单
    }
}