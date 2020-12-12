#include <bits/stdc++.h>
using namespace std;

const int maxn = 10;
string FileContent[maxn];
int FAT[maxn];
map<string, int> File;

int main()
{
    srand(777);
    for (int i = 0; i < maxn; ++i) FileContent[i].resize(4);
    while (1)
    {
        string a, b, c;
        cin >> a;
        if (a == "mkfile")
        {
            cin >> b >> c;
            int len = ceil(c.size()/4.0);
            int last, now;
            last = -1;
            for (int i = 1; i <= len; ++i)
            {
                now = rand()%maxn;
                while (FAT[now] || now == last) now = rand()%maxn;
                if (last == -1) File[b] = now;
                if (last != -1) FAT[last] = now;
                FileContent[now] = c.substr((i-1)*4, 4);
                last = now;
                if (i == len) FAT[now] = -1;
            }
        }
        else if (a == "dir")
        {
            for (auto it = File.begin(); it != File.end(); ++it)
                cout << "Filename: " << it->first << "  BeginID: " << it->second << endl;
            cout << "FAT: " << endl;
            for (int i = 0; i < maxn; ++i)
                cout << "(" << i << ", " << FAT[i] << ")" << endl;
        }
        else if (a == "type")
        {
            cin >> b;
            auto it = File.find(b);
            if (it != File.end())
            {
                int now = it->second;
                while (1)
                {
                    cout << FileContent[now];
                    now = FAT[now];
                    if (now == -1) break;
                }
                cout << endl;
            }
            else cout << b << " is non-existent" << endl;
        }
        else if (a == "del")
        {
            cin >> b;
            auto it = File.find(b);
            if (it != File.end())
            {
                int now = it->second;
                int last = -1;
                while (1)
                {
                    FileContent[now].clear();
                    last = now;
                    now = FAT[now];
                    FAT[last] = 0;
                    if (now == -1) break;
                }
                File.erase(it);
            }
            else cout << b << " is non-existent" << endl;
        }
        else if (a == "quit") break;
    }
    return 0;
}