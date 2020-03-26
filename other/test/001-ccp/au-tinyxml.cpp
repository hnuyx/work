
#include <stdio.h>

#include "tinyxml2.h"

int main()
{
    tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument();

    doc->InsertFirstChild(doc->NewComment("doc comment"));
    tinyxml2::XMLElement *elem = doc->NewElement("config");
    tinyxml2::XMLElement *elem2 = doc->NewElement("opt1");
    //elem->InsertFirstChild(doc->NewComment("config comment"));
    elem2->SetAttribute("name1", "value1");
    elem2->SetAttribute("name2", 333);
    elem->InsertFirstChild(elem2);
    elem2 = doc->NewElement("opt2");
    elem2->SetAttribute("name1", "value2");
    elem2->SetAttribute("name2", 666);
    elem->InsertEndChild(elem2);
    doc->InsertEndChild(elem);

    elem = doc->NewElement("opt");
    doc->InsertEndChild(elem);
    elem2 = doc->NewElement("opt3");
    elem->InsertFirstChild(elem2);
    elem2->SetAttribute("name1", "value3");
    elem2->SetAttribute("name2", 999);
    elem2->SetText("opt-3");
    elem2 = doc->NewElement("opt4");
    elem->InsertEndChild(elem2);
    elem2->SetAttribute("name1", "value4");
    elem2->SetAttribute("name2", 888);
    elem2->SetValue("opthello");

    doc->SaveFile("456.xml");

    return 0;
}
