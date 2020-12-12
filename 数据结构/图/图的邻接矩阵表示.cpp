#include <bits/stdc++.h>
using namespace std;

struct f
{
    int now;
    int pre;
    int value;
    f(int a, int b, int c):now(a), pre(b), value(c){}
};


class MGraph
{
    int *a;
    int n;
    int e;
    int v;
    queue<int> ds;
    bool *visited;
public:
    MGraph(int i, int j):n(i), e(j), v(1<<30)
    {
        a = new int [n*n];
        for (int i = 0; i < n*n; ++i)
            a[i] = v;
        visited = new bool [n];
        printf("请依次输入%d条边，形如（i，j，v）\n", e);
        for (int i = 0; i < e; ++i)
        {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            a[x*n+y] = z;
        }
    }
    ~MGraph(){if (a) delete [] a; if (visited) delete [] visited;}
    int search(int x, int y)
    {
        if (a) return a[x*n+y];
        return v;
    }
    void insert(int x, int y, int z)
    {
        scanf("%d%d%d", &x, &y, &z);
        a[x*n+y] = z;
    }
    bool del(int x, int y)
    {
        if (search(x, y) == (1 << 30))
            return false;
        a[x*n+y] = 1 << 30;
        return true;
    }
    void init()
    {
        for (int i = 0; i < n; ++i)
            visited[i] = 0;
        visited[0] = 1;
        ds.push(0);
    }
    bool check()
    {
        for (int i = 0; i < n; ++i)
            if (!visited[i]) return false;
        return true;
    }
    void dfs(int s)
    {
        if (check())
        {
            printf("%d", ds.front());
            ds.pop();
            while (!ds.empty())
            {
                printf("->%d", ds.front());
                ds.pop();
            }
            return ;
        }
        for (int i = 0; i < n; ++i)
        {
            if (a[s*n+i] != (1 << 30) && !visited[i])
            {
                visited[i] = 1;
                ds.push(i);
                dfs(i);
                ds.pop();
                visited[i] = 0;
            }
        }
    }

};




int main()
{
    int n, e;
    printf("请输入地点个数n和道路条数e：");
    scanf("%d%d", &n, &e);
    MGraph m(n, e);
    m.init();
    m.dfs(0);
    printf("\n\n");
    
    return 0;
}