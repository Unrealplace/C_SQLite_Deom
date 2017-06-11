//
//  main.c
//  C_SQLite_Demo
//
//  Created by LiYang on 2017/6/10.
//  Copyright © 2017年 LiYang. All rights reserved.
//

#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>

sqlite3 * db;
char * zErrMsg =0;
int rc;
char * sql;
const char* data = "Callback function called";

static int callBack(void *NotUsed,int argc,char ** argv,char ** azColName){

    int i ;
    for (i =0; i<argc; i++) {
        printf("%s = %s\n",azColName[i],argv[i]?argv[i]:"NULL");
    }
    printf("\n");//
    return 0;
    
}

//int (*callback)(void *, int, char **, char **)
//在我们开始讲解获取记录的实例之前，让我们先了解下回调函数的一些细节，这将在我们的实例使用到。这个回调提供了一个从 SELECT 语句获得结果的方式。它声明如下：
//typedef int (*sqlite3_callback)(
//void*,    /* Data provided in the 4th argument of sqlite3_exec() */
//int,      /* The number of columns in row */
//char**,   /* An array of strings representing fields in the row */
//char**    /* An array of strings representing column names */
//);
//如果上面的回调在 sqlite_exec() 程序中作为第三个参数，那么 SQLite 将为 SQL 参数内执行的每个 SELECT 语句中处理的每个记录调用这个回调函数。


//open database//

void openDB(){

    rc = sqlite3_open("/Users/liyang/Desktop/DataBase/test.db", &db);
    if (rc) {
        fprintf(stderr, "can't open database:%s\n",sqlite3_errmsg16(db));
    }else{
    
        fprintf(stdout, "open database successfully\n");
    }
    
}
void closeDB(){

    sqlite3_close(db);
  
}

void createTable(){

    sql = "create table CTestTable    ("\
             "id int primary key not null,"\
             "name   text           not null,"\
             "age int not null,"\
             "address char(50),"\
             "salary real);";
    rc = sqlite3_exec(db, sql, callBack, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Table created successfully\n");
    }
    closeDB();

    
}

/**
 增加数据
 */
void insertData(){

    openDB();
    /* Create SQL statement */
    sql = "INSERT INTO CTestTable (ID,NAME,AGE,ADDRESS,SALARY) "  \
    "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
    "INSERT INTO CTestTable (ID,NAME,AGE,ADDRESS,SALARY) "  \
    "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
    "INSERT INTO CTestTable (ID,NAME,AGE,ADDRESS,SALARY)" \
    "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
    "INSERT INTO CTestTable (ID,NAME,AGE,ADDRESS,SALARY)" \
    "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";
    
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callBack, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Records created successfully\n");
    }

    closeDB();
    
}

/**
 查询数据
 */
void selectData(){

    openDB();
    /* Create SQL statement */
    sql = "SELECT * from CTestTable";
    
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callBack, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Operation done successfully\n");
        
    }
    closeDB();
}


/**
 更新数据
 */
void updateData(){

    openDB();
    /* Create merged SQL statement */
    sql = "UPDATE CTestTable set SALARY = 25000.00 where ID=1; " \
    "SELECT * from CTestTable";
    
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callBack, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Operation done successfully\n");
    }
    closeDB();
    
}

/**
 删除数据
 */
void deleteData(){

    openDB();
    /* Create merged SQL statement */
    sql = "DELETE from CTestTable where ID=2; " \
    "SELECT * from CTestTable";
    
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callBack, (void*)data, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Operation done successfully\n");
    }
    closeDB();
}

int main(int argc, const char * argv[]) {
  
    
    openDB();
    createTable();
    insertData();
    selectData();
    updateData();
    deleteData();
    
    
    
    return 0;
}
