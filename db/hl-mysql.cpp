
/**
 * hl-mysql.cpp
 * mysql data
 * Henry 2019-08-29
 * */

#include <stdio.h>
#include <string.h>

#include "hl-mysql.h"

#define HL_MYSQL_HOST              "127.0.0.1"
#define HL_MYSQL_USER              "usr"
#define HL_MYSQL_PASSWD            "password"
#define HL_MYSQL_DATABASE          "databasename"
#define HL_MYSQL_PORT              3306

HLMysql::HLMysql()
{
    memset(&mysql, 0, sizeof(mysql));
    options.host = HL_MYSQL_HOST;
    options.user = HL_MYSQL_USER;
    options.passwd = HL_MYSQL_PASSWD;
    options.db = HL_MYSQL_DATABASE;
    options.port = HL_MYSQL_PORT;

    is_connected = false;
}

HLMysql::~HLMysql()
{
    if(is_connected)
        mysql_close(&mysql);

    doc.Clear();
}

/* connect to mysql
 * host: mysql host
 * user: mysql user
 * passwd: password of mysql user
 * db: database
 * port mysql port
 * */
int HLMysql::connect(const char *host, const char *user, const char *passwd, const char *db, uint32_t port)
{
    if(is_connected)
        return 0;

    if(NULL == mysql_init(&mysql))
    {
        printf("mysql init failed\n");
        return -1;
    }

    if(NULL == mysql_real_connect(&mysql, host, user, passwd, db, port, NULL, 0))
    {
        printf("connect mysql failed\n");
        return -1;
    }

    // record connection info
    options.host = host;
    options.user = user;
    options.passwd = passwd;
    options.db = db;
    options.port = port;
    is_connected = true;

    return 0;
}

int HLMysql::reconnect(const char *host, const char *user, const char *passwd, const char *db, uint32_t port)
{
    // close old mysql first
    if(is_connected)
    {
        mysql_close(&mysql);
        is_connected = false;
    }

    return connect(host, user, passwd, db, port);
}

/* query mysql
 * sql: sql command
 * */
MYSQL_RES* HLMysql::query(const char *sql)
{
    if(!is_connected)
    {
        int ret = connect(options.host, options.user, options.passwd, options.db, options.port);
        if (ret == -1)
            return NULL;
    }

    mysql_query(&mysql, sql);
    return mysql_store_result(&mysql);
}

/* read options
 * filename: configure file name
 * */
int HLMysql::read_options(const char *filename)
{
    tinyxml2::XMLError ret = doc.LoadFile(filename);
    if(ret != tinyxml2::XML_SUCCESS)
    {
        printf("load xml file faild: %s\n", tinyxml2::XMLDocument::ErrorIDToName(ret));
        return -1;
    }
    tinyxml2::XMLElement *elem;

    elem = doc.FirstChildElement("Configuration");
    if(!elem) return -1;
    elem = elem->FirstChildElement("mysql");
    if(!elem) return -1;

    elem->QueryStringAttribute("host", &options.host);
    elem->QueryStringAttribute("user", &options.user);
    elem->QueryStringAttribute("passwd", &options.passwd);
    elem->QueryStringAttribute("database", &options.db);
    elem->QueryUnsignedAttribute("port", &options.port);

    return 0;
}
