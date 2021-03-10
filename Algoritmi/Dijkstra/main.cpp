#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;
ifstream fin("dijkstra.in");
ofstream fout("dijkstra.out");

int main()
{
    int n, m, x, y, c, s;
    fin>>n>>m;
    int d[n+1], t[n+1], viz[n+1];
    vector <pair <int, int>> v[n+1];
    for(int i=1; i<=m; ++i)
    {
        fin>> x >> y >> c;
        v[x].push_back({y, c});
    }
    for(int i=1; i<=n; ++i)
    {
        d[i]=INT_MAX;
        t[i]=0;
        viz[i]= 0;
    }
    priority_queue < pair <int, int>> q;
    s=1;
    d[s]=0;
    viz[s]=1;
    q.push({-d[s],s});
    while(!q.empty())
    {
        x = q.top().second;
        q.pop();
        viz[x]=0;
        for(auto p: v[x])
        {
            y = p.first;
            c = p.second;
            if( d[x] + c < d[y] )
            {
                d[y] = d[x] + c;
                t[y] = x;
                if(viz[y] == 0)
                {
                    q.push({-d[y], y});
                    viz[y] = 1;
                }
            }
        }
    }
    for(int i = 2; i<=n; ++i)
    {
        if(d[i] == INT_MAX) d[i] = 0;
        fout << d[i]<<' ';
    }
    return 0;
}
