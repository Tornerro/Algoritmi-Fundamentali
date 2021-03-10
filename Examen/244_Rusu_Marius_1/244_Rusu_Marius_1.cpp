#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

ifstream fin("graf.in");

int ta[100001], tb[100001], da[100001], db[100001], viz[100001];
vector<int> v[100001]; // liste de adiacenta

void BFS(int x) // fac BFS pt arborele de distante si tin in ta vectorul de tati si in da vectorul de distante
{
    queue<int> q;
    q.push(x);
    viz[x]=1;
    while(!q.empty())
    {
        x = q.front();
        q.pop();
        for(int y: v[x])
        {
            if(viz[y] == 0)
            {
                q.push(y);
                viz[y] = 1;
                da[y] = da[x] + 1;
                ta[y] = x;
            }
        }
    }
}

void DFS(int x) // parcurgere in adancime pt un alt arbore, tin in tb vectorul de tati si in db vectorul de distante
{
    viz[x] = 0;
    for(int y: v[x])
    {
        if(viz[y] == 1)
        {
            tb[y] = x;
            db[y] = db[x] + 1;
            DFS(y);
        }
    }
}

int main()
{
    int n, m, x, y;
    fin>> n>> m;
    for(int i= 1; i<=m; ++i)
    {
        fin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    BFS(1);
    cout<<"T: \n";
    for(int i = 1; i<=n; ++i)
    {
        if(ta[i])cout<<ta[i]<<' '<<i<<'\n'; // afisez muchiile din arborele de distanta
    }

    DFS(1);
    cout<<"\nT': \n";
    for(int i=1 ;i<=n; ++i)
    {
        if(tb[i])cout<<tb[i]<<' '<<i<<'\n'; // afisez muchiile din arborele dfs
    }


    cout<<"\nv: ";
    for(int i = 1; i<=n; ++i)
    {
        if(da[i]!=db[i])cout<<i<<' '; // afisez muchiile cu distante diferite
    }

    return 0;
}
