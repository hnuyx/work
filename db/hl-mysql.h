
/**
 * hl-mysql.h
 * mysql data
 * Henry 2019-08-29
 * */

#ifndef __HL_MYSQL_H__
#define __HL_MYSQL_H__

#include <stdint.h>
#include <mysql/mysql.h>

#include "tinyxml2.h"

#define HL_SQL_MAX_SIZE                    512

#pragma pack(push, 4)
typedef struct _HLMysqlOpt
{
    const char *host;
    const char *user;
    const char *passwd;
    const char *db;
    uint32_t port;
} HLMysqlOpt;
#pragma pack(pop)

class HLMysql
{
public:
    HLMysql();
    ~HLMysql();

    /* connect to mysql
     * host: mysql host
     * user: mysql user
     * passwd: password of mysql user
     * db: database
     * port mysql port
     * */
    int connect(const char *host, const char *user, const char *passwd, const char *db, uint32_t port);
    int reconnect(const char *host, const char *user, const char *passwd, const char *db, uint32_t port);

    /* query mysql
     * sql: sql command
     *
     * should free the return value by mysql_free_result
     * */
    MYSQL_RES *query(const char *sql);

    /* read options
     * filename: opstions file-name
     * */
    int read_options(const char *filename);

    // options
    HLMysqlOpt options;
private:
    MYSQL mysql;

    // xml 
    tinyxml2::XMLDocument doc;

    bool is_connected;
};

#endif

