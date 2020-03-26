
#include <stdio.h>
#include <list>

int main()
{
    std::list<int> a;
    for (int i = 0; i < 10; i ++)
        a.push_back(i);

    auto it = a.begin();
    while(it != a.end())
    {
        printf("%d\n", *it);
        ++ it;
    }

    return 0;
}
