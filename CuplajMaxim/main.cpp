#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("graf.in");
ofstream fout("graf.out");

int n, m, s, t, viz[101], tata[101];

struct arc
{
    int y, flux, cap;
};

vector<arc> v[101];

vector<int> w[101];

int lant_nesat()
{
    int x, y, f, c;
    for(int i=s; i<=t;++i)
    {
        tata[i]= -1;
        viz[i] = 0;
    }

    viz[s] = 1;
    queue<int> q;
    q.push(s);
    while(!q.empty())
    {
        x= q.front();
        q.pop();
        for(arc p: v[x])
        {
            y=p.y;
            f=p.flux;
            c=p.cap;
            if(viz[y]==0 && c - f >0)
            {
                viz[y] = 1;
                q.push(y);
                tata[y] = x;
                if(y==t)return 1;
            }
        }
    }
    return 0;
}

void revizuire_flux()
{
    int e = 1, y=t, x;
    while(tata[y]!=-1)
    {
        x = tata[y];
        for(int i = 0 ; i<=v[x].size(); ++i)
        {
            if(v[x][i].y == y )
            {
                v[x][i].flux += e;
            }
        }
        y = x;
    }


}


int verif_bipartit(int x)
{
    queue<int> q;
    q.push(x);
    viz[x] = 1;
    while(!q.empty())
    {
        x = q.front();
        q.pop();
        for(int p: w[x])
        {
            if(viz[p] == 0)
            {
                viz[p] = 3 - viz[x];
                q.push(p);
                tata[p] = x;
            }
            else
            {
                if(viz[p] == viz[x])
                {
                    tata[p] = x;
                    return x;
                }
            }
        }
    }
    return 0;
}

int main()
{
    int x, y;
    arc p;
    fin>> n>> m;
    for(int i= 1; i<=m; ++i)
    {
        fin>>x>>y;
        w[x].push_back(y);
        w[y].push_back(x);
    }
    x=verif_bipartit(1);
    if(x!=0)
    {
        fout<<"Graful nu e bipartit";
        return 0;
    }
    s = 0;
    t = n+1;
    for(int i=1; i<=n; ++i)
    {
        if(viz[i]==1)
        {
            p.y = i;
            p.cap = 1;
            p.flux = 0;
            v[0].push_back(p);
            for(int j: w[i])
            {
                p.y = j;
                p.cap = 1;
                p.flux = 0;
                v[i].push_back(p);
            }
        }
        else
        {
            p.y = t;
            p.cap = 1;
            p.flux = 0;
            v[i].push_back(p);
        }

    }
    while(lant_nesat())
    {
        y = t;
        while(tata[y]!=0)
        {
            x = tata[y];
            y= x;
        }
        revizuire_flux();
    }
    for(int i=1; i<=n; ++i)
    {
        for(auto p: v[i])
        {
            if(p.flux && p.y!=t)fout<<i<<' '<<p.y<<'\n';
        }
    }
    return 0;
}
