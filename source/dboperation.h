// 防止被重复包含的头
#ifndef DBOPERATION_H
#define DBOPERATION_H

// 包含必要的头文件
#include "includeheaders.h"

void checkFileProi(); // 检测数据库是否可以被访问
sqlite3* connectDB(); // 连接数据库，并判断是否存在对应的数据表
int isTableExistCallback(void *,int nCount,char **cValue,char **cName); // 判断数据表存在时的回调函数
void addTeacherToDB(sqlite3 *teacherdb,const teacher *t); // 将参数传入的教师数据写入数据库
void findTeacherinDB_TeacherID(sqlite3 *teacherdb,int id); // 查找教师信息函数，利用教师id
void findTeacherinDB_TeacherName(sqlite3 *teacherdb,const char *name); // 利用教师名字（汉字）查找教师信息
void findTeacherinDB_PhoneNumber(sqlite3 *teacherdb,const char *phone); // 利用教师电话号码查找教师信息
int findTeacherCallback(void *ret,int nCount,char **cValue,char **cName); // 当找到教师信息时的回调函数

#endif