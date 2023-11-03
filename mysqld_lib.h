#ifndef MYSQL_LIB_MAIN
#define MYSQL_LIB_MAIN 1

#include <mysql/mysql.h>
// #include <mysql/my_global.h>
#include <mysql/mysqld_error.h>
#include <mysql/errmsg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

MYSQL* mysql;
MYSQL_RES* res;
MYSQL_ROW row;
MYSQL_FIELD* field;
int i;
const char* str_row = {"%-20s\t"};
const char* str_field = {"%-20s\t"};

void show_get_data() {
    printf ("SHOW GET DATA OK\n");
    printf ("\n\tResult: %li row\n\n", mysql_num_rows(res));
    i = 0;
    while (i < mysql_num_fields(res)) {
        field = mysql_fetch_field_direct(res, i);
        // printf ("\t%15s|", field->name);
        printf (str_field, field->name);
        i++;
    }
    printf ("\n\t\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        for (i = 0; i < mysql_num_fields(res); i++) {
            // printf ("\t%15s|", row[i]);
            printf (str_row, row[i]);
        }
        printf ("\n");
    }
    mysql_free_result(res);
}

void error_info () {
        printf("Error connect\n");
        printf("error N: %i %s\n", mysql_errno(mysql), mysql_error(mysql));
}

void show_result () {
    res = mysql_store_result(mysql); // ???
    if (res == NULL)
        printf ("\n\tres == NULL\t Error get data!\n");
    else {
        printf ("SHOW RESULT OK\n");
        // max_weight();
        if (mysql_num_rows(res) > 0) {
            show_get_data();
        }
        else {
            printf ("\n\t No Data! code = -sr\n");
        }

        printf ("\n\tEND OF THE QUERY\n\n");
        // sleep(5);
        getchar();
        system("clear");
    }
}

void init_mysql () {
    mysql = mysql_init(NULL);
    if (mysql == NULL) printf ("\n\tError init!\n"); 
    else printf ("\n\tinit OK!\n");
}


/// @brief подключение к нужной БД
void connect_mysql () {
    if (!mysql_real_connect(mysql,
                    "localhost",
                    "mysql_vs",
                    "password",
                    "test",
                    0,
                    NULL,
                    0
                    )) error_info();
    else printf ("\tConnection OK!\n");
}

void __mysql_query(const char query[]) {
    if (mysql_query(mysql, query) != 0) {
        error_info();
    } 
    else {
        show_result();
    }
}

#endif