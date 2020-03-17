
#include <stdio.h>

#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/string/to_string.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

int main()
{
    mongocxx::instance instance{}; 

    //mongocxx::uri uri("mongodb://10.47.51.126:37017/?appname=find-trend");
    //mongocxx::uri uri("mongodb://10.46.64.71:37017/?appname=find-trend");
    //mongocxx::uri uri("mongodb://10.47.51.127:37017/?appname=find-trend");
    mongocxx::uri uri("mongodb://10.24.25.90:27017/?appname=find-trend");
    mongocxx::client client(uri);
    mongocxx::client client2(uri);

    mongocxx::database db = client["stock"];
    mongocxx::collection coll = db["trend"];

    mongocxx::database db2 = client2["stock"];
    mongocxx::collection coll2 = db2["trend"];

    double close, pre_close;
    uint64_t date, time, amount, balance;

    auto sort = bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("date", 1));
    mongocxx::options::find opts;
    opts = mongocxx::options::find{};
    opts.sort(sort.view());

    //const char *filter = "{\"date\": {\"$lte\": \"20191231\", \"$gte\": \"20190101\"}, \"code\": \"002515.SZ\"}";
    //auto cursor = coll.find(bsoncxx::from_json(filter), opts);

    char stockid[10];
    char filter[512];
    FILE *fp = fopen("/data/quant/kline/stocks", "r");
    mongocxx::cursor ct;
    while(EOF != fscanf(fp, "%s", stockid))
    {
        snprintf(filter, 512, "{\"date\": {\"$lte\": \"20191231\", \"$gte\": \"20190101\"}, \"code\": \"%s\"}", stockid);
        mongocxx::cursor cursor = coll.find(bsoncxx::from_json(filter), opts);
        mongocxx::cursor cursor2 = coll2.find(bsoncxx::from_json(filter), opts);
        for(auto doc1 = cursor.begin(), doc2 = cursor2.begin(); doc1 != cursor.end(); doc1 ++, doc2 ++)
        {
            auto doc = *doc1;
            date = std::stoll(doc["date"].get_utf8().value.to_string());
            pre_close = std::stod(doc["preclose_px"].get_utf8().value.to_string());
            doc = *doc2;
            auto array = doc["data"][10];
            time = std::stoll(array[0].get_utf8().value.to_string());
            close = std::stod(array[1].get_utf8().value.to_string());
            balance = array[6].get_int64();
            amount = array[7].get_int64();

            if(date != time / 10000)
                printf("%s %lu %lu %f %f %lu %lu\n", stockid, date, time, close, pre_close, balance, amount);
        }
    }
    fclose(fp);

    return 0;
}
