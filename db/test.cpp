
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
    /*
     * mysql.connect(....)
     * mysql.qurey(...)
     * MYSQL_RES ret = mysql.query(sql);
     * int num = mysql_num_fields(ret);
     * while((row = mysql_fetch_row(ret)))
     * {
     *     for(int i = 0; i < num; i ==)
     *     {
     *         printf("%s ", row[i]);
     *     }
     *     printf("\n");
     * }
     * mysql_free_result(ret);
     *
     * */
}
#endif

#if TEST_REDIS
void test_hl_redis()
{
    HLRedis redis;
    redis.read_options("db.xml");
    /*
     * redisReply *reply;
     *
     * redisContext *ctx = redis.connect();
     * redisAppendCommand(ctx, cmd);
     * redisGetReply(ctx, (void**)&reply);
     * freeReplyObject(reply);
     *
     * This is the reply object returned by redisCommand()
     * typedef struct redisReply {
     *     int type;                    // REDIS_REPLY_* 
     *     long long integer;           // The integer when type is REDIS_REPLY_INTEGER
     *     int len;                     // Length of string
     *     char *str;                   // Used for both REDIS_REPLY_ERROR and REDIS_REPLY_STRING
     *     size_t elements;             // number of elements, for REDIS_REPLY_ARRAY
     *     struct redisReply **element; // elements vector for REDIS_REPLY_ARRAY
     * } redisReply;
     *
     * */
}
#endif

#if TEST_MONGODB
void test_hl_mongodb()
{
    HLMongoDB mdb;
    mdb.read_options("db.xml");

    /* mdb.connect(uri);
     *
     * // sort asc
     * auto sort = make_document(kvp("id", 1));
     * mongocxx::options::find opts{};
     * opts.sort(sort.view());
     *
     * snprintf(filter_buf, LM_FILTER_MAX_SIZE, "{}", xxxxxx)
     * auto cursor = client.find(<db-name>, <collection-name>, filter_buf, opts);
     * for (auto doc : cursor)
     * {
     *     int xx = mongo_get_int32(doc['xxxxx']);
     *     auto array = doc["data"];
     *     for (auto ele : array.get_array().value)
     *     {
     *         int xxx = mongo_get_int32(ele[0]);
     *         int xxx = mongo_get_int32(ele[1]);
     *     }
     * }
     *
     * */
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
