#include <bits/stdc++.h>
using namespace std;


struct f
{
    int now;
    int pre;
    int value;
    f(int a, int b, int c):now(a), pre(b), value(c){}
};


class LGraph
{
    vector<vector<pair<int, int> > > a;
    int n, e;
    bool *visited;
    queue<int> ds;
public:
    LGraph(int i, int j):n(i), e(j)
    {
        a.resize(n);
        visited = new bool [n];
        printf("请依次输入%d条边，形如（i，j，v）\n", e);
        for (int i = 0; i < e; ++i)
        {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            a[x].push_back(make_pair(y, z));
        }
    }
    ~LGraph(){if (visited) delete [] visited;}
    int search(int x, int y)
    {
        for (int i = 0; i < a[x].size(); ++i)
            if (a[x][i].first == y) return a[x][i].second;
        return 1 << 30;
    }
    void insert(int x, int y, int z)
    {
        scanf("%d%d%d", &x, &y, &z);
        a[x].push_back(make_pair(y, z));
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
        for (int i = 0; i < a[s].size(); ++i)
        {
            int t = a[s][i].first;
            if (!visited[t])
            {
                visited[t] = 1;
                ds.push(t);
                dfs(t);
                ds.pop();
                visited[t] = 0;
            }
        }
    }

};

int main()
{
    int n, e;
    printf("请输入地点个数n和道路条数e：");
    scanf("%d%d", &n, &e);
    LGraph L(n, e);
    L.init();
    L.dfs(0);
    return 0;
}