
#include <stdio.h>

#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>

#include <bsoncxx/json.hpp>

using bsoncxx::v_noabi::type;

#define FUNDFLOW_DATA_STRUCT  \
    uint32_t little_in;       \
    uint32_t little_out;      \
    uint32_t medium_in;       \
    uint32_t medium_out;      \
    uint32_t large_in;        \
    uint32_t large_out;       \
    uint32_t super_in;        \
    uint32_t super_out;       \
    int32_t  inflow;          \
    double   ddx;             \
    double   ddy;             \
    double   tcl;             \
    double   investor_level;

typedef struct _ffd
{
    FUNDFLOW_DATA_STRUCT
} FFD;

int64_t get_int64(bsoncxx::v_noabi::document::element ele)
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

int32_t get_int32(bsoncxx::v_noabi::document::element ele)
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

double get_double(bsoncxx::v_noabi::document::element ele)
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

int main()
{
    //mongocxx::v_noabi::instance instance{};
    mongocxx::instance instance{};

    //mongocxx::uri uri("mongodb://10.46.64.71:37017");
    mongocxx::uri uri("mongodb://10.47.161.162:27017");
    mongocxx::client client(uri);

    mongocxx::database db = client["god"];
    //mongocxx::collection coll = db["fundflows"];
    mongocxx::collection coll = db["fundflow_histories"];

    auto sort = bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("date", 1));
    mongocxx::options::find opts;
    opts = mongocxx::options::find{};
    opts.sort(sort.view());

    const char *filter = "{\"stock_code\": \"300379\"}";
    //const char *filter = "{}";
    auto cursor = coll.find(bsoncxx::from_json(filter), opts);

    uint64_t time;
    std::string code, mic;
    FFD ffd = {0};
    for(auto doc : cursor)
    {
        auto ele = doc["date"];
        time               = std::stoul(doc["date"].get_utf8().value.to_string());
        code               = doc["stock_code"].get_utf8().value.to_string();
        mic                = doc["finance_mic"] ? doc["finance_mic"].get_utf8().value.to_string() : "";
        ffd.inflow         = get_int32(doc["inflow"]);
        ffd.little_in      = get_int32(doc["little_in"]);
        ffd.little_out     = get_int32(doc["little_out"]);
        ffd.medium_in      = get_int32(doc["medium_in"]);
        ffd.medium_out     = get_int32(doc["medium_out"]);
        ffd.large_in       = get_int32(doc["large_in"]);
        ffd.large_out      = get_int32(doc["large_out"]);
        ffd.super_in       = get_int32(doc["super_in"]);
        ffd.super_out      = get_int32(doc["super_out"]);
        ffd.ddx            = get_double(doc["ddx"]);
        ffd.ddy            = get_double(doc["ddy"]);
        ffd.tcl            = get_double(doc["tcl"]);
        ffd.investor_level = get_double(doc["investor_level"]);
        if(mic == "" || mic.length() == 9)
        printf("%lu %s.%s %d %u %u %u %u %u %u %u %u %f %f %f %f\n",
               time, code.c_str(), mic.c_str(),
               ffd.inflow,
               ffd.little_in, ffd.little_out,
               ffd.medium_in, ffd.medium_out,
               ffd.large_in,  ffd.large_out,
               ffd.super_in,  ffd.super_out,
               ffd.ddx, ffd.ddy,
               ffd.tcl, ffd.investor_level);
    }

    return 0;
}
