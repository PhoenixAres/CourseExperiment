#include <bits/stdc++.h>
using namespace std;

const int maxn = 110;
const int n = 4;
const int m = 100;
int ask[maxn];

void LRU()
{
    map<int, int> mp;
    int cnt = 0;
    for (int i = 1; i <= m; ++i)
    {
        if (!mp.count(ask[i])) ++cnt;
        if (!mp.count(ask[i]) && mp.size() == n)
        {
            priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
            for (map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it)
                pq.push(make_pair(it->second, it->first));
            mp.erase(pq.top().second);
        }
        mp[ask[i]] = i;
        printf("第%d次请求：", i);
        for (map<int, int>::iterator it = mp.begin(); it != mp.end(); ++it)
            printf("%d ", it->first);
        printf("\n");
    }
    printf("缺页中断次数：%d\n", cnt);
}

void FIFO()
{
    int cnt = 0;
    queue<int> q;
    set<int> st;
    for (int i = 1; i <= m; ++i)
    {
        if (!st.count(ask[i]))
        {
            ++cnt;
            if (q.size() == n) st.erase(q.front()), q.pop();
            q.push(ask[i]);
            st.insert(ask[i]);
        }
        printf("第%d次请求：", i);
        for (set<int>::iterator it = st.begin(); it != st.end(); ++it)
            printf("%d ", *it);
        printf("\n");
    }
    printf("缺页中断次数：%d\n", cnt);
}


int main()
{
    srand(777);
    for (int i = 1; i <= m; ++i) ask[i] = rand()%21;
    for (int i = 1; i <= m; ++i) printf("%d ", ask[i]);
    printf("\n");
    LRU();
    FIFO();
    return 0;
}