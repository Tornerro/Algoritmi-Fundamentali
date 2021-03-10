#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;
ifstream fin("dag.in");
ofstream fout("dag.out");

int d[101], t[101];

int main()
{
    int n, m, x, y, s, c;
    fin>>n>>m;
    vector<pair<int,int>> v[n+1];
    vector<int> st;
    int grad[n+1];
    for(int i=1; i<=n;++i)
    {
        d[i]=INT_MAX;
        t[i]=0;
        grad[i]=0;
    }
    for(int i=1; i<=m;++i)
    {
        fin>>x>>y>>c;
        v[x].push_back({y,c});
        grad[y]++;
    }
    queue<int> q;
    for(int i=1; i<=n; ++i)
    {
        if(!grad[i])q.push(i);
    }
    while(!q.empty())
    {
        x = q.front();
        q.pop();
        st.push_back(x);
        for(auto i: v[x])
        {
            grad[i.first]--;
            if(!grad[i.first])q.push(i.first);
        }
    }
    for(int x: st) fout<<x<<" ";
    fout<<'\n';

    s = 5;
    d[s] = 0;
    for(int i: st)
    {
        for(auto j: v[i])
        {
            if(d[i] + j.second < d[j.first] )
            {
                d[j.first] = d[i] + j.second;
                t[j.first] = i;
            }
        }
    }
    for(int i=1; i<=n; ++i)
    {
        if(d[i]==INT_MAX)d[i]=-1;
        fout<<d[i]<<' ';
    }

    return 0;
}
