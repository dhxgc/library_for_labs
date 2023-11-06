// #include <mysqld_lib.h>
#include "mysqld_lib.h"
#include <unistd.h>

int main () 
{
    init_mysql();
    connect_mysql("localhost",
                  "kkk",
                  "kkk",
                  "tests");
                  
    // __mysql_query_dml("create table `lab1_1` (id int unsigned primary key not null auto_increment, name varchar(20) not null default 'unknown', password varchar(15) not null default 'unknown');");
    __mysql_query_ddl("desc lab1_1;");
    // __mysql_query_dml("drop table jst;");

    mysql_close(mysql);
    return 0;
}
