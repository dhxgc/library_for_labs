#include "mysqld_lib.h"
#include <unistd.h>

int main () 
{
    init_mysql();
    connect_mysql();

    __mysql_query("select * from users;");
    __mysql_query("desc users;");

    mysql_close(mysql);
    return 0;
}