
#include <stdio.h>
#include <unordered_set>
#include <string>

int main()
{
    char buf[16];
    std::unordered_set<std::string> names;
    for(int i = 0; i < 10; i ++)
    {
        snprintf(buf, 16, "i'm %d", i);
        names.emplace(buf);
    }

    for(auto &name : names)
    {
        printf("%s\n", name.c_str());
    }

    return 0;
}
