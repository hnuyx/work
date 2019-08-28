
#include <stdio.h>
#include <stdint.h>
#include <vector>

#pragma pack(push, 4)
typedef struct _T
{
    uint32_t a;
    uint32_t b;
    uint32_t c;
} T;
#pragma pack(pop)

std::vector<T> get()
{
    std::vector<T> ts;
    ts.resize(10);

    return ts;
}

int main()
{
    std::vector<T> ts = get();
    printf("size %lu\n", sizeof(ts));

    for (int i = 0; i < ts.size(); i++)
    {
        printf("%u-%u-%u\n", ts[i].a, ts[i].b, ts[i].c);
    }

    return 0;
}
