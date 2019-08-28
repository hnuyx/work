#include <stdio.h>
#include <queue>

int coins[] = {1, 7, 11};

#define MAX 10000
int ret[MAX] = {0};

#define min(a, b)  (a) < (b) ? (a) : (b)

int getN(int n, int size)
{
    if(n >= MAX)
        return 0;

    std::queue<int> q;
    for(int i = 0; i < size; i ++)
    {
        ret[coins[i]] = 1;
        q.push(coins[i]);
    }

    int f, t;
    while(q.size() > 0)
    {
        int f = q.front();
        for(int i = 0;i < size; i ++)
        {
            t = f + coins[i];
            if(t < MAX && t <= n)
            {
                if(ret[t] == 0)
                    ret[t] = ret[f] + 1;
                else
                    ret[t] = min(ret[t], ret[f]+1);
    
                q.push(t);
            }
        }
        q.pop();
    }

    return ret[n];
}

int main()
{
    int size = sizeof(coins)/sizeof(int);
    int ret = getN(14, size);
    printf("%d\n", ret);

    return 0;
}
