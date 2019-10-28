#include <stdio.h>

#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>

int main()
{
    std::string initFileName = "log.properties";
    log4cpp::PropertyConfigurator::configure(initFileName);
    log4cpp::Category& root = log4cpp::Category::getRoot();
    log4cpp::Category& demo = log4cpp::Category::getInstance(std::string("demo"));
    //log4cpp::Category& son = log4cpp::Category::getInstance(std::string("demo.son"));

    for(int i = 0; i < 10; i ++)
    {
        //root.error("root error");
        //root.warn("root warn");
        //root.errorStream() << "root stream error";
        //root.warnStream() << "root stream warn";
        demo.error("demo error");
    	demo.warn("demo warn");
        demo.errorStream() << "demo stream error";
        demo.warnStream() << "demo stream warn";
        //son.error("son error");
    	//son.warn("son warn");
        //son.errorStream() << "son stream error";
        //son.warnStream() << "son stream warn";
    }

	log4cpp::Category::shutdown();

    return 0;
}
