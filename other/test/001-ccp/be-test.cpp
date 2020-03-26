


#define MAX_INT(a, b) (a) > (b) ? (a) : (b)

int func(int *a, unsigned int cnt)
{
    if (cnt == 0)
        return 0;

    int *b = (int *) malloc(cnt * sizeof(int));
    int max = a[0];
    b[0] = a[0];

    for(int i = 1; i < cnt; ++i)
    {
        b[i] = MAX_INT(a[i], b[i-1] + a[i]);
        max = MAX_INT(max, b[i]);
    }

    free(b);

    return max;
}
