
#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>

#include <hiredis.h>

#define CHECK_RET_RETURN(r,e,s,t) \
    if (r == e) { printf("%s\n", s); return t; }

#define ADJUST_TIME(se,ue,us) \
    if (ue < us) { ue += 1000000; se -= 1; }

#define REAL_DATA 1

int main()
{
#if REAL_DATA
    const char *ip = "r-bp195e31d04b0dd4.redis.rds.aliyuncs.com";
#else
    const char *ip = "172.16.2.121";
#endif
    const int port = 6379;

    // connect to redis
    redisContext *ctx = redisConnect(ip, port);
    if(!ctx)
    {
        printf("connect to redis %s:%d failed\n", ip, port);
        return -1;
    }
    else if (ctx->err)
    {
        printf("connect to redis %s:%d error: %s\n", ip, port, ctx->errstr);
        redisFree(ctx);
        return -1;
    }

    redisReply *reply;
    struct timeval start, end;

    // auth
#if REAL_DATA
    reply = (redisReply *)redisCommand(ctx,"AUTH ADbugA2JU6yALx");
#else
    reply = (redisReply *)redisCommand(ctx,"AUTH MyRedis1@2");
#endif
    CHECK_RET_RETURN(reply, NULL, "auth failed", -1);
    printf("Auth result: %s\n", reply->str);
    freeReplyObject(reply);

    // select database
#if REAL_DATA
    reply = (redisReply *)redisCommand(ctx,"SELECT 17");
#else
    reply = (redisReply *)redisCommand(ctx,"SELECT 9");
#endif
    printf("select database result: %s\n", reply->str);
    freeReplyObject(reply);

    double open = 0.0, high = 0.0, low = 0.0, close = 0.0, prev = 0.0;
    uint64_t date = 0, amount = 0, balance = 0;

    //int anum[] = {1, 10, 30, 50, 70, 100, 200, 300, 400, 500, 600, 10000, 60000};
    int anum[] = {1};
    for (int i = 0; i < sizeof(anum)/4; i ++)
    {
        int num = anum[i];
        printf("num %d-------------------------\n", num);
#if 0
        // query 1m kline
        gettimeofday(&start, NULL);
        for(int j = 0; j < num; j ++)
        {
#if REAL_DATA
            //reply = (redisReply *)redisCommand(ctx,"LRANGE daykline-600027.SS-0 0 -1 ");
            reply = (redisReply *)redisCommand(ctx,"LRANGE onekline-600027.SS-0 -1 -1 ");
            //printf("%u\n", reply->elements);
            //printf("%s\n", reply->element[reply->elements-1]->str);
#else
            reply = (redisReply *)redisCommand(ctx,"SET a 1 ");
#endif
            freeReplyObject(reply);
        }
        gettimeofday(&end, NULL);
        ADJUST_TIME(end.tv_sec, end.tv_usec, start.tv_usec);
        printf("redis query         %d times cost %u.%u s\n", num, (end.tv_sec - start.tv_sec), (end.tv_usec - start.tv_usec));
#endif
    
        // query 1m kline -- pipeline
        gettimeofday(&start, NULL);
        for(int j = 0; j < num; j ++)
#if REAL_DATA
            //redisAppendCommand(ctx,"LRANGE onekline-600027.SS-0 0 -1 ");
            redisAppendCommand(ctx,"LRANGE onekline-600027.SS-0 -1 0 ");
#else
            redisAppendCommand(ctx,"SET a 1");
#endif
        for(int j = 0; j < num; j ++)
        {
            redisGetReply(ctx, (void**)&reply);
            //printf("%s\n", reply->element[0]->str);
            if(reply->elements == 1)
                sscanf(reply->element[0]->str, "%lu,%lf,%lf,%lf,%lf,%lu,%lu,",
                       &date, &open, &high, &low, &close, &amount, &balance);
            freeReplyObject(reply);
        }
        printf("%lu %lf %lf %lf %lf %lu %lu\n", date, open, high, low, close, amount, balance);
        gettimeofday(&end, NULL);
        ADJUST_TIME(end.tv_sec, end.tv_usec, start.tv_usec);
        printf("redis pipline-query %d times cost %u.%u s\n", num, (end.tv_sec - start.tv_sec), (end.tv_usec - start.tv_usec));
    }

    redisFree(ctx);
    return 0;
}
