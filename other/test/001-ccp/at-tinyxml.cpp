
#include <stdio.h>

#include "tinyxml2.h"

int main()
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError ret = doc.LoadFile("123.xml");

    if(ret != tinyxml2::XML_SUCCESS)
    {
        printf("load xml file faild: %s\n", tinyxml2::XMLDocument::ErrorIDToName(ret));
        return -1;
    }
    tinyxml2::XMLElement *elem, *elem2;
    const char *p = "default";
    uint32_t v = 0;

    elem = doc.FirstChildElement("config");
    if(!elem) return -1;

    if((elem2 = elem->FirstChildElement("opt1")))
    {
        elem2->QueryStringAttribute("name1", &p);
        elem2->QueryUnsignedAttribute("name2", &v);
        printf("opt1: %s-%d\n", p, v);
    }

    if((elem2 = elem->FirstChildElement("opt2")))
    {
        elem2->QueryStringAttribute("name1", &p);
        elem2->QueryUnsignedAttribute("name2", &v);
        printf("opt2: %s-%d\n", p, v);
    }

    if((elem = doc.FirstChildElement("opt")))
    {
        elem->QueryStringAttribute("name1", &p);
        elem->QueryUnsignedAttribute("name2", &v);
        printf("opt: %s-%d\n", p, v);

        if((elem2 = elem->FirstChildElement("opt3")))
        {
            elem2->QueryStringAttribute("name1", &p);
            elem2->QueryUnsignedAttribute("name2", &v);
            printf("opt3: %s-%d\n", p, v);
        }

        if((elem2 = elem->FirstChildElement("opt4")))
        {
            elem2->QueryStringAttribute("name1", &p);
            elem2->QueryUnsignedAttribute("name2", &v);
            printf("opt4: %s-%d\n", p, v);
        }
    }

    return 0;
}
