
/**
 * hl-redis.cpp
 * redis
 * Henry 2019-08-29
 * */

#include "hl-redis.h"

// redis info: ip, port, password, database
#define HL_REDIS_HOST_IP            "127.0.0.1"
#define HL_REDIS_HOST_PORT          6379
#define HL_REDIS_HOST_PASSWORD      "password"
#define HL_REDIS_HOST_DATABASE      1

HLRedis::HLRedis()
{

    //init options
    options.ip = HL_REDIS_HOST_IP;
    options.port = HL_REDIS_HOST_PORT;
    options.password = HL_REDIS_HOST_PASSWORD;
    options.database = HL_REDIS_HOST_DATABASE;
}

HLRedis::~HLRedis()
{
    if(ctx)
        redisFree(ctx);

    doc.Clear();
}

/* connect to redis
 * */
redisContext* HLRedis::connect()
{
    // connect to redis
    redisContext *ctx = redisConnect(options.ip, options.port);
    if(!ctx)
    {
        printf("connect to redis %s:%d failed\n", options.ip, options.port);
        return NULL;
    }
    else if (ctx->err)
    {
        printf("connect to redis %s:%d error: %s\n", options.ip, options.port, ctx->errstr);
        redisFree(ctx);
        return NULL;
    }

    redisReply *reply;
    char cmd[HL_REDIS_CMD_MAX_LENGTH];

    // auth
    snprintf(cmd, HL_REDIS_CMD_MAX_LENGTH, "AUTH %s", options.password);
    reply = (redisReply *)redisCommand(ctx,cmd);
    if(reply == NULL)
    {
        printf("auth failed\n");
        redisFree(ctx);
        return NULL;
    }
    printf("Auth result: %s\n", reply->str);
    freeReplyObject(reply);

    // select database
    snprintf(cmd, HL_REDIS_CMD_MAX_LENGTH, "SELECT %d", options.database);
    reply = (redisReply *)redisCommand(ctx, cmd);
    printf("select database result: %s\n", reply->str);
    freeReplyObject(reply);

    return ctx;
}

/* read options
 * filename: opstions file-name
 * */
int HLRedis::read_options(const char *filename)
{
    tinyxml2::XMLError ret = doc.LoadFile(filename);
    if(ret != tinyxml2::XML_SUCCESS)
    {
        printf("load xml file faild: %s\n", tinyxml2::XMLDocument::ErrorIDToName(ret));
        return -1;
    }

    tinyxml2::XMLElement *elem;

    elem = doc.FirstChildElement("Configuration");
    if(!elem) return 0;
    elem = elem->FirstChildElement("redis");
    if(!elem) return 0;

    elem->QueryStringAttribute("redisHostIP", &options.ip);
    elem->QueryIntAttribute("redisHostPort", &options.port);
    elem->QueryStringAttribute("redisHostPassword", &options.password);
    elem->QueryIntAttribute("redisHostDatabase", &options.database);

    return 0;
}

