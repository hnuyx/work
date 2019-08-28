
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
    //mongocxx::v_noabi::instance instance{}; 
    mongocxx::instance instance{}; 

    mongocxx::uri uri("mongodb://172.16.2.70:27017/?appname=find-test");
    mongocxx::client client(uri);

    mongocxx::database db = client["kline"];
    mongocxx::collection coll = db["history_klines_1_0"];
    //mongocxx::collection coll = db["history_klines_day_0"];
    //mongocxx::collection coll = db["history_klines_year_0"];
    mongocxx::collection exrt_coll = db["exrights"];

#if 0
    //mongocxx::cursor cursor = coll.find({});
    for(auto doc : cursor)
    {
        std::cout << bsoncxx::to_json(doc) << "\n";
        break;
    }
#endif 
#if 0
    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result = coll.find_one({});
    if(maybe_result)
    {
        std::cout << bsoncxx::to_json(*maybe_result) << "\n";
    }
#endif

    double open, high, low, close, prev;
    uint64_t time, amount, balance;

    auto sort = bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("date", 1));
    mongocxx::options::find opts;
    opts = mongocxx::options::find{};
    opts.sort(sort.view());

    //auto ret = coll.find_one({});

    bsoncxx::array::view aa1;

    bool is_exrt = false;
    const char *filter_exrt = "{\"_id\": \"600572.SS\"}";
    auto ret = exrt_coll.find(bsoncxx::from_json(filter_exrt));
    for(auto doc : ret)
    {
        is_exrt = true;
        aa1 = doc["data"].get_array().value;
        
        break;
    }

    //const char *filter = "{\"date\": {\"$lte\": \"20190628\", \"$gte\": \"20190628\"}, \"stock_code\": \"600572.SS\"}";
    //const char *filter = "{\"date\": {\"$lte\": \"20190628\", \"$gte\": \"0\"}, \"stock_code\": \"600572.SS\"}";
    const char *filter = "{\"date\": {\"$lte\": \"20190628\", \"$gte\": \"0\"}, \"stock_code\": \"600290.SS\"}";
    auto cursor = coll.find(bsoncxx::from_json(filter), opts);

#if 0
    auto d = cursor.begin();
    auto aa1 = (*d)["data"].get_array().value;
    int ss1 = std::distance(aa1.begin(), aa1.end());
#endif

    for(auto doc : cursor)
    {
        //std::string s = bsoncxx::string::to_string(doc["date"].get_utf8().value);

        prev = doc["preclose_px"].get_double();

        auto array = doc["data"];
        if(array)
        {
            auto a1 = array.get_array();
            auto a2 = array.get_array().value;
            auto ele1 = array.get_array().value.begin();
            auto ele2 = array.get_array().value.end();
            auto ele3 = array.get_array().value.cbegin();
            auto ele4 = array.get_array().value.cend();
            int size = std::distance(array.get_array().value.begin(), array.get_array().value.end());
            for (auto ele : array.get_array().value)
            {
                time    = std::stoul(ele[0].get_utf8().value.to_string());
                open    = ele[1].get_double();
                high    = ele[2].get_double();
                low     = ele[3].get_double();
                close   = ele[4].get_double();
                amount  = ele[5].get_int64();
                balance = ele[6].get_int64();
                printf("%lf %lf %lf %lf %lf %lu %lu %lu\n",
                       open, high, low, close, prev, time, amount, balance);
            }
        }
        else
        {
            time    = std::stoul(doc["date"].get_utf8().value.to_string());
            open    = doc["open_px"].get_double();
            high    = doc["high_px"].get_double();
            low     = doc["low_px"].get_double();
            close   = doc["close_px"].get_double();
            amount  = doc["business_amount"].get_int64();
            balance = doc["business_balance"].get_int64();
            printf("%lf %lf %lf %lf %lf %lu %lu %lu\n",
                   open, high, low, close, prev, time, amount, balance);
        }



#if 0
        std::string s = doc["data"][0][0].get_utf8().value.to_string();
        std::cout << s << std::endl;
#endif

#if 0
        std::string s = doc["date"].get_utf8().value.to_string();
        uint64_t time = std::stoul(s);
        std::cout << bsoncxx::to_json(doc) << "\n";
        std::cout << doc["open_px"].get_double() << " "
            << doc["high_px"].get_double() <<  " "
            << doc["low_px"].get_double() <<  " "
            << doc["close_px"].get_double() <<  " "
            << doc["preclose_px"].get_double() <<  " "
            << time <<  " "
            << doc["business_amount"].get_int64() <<  " "
            << doc["business_balance"].get_int64() <<  std::endl;
#endif
        //break;
    }

    return 0;
}
