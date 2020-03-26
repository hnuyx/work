
#include <stdio.h>
#include <string.h>

#include <mysql/mysql.h>

int main()
{
    MYSQL mysql;
    memset(&mysql, 0, sizeof(mysql));
    mysql_close(&mysql);

    if(NULL == mysql_init(&mysql))
    {
        printf("mysql init failed\n");
        return -1;
    }

    if(NULL == mysql_real_connect(&mysql, "127.0.0.1", "username", "password", "dbname", 3306, NULL, 0))
    {
        printf("connect mysql failed\n");
        return -1;
    }

    const char *sql = "select * from table;";

    printf("query: %d\n", mysql_query(&mysql, sql));
    MYSQL_RES *ret = mysql_store_result(&mysql);
    if(!ret)
    {
        printf("mysql store result failed\n");
        return -1;
    }

    MYSQL_ROW row;
    MYSQL_FIELD *field;

    int num = mysql_num_fields(ret);
    for(int i = 0; i < num; i ++)
    {
        field = mysql_fetch_field_direct(ret, i);
        printf("%s ", field->name);
    }
    printf("\n");

    while(row = mysql_fetch_row(ret))
    {
        for(int i = 0; i < num; i ++)
        {
            printf("%s ", row[i]);
        }
        printf("\n");
    }

    return 0;
}
