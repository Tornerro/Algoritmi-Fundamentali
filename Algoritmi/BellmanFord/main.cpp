#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;
ifstream fin("bellmanford.in");
ofstream fout("bellmanford.out");

int d[50001], t[50001], viz[50001], nr[50001];
vector<pair<int, int>> v[50001];

int bellmanford(int n, int m, int s)
{
    int x, y, c;
    d[s] = 0;
    queue<int> q;
    q.push(s);
    viz[s]=1;
    while(!q.empty())
    {
        x=q.front();
        q.pop();
        viz[x]=0;
        for(auto j : v[x])
        {
            y = j.first;
            c = j.second;
            if( d[x]!=INT_MAX && ( d[x] + c < d[y]) )
            {
                d[y] = d[x] + c;
                t[y] = x;
                if(!viz[y])
                {
                    q.push(y);
                    viz[y]=1;
                    nr[y] = nr[x] + 1;
                    if(nr[y] > n-1)return 0;
                }
            }
        }
    }
    return 1;
}

int main()
{
    int n, m, x, y, c, ok;
    fin>> n>> m;
    for(int i=1; i<=m; ++i)
    {
        fin>> x>> y>> c;
        v[x].push_back({y, c});
    }
    for(int i=1 ;i<=n; ++i)d[i] = INT_MAX;
    if( bellmanford(n, m, 1))
    {
        for(int i=2; i<=n; ++i)fout<<d[i]<<' ';
    }
    else fout<<"Ciclu negativ!";
    return 0;
}
