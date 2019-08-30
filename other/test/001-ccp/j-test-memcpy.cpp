
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _T
{
    char *s1;
    char *s2;
} T;

int main()
{
    T *a = (T*)malloc(sizeof(T));
    a->s1 = (char*)malloc(16);
    a->s2 = (char*)malloc(16);

    sprintf(a->s1, "%s", "abcdefg");
    sprintf(a->s2, "%s", "hijklmn");

    for(int i = 0; i < 1000; i ++)
    {
        T *b = (T*)malloc(sizeof(T));
        memcpy(b, a, sizeof(T));
    
        printf("%s, %s\n", b->s1, b->s2);
    }

    return 0;
}
