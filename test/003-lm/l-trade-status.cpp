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

    mongocxx::uri uri("mongodb://10.47.51.126:37017/?appname=trade-status-test");
    mongocxx::client client(uri);

    mongocxx::database db = client["god"];
    mongocxx::collection coll = db["stocks_reals"];

    const char *filter = "{\"trade_status\": \"STOPT\"}";
    //auto cursor = coll.find(bsoncxx::from_json(filter), opts);
    auto cursor = coll.find(bsoncxx::from_json(filter));

    for(auto doc : cursor)
    {
        std::string code = doc["_id"].get_utf8().value.to_string();
        std::string fm = doc["finance_mic"].get_utf8().value.to_string();
        if(code.size() == 6)
            code = code + "." + fm;
        std::string ts = doc["trade_status"].get_utf8().value.to_string();
        printf("%s %s\n", code.c_str(), ts.c_str());
    }

    return 0;
}
