
/**
 * hl-mongodb.cpp
 * mongodb client
 * Henry 2019-08-29
 * */

#include "hl-mongodb.h"

#define HL_MONGODB_URI "mongodb://172.16.2.70:27017/?appname=test"

HLMongoDB::HLMongoDB()
{
    init_mongo();
    client = NULL;

    options.uri = HL_MONGODB_URI;
}

HLMongoDB::~HLMongoDB()
{
    if(client)
        delete client;

    doc.Clear();
}

/* find data by filter in mongodb
 * dbname: database name
 * collname: collection name
 * filter: json format of filter
 * */
mongocxx::cursor HLMongoDB::find(const char *dbname, const char *collname, const char* filter,
                                 const mongocxx::options::find& opts)
{
    mongocxx::database db = (*client)[dbname];
    mongocxx::collection coll = db[collname];

    return coll.find(bsoncxx::from_json(filter), opts);
}


static bool sg_init_flag = false;
// init mongo
void HLMongoDB::init_mongo()
{
    if(sg_init_flag)
        return ;

    mongocxx::instance instance{};

    sg_init_flag = true;
}


// connect
int HLMongoDB::connect(const char *uri)
{
    if(client)
        delete client;

    // connect mongo
    client = new mongocxx::client(mongocxx::uri(uri));

    return 0;
}

// get int64
int64_t mongo_get_int64(bsoncxx::v_noabi::document::element ele)
{
    if(!ele) return 0;

    switch(ele.type())
    {
        case type::k_double:
            return (int64_t)ele.get_double();
            break;
        case type::k_int64:
            return (int64_t)ele.get_int64();
            break;
        case type::k_int32:
            return (int64_t)ele.get_int32();
            break;
        case type::k_utf8:
            return (int64_t)std::stol(ele.get_utf8().value.to_string());
            break;
        default:
            break;
    }

    return 0;
}

// get int32
int32_t mongo_get_int32(bsoncxx::v_noabi::document::element ele)
{
    if(!ele) return 0;

    switch(ele.type())
    {
        case type::k_double:
            return (int32_t)ele.get_double();
            break;
        case type::k_int64:
            return (int32_t)ele.get_int64();
            break;
        case type::k_int32:
            return ele.get_int32();
            break;
        case type::k_utf8:
            return std::stoi(ele.get_utf8().value.to_string());
            break;
        default:
            break;
    }

    return 0;
}

// get double
double mongo_get_double(bsoncxx::v_noabi::document::element ele)
{
    if(!ele) return 0.0;

    switch(ele.type())
    {
        case type::k_double:
            return ele.get_double();
            break;
        case type::k_int64:
            return (double)ele.get_int64();
            break;
        case type::k_int32:
            return (double)ele.get_int32();
            break;
        case type::k_utf8:
            return std::stod(ele.get_utf8().value.to_string());
            break;
        default:
            break;
    }

    return 0.0;
}

/* read options
 * filename: configure file name
 * */
int HLMongoDB::read_options(const char *filename)
{
    tinyxml2::XMLError ret = doc.LoadFile(filename);
    if(ret != tinyxml2::XML_SUCCESS)
    {
        printf("load xml file faild: %s\n", tinyxml2::XMLDocument::ErrorIDToName(ret));
        return -1;
    }
    tinyxml2::XMLElement *elem;

    elem = doc.FirstChildElement("Configuration");
    if(!elem) return -1;
    elem = elem->FirstChildElement("mongodb");
    if(!elem) return -1;

    elem->QueryStringAttribute("uri", &options.uri);

    return 0;
}
