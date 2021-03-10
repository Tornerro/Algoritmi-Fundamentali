#include <iostream>
#include <fstream>
#include <vector>
#include <list>
using namespace std;
ifstream fin("graf.in");
ofstream fout("graf.out");

int n, m, c[101], vec[101], viz[101];
vector<int> v[101];
list<int> p;

int adauga_la_lista(int x)
{
    p.push_front(x);
    viz[x]=1;
    vec[x]=0;
    for(int i: v[x])
    {
        vec[i]--;
        if(viz[x]==0 && vec[i]<=5 )adauga_la_lista(i);
    }
}

void fa_lista()
{
    while(p.size()!= n)
    {
        for(int i=1 ;i<=n && p.size()!=n; ++i)
        {
            if(viz[i]==0 && vec[i]<=5)adauga_la_lista(i);
        }
    }
}



int main()
{
    int x, y, k;
    fin>>n>>m;
    for(int i=1; i<=m; ++i)
    {
        fin>> x>> y;
        vec[x]++;
        vec[y]++;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    fa_lista();
    while(!p.empty())
    {
        x = p.front();
        p.pop_front();
        y = 1;
        k = 1;
        cout<<x<<": ";
        do
        {
            k = y;
            for(int i :v[x])
            {
                cout<<i<<"-"<<c[i]<<' ';
                if(c[i] == y)y++;
            }
        }
        while(k!=y);
        cout<<'\n';
        c[x] = y;
    }
    for(int i=1; i<=n; ++i)fout<<c[i]<<' ';
    return 0;
}
