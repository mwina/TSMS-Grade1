#ifndef DBOPERATION_H
#define DBOPERATION_H

#include "includeheaders.h"
#include "datastruct.h"
#include "sqlite3.h"

void checkFileProi();
sqlite3* connectDB();
int isTableExistCallback(void *,int nCount,char **cValue,char **cName);
void addTeacherToDB(sqlite3 *teacherdb,const teacher *t);

#endif