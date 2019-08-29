
/**
 * hl-mongodb.h
 * mongodb client
 * Henry 2019-08-29
 * */

#ifndef __HL_MONGODB_H__
#define __HL_MONGODB_H__

#include <stdio.h>
#include <stdint.h>

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

#include "tinyxml2.h"

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::basic::make_document;
using bsoncxx::builder::basic::kvp;
using bsoncxx::v_noabi::type;

#pragma pack(push, 4)
typedef struct _HLMongodbOpt
{
    const char *uri;
} HLMongodbOpt;
#pragma pack(pop)

class HLMongoDB
{
public:
    HLMongoDB();
    ~HLMongoDB();

    /* find data by filter in mongodb
     * dbname: database name
     * collname: collection name
     * filter: json format of filter
     * */
    mongocxx::cursor find(const char *dbname, const char *collname, const char* filter,
                          const mongocxx::options::find& opts = mongocxx::options::find());

    // init mongo
    static void init_mongo();

    // connect
    int connect(const char *uri);

    /* read options
     * filename: opstions file-name
     * */
    int read_options(const char *filename);

    // options
    HLMongodbOpt options;
private:
    mongocxx::client *client;

    // xml 
    tinyxml2::XMLDocument doc;

};

// get int64
int64_t mongo_get_int64(bsoncxx::v_noabi::document::element ele);
// get int32
int32_t mongo_get_int32(bsoncxx::v_noabi::document::element ele);
// get double
double mongo_get_double(bsoncxx::v_noabi::document::element ele);

#endif
