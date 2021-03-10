#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("graf.in");
ofstream fout("graf.out");

int viz[101], nivel[101], niv_min[101];
vector <int> v[101], crit;

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
            if(niv_min[j]>nivel[i] || (niv_min[j] == nivel[i] && nivel[i] !=1))
            {
                crit.push_back(i);
            }
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

int main()
{
    int n, m, x, y;
    fin>>n >>m;
    for(int i=1; i<=m; ++i)
    {
        fin>> x>> y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    nivel[1] = 1;
    df(1);
    for(int p: crit)
    {
        fout<<p<<' ';
    }
    return 0;
}
