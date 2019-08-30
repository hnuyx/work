
/**
 * hl-redis.h
 * redis
 * Henry 2019-08-29
 * */

#ifndef __HL_REDIS_H__
#define __HL_REDIS_H__

#include <hiredis.h>
#include "tinyxml2.h"


#define HL_REDIS_CMD_MAX_LENGTH             256

#pragma pack(push, 4)
typedef struct _HLRedisOpt
{
    const char *ip;
    const char *password;
    int port;
    int database;
} HLRedisOpt;
#pragma pack(pop)

class HLRedis
{
public:
    HLRedis();
    ~HLRedis();

    /* connect to redis
     * */
    redisContext* connect();

    /* read options
     * filename: opstions file-name
     * */
    int read_options(const char *filename);

    // options
    HLRedisOpt options;

private:
    redisContext *ctx;

    // xml 
    tinyxml2::XMLDocument doc;
};

#endif
