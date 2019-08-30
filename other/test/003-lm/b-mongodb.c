
#include <mongoc.h>
#include <bson.h>
#include <stdio.h>
#include <sys/time.h>

#define ADJUST_TIME(se,ue,us) \
    if (ue < us) { us += 1000000; se -= 1; }

int main()
{
    printf("hello mongo\n");
    const char *mongo_url = "mongodb://172.16.2.70:27017/?appname=find-test";
    mongoc_client_t *client;
    mongoc_collection_t *collection;
    bson_t *filter;
    const bson_t *doc;
    mongoc_cursor_t *cursor;
    bson_error_t error;
    char *str;
    bool retval;

    mongoc_init();

    // connect to mongo
    client = mongoc_client_new(mongo_url);
    if (!client)
    {
        printf("parse mongo uri %s failed %s\n", mongo_url);
        return -1;
    }

    struct timeval start, end;
    //int anum[] = {1, 10, 30, 50, 70, 100, 200, 300, 400, 500, 600, 10000};
    int anum[] = {1};
    for (int i = 0; i < sizeof(anum)/4; i ++)
    {
        int num = anum[i];
        printf("num %d-------------------------\n", num);
        gettimeofday(&start, NULL);
        for(int j = 0; j < num; j ++)
        {
            //collection = mongoc_client_get_collection(client, "kline", "history_klines_1_0");
            collection = mongoc_client_get_collection(client, "kline", "history_klines_day_0");
            filter = bson_new_from_json((const uint8_t*)"{\"date\": {\"$lte\": \"20190628\", \"$gte\": \"20190628\"}, \"stock_code\": \"600572.SS\"}", -1, &error);
            if (!filter)
            {
                printf("get filter failed %s\n", error.message);
                return -1;
            }
            cursor = mongoc_collection_find_with_opts(collection, filter, NULL, NULL);
            //cursor = mongoc_collection_find(collection, MONGOC_QUERY_NONE,
            //                                0, 1, 0, filter, NULL, NULL);
            while (mongoc_cursor_next(cursor, &doc))
            {
                str = bson_as_canonical_extended_json(doc, NULL);
                printf("%s\n", str);
                bson_free(str);
                break;
            }
        }
        bson_destroy(filter);
        mongoc_cursor_destroy(cursor);
        mongoc_collection_destroy(collection);
        gettimeofday(&end, NULL);
        ADJUST_TIME(end.tv_sec, end.tv_usec, start.tv_usec);
        printf("mongo query %d times cost %u.%u s\n", num, (end.tv_sec - start.tv_sec), (end.tv_usec - start.tv_usec));
    }

    mongoc_client_destroy(client);
    mongoc_cleanup();

    return 0;
}
