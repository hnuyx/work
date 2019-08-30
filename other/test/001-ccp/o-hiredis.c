
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

#include <hiredis.h>

#define CHECK_RET_RETURN(r,e,s,t) \
    if (r == e) { printf("%s\n", s); return t; }

#define ADJUST_TIME(se,ue,us) \
    if (ue < us) { us += 1000000; se -= 1; }

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
    reply = redisCommand(ctx,"AUTH ADbugA2JU6yALx");
#else
    reply = redisCommand(ctx,"AUTH MyRedis1@2");
#endif
    CHECK_RET_RETURN(reply, NULL, "auth failed", -1);
    printf("Auth result: %s\n", reply->str);
    freeReplyObject(reply);

    // select database
#if REAL_DATA
    reply = redisCommand(ctx,"SELECT 17");
#else
    reply = redisCommand(ctx,"SELECT 9");
#endif
    printf("select database result: %s\n", reply->str);
    freeReplyObject(reply);

    char **cmdargv = (char **)malloc(sizeof(char *)*10000);
    for(int i = 0; i < 10000; i ++)
    {
        cmdargv[i] = (char *)malloc(sizeof(char) * 64);
    }

    //int anum[] = {1, 10, 30, 50, 70, 100, 200, 300, 400, 500, 600, 10000};
    int anum[] = {2};
    for (int i = 0; i < sizeof(anum)/4; i ++)
    {
        int num = anum[i];
        printf("num %d-------------------------\n", num);
        // query 1m kline
        gettimeofday(&start, NULL);
        for(int j = 0; j < num; j ++)
        {
#if REAL_DATA
            reply = redisCommand(ctx,"LRANGE onekline-600027.SS-0 0 -1 ");
#else
            reply = redisCommand(ctx,"SET a 1 ");
#endif
            freeReplyObject(reply);
        }
        gettimeofday(&end, NULL);
        ADJUST_TIME(end.tv_sec, end.tv_usec, start.tv_usec);
        printf("redis query         %d times cost %u.%u s\n", num, (end.tv_sec - start.tv_sec), (end.tv_usec - start.tv_usec));
    
        // query 1m kline -- pipeline
        gettimeofday(&start, NULL);
        for(int j = 0; j < num; j ++)
        {
#if REAL_DATA
            //redisAppendCommand(ctx,"LRANGE onekline-600027.SS-0 0 -1 ");
            snprintf(cmdargv[j], 64, "%s", "LRANGE onekline-600027.SS-0 0 -1");
#else
            redisAppendCommand(ctx,"SET a 1");
#endif
        }
        int ret = redisAppendCommandArgv(ctx, num, cmdargv, NULL);
        if (ret == REDIS_OK)
            printf("redisAppendCommandArgv ok\n");
        else
            printf("redisAppendCommandArgv error: %s\n", ctx->errstr);
        ret = redisGetReply(ctx, (void**)&reply);
        if (ret == REDIS_OK)
            printf("redisGetReply ok\n");
        else
            printf("redisGetReply error: %s\n", reply->str);
        printf("reply str: %s\n", reply->str);
        freeReplyObject(reply);
        gettimeofday(&end, NULL);
        ADJUST_TIME(end.tv_sec, end.tv_usec, start.tv_usec);
        printf("redis pipline-query %d times cost %u.%u s\n", num, (end.tv_sec - start.tv_sec), (end.tv_usec - start.tv_usec));
    }

    for (int i = 0; i < 10000; i ++)
    {
        free(cmdargv[i]);
    }
    free(cmdargv);

    redisFree(ctx);
    return 0;
}
