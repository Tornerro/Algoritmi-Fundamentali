#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
ifstream fin("biconex.in");
ofstream fout("biconex.out");

int viz[100001], nivel[100001], niv_min[100001], k;
vector <int> v[100001];
set <int> s[1000001];

struct muchie
{
    int x, y;
};

vector <muchie> muchii;
muchie p;

void df(int i)
{
    viz[i] = 1;
    niv_min[i] = nivel[i];
    for(int j: v[i])
    {
        if(viz[j]==0)
        {
            nivel[j] = nivel[i] + 1;
            p.x = i;
            p.y = j;
            muchii.push_back(p);
            df(j);
            niv_min[i] = min(niv_min[i], niv_min[j]);
            if(niv_min[j]>nivel[i] || (niv_min[j] == nivel[i] && nivel[i] !=1))
            {
                k++;
                while(i!=muchii.back().x || j!= muchii.back().y)
                {
                    s[k].insert( muchii.back().x );
                    s[k].insert( muchii.back().y );
                    muchii.pop_back();
                }
                s[k].insert( muchii.back().x );
                s[k].insert( muchii.back().y );
                muchii.pop_back();
            }
            else if(nivel[i]==1)
            {
                k++;
                while(!muchii.empty())
                {
                    s[k].insert( muchii.back().x );
                    s[k].insert( muchii.back().y );
                    muchii.pop_back();
                }
            }
        }
        else
        {
            if(nivel[j] < nivel[i]-1)
            {
                niv_min[i] = min(niv_min[i], nivel[j]);
                p.x = i;
                p.y = j;
                muchii.push_back(p);
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
    fout<<k<<'\n';
    for(int i = 1; i<=k; ++i)
    {
        for(auto j: s[i])
        {
            fout<<j<<' ';
        }
        fout<<'\n';
    }
    return 0;
}
