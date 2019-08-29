
#include <stdio.h>

#define TEST_MYSQL           1
#define TEST_REDIS           1
#define TEST_MONGODB         1

#if TEST_MYSQL
#include "hl-mysql.h"
#endif

#if TEST_REDIS
#include "hl-redis.h"
#endif

#if TEST_MONGODB
#include "hl-mongodb.h"
#endif

#if TEST_MYSQL
void test_hl_mysql()
{
    HLMysql mysql;
    mysql.read_options("db.xml");
}
#endif

#if TEST_REDIS
void test_hl_redis()
{
    HLRedis redis;
    redis.read_options("db.xml");
}
#endif

#if TEST_MONGODB
void test_hl_mongodb()
{
    HLMongoDB mdb;
    mdb.read_options("db.xml");
}
#endif

int main()
{
#if TEST_MYSQL
    test_hl_mysql();
#endif
#if TEST_REDIS
    test_hl_redis();
#endif
#if TEST_MONGODB
    test_hl_mongodb();
#endif

    return 0;
}
