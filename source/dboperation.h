#ifndef DBOPERATION_H
#define DBOPERATION_H

#include "includeheaders.h"
#include "sqlite3.h"

void checkFileProi();
sqlite3* connectDB();
int isTableExistCallback(void *,int nCount,char **cValue,char **cName);

#endif