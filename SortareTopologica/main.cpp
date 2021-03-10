#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("sortaret.in");
ofstream fout("sortaret.out");

int main()
{
    int n, m, x, y;
    fin>>n>>m;
    vector<int> v[n+1];
    vector<int> st;
    int grad[n+1];
    for(int i=1; i<=n;++i)grad[i]=0;
    for(int i=1; i<=m;++i)
    {
        fin>>x>>y;
        v[x].push_back(y);
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
        for(int i: v[x])
        {
            grad[i]--;
            if(!grad[i])q.push(i);
        }
    }
    for(int x: st) fout<<x<<" ";
    return 0;
}
