#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;
ifstream fin("graf.in");
ofstream fout("graf.out");

struct muchie
{
    int x, y, cost;
};

vector <muchie> muchii;
muchie p;

int viz[101], nivel[101], niv_min[101], n;
set <int> v[101];

void df(int i)
{
    viz[i] = 1;
    niv_min[i] = nivel[i];
    for(int j: v[i])
    {
        if(viz[j]==0)
        {
            nivel[j] = nivel[i] + 1;
            df(j);
            niv_min[i] = min(niv_min[i], niv_min[j]);
        }
        else
        {
            if(nivel[j] < nivel[i]-1)
            {
                niv_min[i] = min(niv_min[i], nivel[j]);
            }
        }
    }
}

int pivot(int p, int q, vector<muchie> &v)
{
    muchie x = v[p];
    while(p<q)
    {
        while(p<q && v[q].cost <= x.cost)q--;
        v[p]=v[q];
        while(p<q && v[p].cost >= x.cost)p++;
        v[q]=v[p];
    }
    v[p] = x;
    return p;
}

void QS(int p, int q, vector<muchie> &v)
{
    if(p < q)
    {
        int a = pivot(p, q, v);
        QS(p, a-1, v);
        QS(a+1, q, v);
    }
}

int test(muchie mu)
{
    for(int i=1;i<=n;++i)
    {
        viz[i]=0;
        nivel[i]=0;
        niv_min[i]=0;
    }
    nivel[mu.x]=1;
    df(mu.x);
    if(niv_min[mu.y]>nivel[mu.x])
    {
        return 0;
    }
    return 1;
}

int main()
{
    muchii.push_back(p);
    int  m, x, y, c;
    fin>>n >>m;
    for(int i=1; i<=m; ++i)
    {
        fin>> x>> y>> c;
        v[x].insert(y);
        v[y].insert(x);
        p.x = x;
        p.y = y;
        p.cost = c;
        muchii.push_back(p);
    }
    QS(1,m, muchii);
    for(int i=1; i<=m && m>n-1; ++i)
    {
        if( test(muchii[i]))
        {
            x=muchii[i].x;
            y=muchii[i].y;
            v[x].erase(y);
            v[y].erase(x);
            muchii.erase(muchii.begin()+i);
            i--;
            m--;
        }
    }
    for(int i=1; i<=m; ++i)fout<<muchii[i].x<<' '<<muchii[i].y<<'\n';
    return 0;
}
