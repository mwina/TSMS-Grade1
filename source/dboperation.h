#ifndef DBOPERATION_H
#define DBOPERATION_H

#include "includeheaders.h"

void checkFileProi();
sqlite3* connectDB();
int isTableExistCallback(void *,int nCount,char **cValue,char **cName);
void addTeacherToDB(sqlite3 *teacherdb,const teacher *t);
void findTeacherinDB_TeacherID(sqlite3 *teacherdb,int id);

#endif