#include<bits/stdc++.h>
using namespace std;

const int maxn = 2e6 + 10;

class sList
{
    int a[maxn];
    int maxlen;
    int len;
public:
    sList():maxlen(maxn), len(0){}
    bool isempty()
    {
        if (!len) return true;
        return false;
    }
    int getlen(){return len;}
    bool insert(int x, int i = -1)
    {
        if (len == maxn) return false;
        if (i >= len) return false;
        if (i == -1) a[len] = x;
        else
        {
            for (int j = len-1; j >= i; --j)
                a[j+1] = a[j];
            a[i] = x;
        }
        ++len;
        return true;
    }
    void reverse()
    {
        for (int i = 0; i < len/2; ++i)
            swap(a[i], a[len-1-i]);
    }
    bool del(int x)
    {
        int k = 0;
        for (int i = 0; i < len; ++i)
            if (a[i] != x) a[k++] = a[i];
        if (len == k) return false;
        else
        {
            len = k;
            return true;
        }
    }
    bool update(int i, int x)
    {
        if (i >= len) return false;
        a[i] = x;
        return true;
    }
    pair<bool, int> find(int i)
    {
        if (i >= len) return make_pair(false, 0);
        return make_pair(true, a[i]);
    }
    bool output()
    {
        if (isempty()) return false;
        for (int i = 0; i < len; ++i)
            printf("%d ", a[i]);
        printf("\n");
        return true;
    }
} sL;

int main()
{
    if (sL.isempty()) printf("empty\n\n");
    sL.insert(2);
    sL.insert(56);
    sL.insert(23);
    sL.insert(8, 1);
    sL.insert(8);
    sL.insert(9);
    pair<bool, int> t = sL.find(6);
    if (t.first) printf("%d\n\n", t.second);
    else printf("%d is not exist\n\n", 6);
    sL.output();
    sL.reverse();
    printf("\n");
    sL.output();
    printf("\n");
    sL.del(8);
    sL.update(0, 200);
    printf("%d\n\n", sL.getlen());
    sL.output();
    return 0;
}