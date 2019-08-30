
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

    if(NULL == mysql_real_connect(&mysql,
                                  "level2-parse-rds.mysql.rds.aliyuncs.com",
                                  "root",
                                  "UUd9nAQOuCvwt2wil@DL",
                                  "mysql_minute",
                                  3306,
                                  NULL, 0))
    {
        printf("connect mysql failed\n");
        return -1;
    }

    //const char *sql = "select code,date,name, BuyOrderNum as buyordernum,SellOrderNum as sellordernum,iBuy as ibuy, iBuyVol as ibuyvol,iBuyOrderNum as ibuyordernum,iSell as isell, iSellVol as isellvol,iSellOrderNum as isellordernum,pBuy as pbuy,pBuyVol as pbuyvol,pBuyOrderNum as pbuyordernum,pSell as psell, pSellVol as psellvol,pSellOrderNum as psellordernum from l2data_2019 where date = '20190822' order by code;";
    const char *sql = "select code,date,name, BuyOrderNum,SellOrderNum,iBuy, iBuyVol,iBuyOrderNum,iSell, iSellVol,iSellOrderNum,pBuy,pBuyVol,pBuyOrderNum,pSell, pSellVol,pSellOrderNum from l2data_2018 order by date, code;";
    //const char *sql = "select distinct code from l2data_2019 where date = '20190822';";

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
        //break;
    }


    return 0;
}
