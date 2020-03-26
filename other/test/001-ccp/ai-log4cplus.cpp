#include <stdio.h>

#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>

int main()
{
    std::string initFileName = "log.properties";
    log4cpp::PropertyConfigurator::configure(initFileName);
    log4cpp::Category& root = log4cpp::Category::getRoot();
    log4cpp::Category& demo = log4cpp::Category::getInstance(std::string("demo"));
    log4cpp::Category& sub = log4cpp::Category::getInstance(std::string("demo.sub"));

    for(int i = 0; i < 100; i ++)
    {
        root.error("root error");
        root.warn("root warn");
        root.errorStream() << "root stream error";
        root.warnStream() << "root stream warn";
        demo.error("demo error");
    	demo.warn("demo warn");
        demo.errorStream() << "demo stream error";
        demo.warnStream() << "demo stream warn";
        sub.error("sub error");
    	sub.warn("sub warn");
        sub.errorStream() << "sub stream error";
        sub.warnStream() << "sub stream warn";
    }

	log4cpp::Category::shutdown();

    return 0;
}
