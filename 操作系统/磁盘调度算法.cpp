#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e6 + 10;

class f
{
public:
    int id;
    int ready;
    int run;
    int start;
    int end;
    int z;
    int remain;
    bool begin;
    int wait;
    void read()
    {
        scanf("%d%d", &ready, &run);
    }
    void out()
    {
        z = end - ready;
        printf("%5d %7d %7d %7d %7d %7d/%d\n", ready, run, start, end, z, z, run);
    }
    void reset()
    {
        remain = run;
        begin = 0;
        start = end = z = 0;
        wait = 0;
    }
} p[maxn];

struct cmp1
{
    bool operator () (const f & a, const f & b)
    {
        return a.run > b.run;
    }

};

struct cmp2
{
    bool operator () (const f & a, const f & b)
    {
        return 1.0*a.wait/a.run < 1.0*b.wait/b.run;
    }
};

int n;
bool judge()
{
    for (int i = 1; i <= n; ++i)
        if (p[i].remain) return 1;
    return 0;
}

void RR()
{
    for (int i = 1; i <= n; ++i)
        p[i].reset();
    int t = 1;
    queue<int> q;
    int last = 0;
    for (int i = 0; judge(); ++i)
    {
        for (int j = 1; j <= n; ++j)
            if (p[j].ready == i) q.push(j);
        if (last && p[last].remain) q.push(last);
        last = q.front();
        p[last].remain -= t;
        if (!p[last].begin) p[last].begin = 1, p[last].start = i;
        if (!p[last].remain) p[last].end = i+1;
        q.pop();
    }
    printf("时间片轮转\n");
    printf("就绪时刻 运行时间 开始时间 结束时间 周转时间 带权周转时间\n");
    for (int i = 1; i <= n; ++i)
        p[i].out();
    double s1, s2;
    s1 = s2 = 0;
    for (int i = 1; i <= n; ++i)
        s1 += p[i].z, s2 += 1.0*p[i].z/p[i].run;
    printf("%37.2f %9.2f\n", s1/n, s2/n);
}

void FCFS()
{
    for (int i = 1; i <= n; ++i)
        p[i].reset();
    int s = 0;
    for (int i = 1; i <= n; ++i)
    {
        p[i].start = max(s, p[i].ready);
        p[i].end = p[i].start + p[i].run;
        s = p[i].end;
    }
    printf("先来先服务\n");
    printf("就绪时刻 运行时间 开始时间 结束时间 周转时间 带权周转时间\n");
    for (int i = 1; i <= n; ++i)
        p[i].out();
    double s1, s2;
    s1 = s2 = 0;
    for (int i = 1; i <= n; ++i)
        s1 += p[i].z, s2 += 1.0*p[i].z/p[i].run;
    printf("%37.2f %9.2f\n", s1/n, s2/n);
}

void SJF()
{
    for (int i = 1; i <= n; ++i)
        p[i].reset();
    int s = 0;
    while (judge())
    {
        priority_queue<f, vector<f>, cmp1> pq;
        for (int i = 1; i <= n; ++i)
            if (p[i].remain && p[i].ready <= s) pq.push(p[i]);
        if (!pq.empty())
        {
            f temp = pq.top();
            p[temp.id].start = s;
            p[temp.id].end = p[temp.id].start + p[temp.id].run;
            p[temp.id].remain = 0;
            s = p[temp.id].end;
        }
        else ++s;
    }
    printf("短作业优先\n");
    printf("就绪时刻 运行时间 开始时间 结束时间 周转时间 带权周转时间\n");
    for (int i = 1; i <= n; ++i)
        p[i].out();
    double s1, s2;
    s1 = s2 = 0;
    for (int i = 1; i <= n; ++i)
        s1 += p[i].z, s2 += 1.0*p[i].z/p[i].run;
    printf("%37.2f %9.2f\n", s1/n, s2/n);
}

void HRRF()
{
    for (int i = 1; i <= n; ++i)
        p[i].reset();
    int s = 0;
    while (judge())
    {
        priority_queue<f, vector<f>, cmp2> pq;
        for (int i = 1; i <= n; ++i)
        {
            p[i].wait = max(p[i].wait, s - p[i].ready);
            if (p[i].remain && p[i].ready <= s) pq.push(p[i]);
        }
        if (!pq.empty())
        {
            f temp = pq.top();
            p[temp.id].start = s;
            p[temp.id].end = p[temp.id].start + p[temp.id].run;
            p[temp.id].remain = 0;
            s = p[temp.id].end;
        }
        else ++s;
    }
    printf("高响应比优先\n");
    printf("就绪时刻 运行时间 开始时间 结束时间 周转时间 带权周转时间\n");
    for (int i = 1; i <= n; ++i)
        p[i].out();
    double s1, s2;
    s1 = s2 = 0;
    for (int i = 1; i <= n; ++i)
        s1 += p[i].z, s2 += 1.0*p[i].z/p[i].run;
    printf("%37.2f %9.2f\n", s1/n, s2/n);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        p[i].read();
        p[i].id = i;
    }
    FCFS();
    SJF();
    HRRF();
    RR();
    return 0;
}