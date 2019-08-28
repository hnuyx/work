
#include <stdio.h>

#include "tinyxml2.h"

int main()
{
    const char *filename = "1.xml";

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError ret = doc.LoadFile(filename);
    if(ret != tinyxml2::XML_SUCCESS)
    {
        printf("load xml file faild: %s\n", tinyxml2::XMLDocument::ErrorIDToName(ret));
        return ret;
    }

    tinyxml2::XMLElement *elem = doc.FirstChildElement("Configuration");
    tinyxml2::XMLElement *elem2 = elem->FirstChildElement("KLine")->FirstChildElement("KLineStrInfo");
    int base = 10;
    elem2->FirstChildElement("one")->QueryIntAttribute("bases", &base);
    printf("base %lu\n", base);
    elem2->FirstChildElement("one")->QueryIntAttribute("base", &base);
    printf("base %lu\n", base);

    return 0;
}
