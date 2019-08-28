
#include <stdio.h>

int find_n(int *a, int cnt, int n, bool is_lower)
{
    int l = 0, r = cnt - 1, m = 0;

    while(l <= r)
    {
        m = (l + r) / 2;
        if (a[m] > n)
            r = m - 1;
        else if (a[m] < n)
            l = m + 1;
        else
            return m;
    }

    return (is_lower ? l : r);
}

int main()
{
    int a[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120};

    printf("%d\n", find_n(a, 12, 0, true));
    printf("%d\n", find_n(a, 12, 0, false));
    printf("%d\n", find_n(a, 12, 5, true));
    printf("%d\n", find_n(a, 12, 5, false));
    printf("%d\n", find_n(a, 12, 15, true));
    printf("%d\n", find_n(a, 12, 15, false));
    printf("%d\n", find_n(a, 12, 25, true));
    printf("%d\n", find_n(a, 12, 25, false));
    printf("%d\n", find_n(a, 12, 35, true));
    printf("%d\n", find_n(a, 12, 35, false));
    printf("%d\n", find_n(a, 12, 45, true));
    printf("%d\n", find_n(a, 12, 45, false));
    printf("%d\n", find_n(a, 12, 55, true));
    printf("%d\n", find_n(a, 12, 55, false));
    printf("%d\n", find_n(a, 12, 65, true));
    printf("%d\n", find_n(a, 12, 65, false));
    printf("%d\n", find_n(a, 12, 75, true));
    printf("%d\n", find_n(a, 12, 75, false));
    printf("%d\n", find_n(a, 12, 85, true));
    printf("%d\n", find_n(a, 12, 85, false));
    printf("%d\n", find_n(a, 12, 95, true));
    printf("%d\n", find_n(a, 12, 95, false));
    printf("%d\n", find_n(a, 12, 105, true));
    printf("%d\n", find_n(a, 12, 105, false));
    printf("%d\n", find_n(a, 12, 115, true));
    printf("%d\n", find_n(a, 12, 115, false));
    printf("%d\n", find_n(a, 12, 125, true));
    printf("%d\n", find_n(a, 12, 125, false));
    printf("%d\n", find_n(a, 12, 135, true));
    printf("%d\n", find_n(a, 12, 135, false));

    return 0;
}

