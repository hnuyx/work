
#include <stdio.h>
#include <unordered_map>
#include <string>

int main()
{
    char buf[8]; 
    std::unordered_map<std::string, int> map;
    for(int i = 0; i < 10; i ++)
    {
        snprintf(buf, 8, "%03d", i);
        map[buf] = i;
    }

    std::unordered_map<std::string, int>::iterator it;
    for(it = map.begin(); it != map.end(); ++ it)
    {
        printf("%s--%d\n", it->first.c_str(), it->second);
    }

    return 0;
}

//void thread_func(QuantJob *job, int vm,  unordered_map<string, Bar> *bd, int tid)
