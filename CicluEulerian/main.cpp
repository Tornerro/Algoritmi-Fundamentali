#include <iostream>
#include <fstream>
#include <vector>
#include <list>
using namespace std;
ifstream fin("ciclueuler.in");
ofstream fout("ciclueuler.out");

int n, m, vec[100001];
vector<int> v[100001];
vector<int> c;

void euler(int x)
{
    while(!v[x].empty())
    {
        int y = v[x].back();
        for(int i=0; i<v[y].size();++i)
        {
            if(v[y][i] == x)
            {
                v[y].erase(v[y].begin()+i);
                break;
            }
        }
        v[x].pop_back();
        euler(y);
    }
    c.push_back(x);
}

int main()
{
    int x, y;
    fin>>n >>m;
    for(int i=1; i<=m; ++i)
    {
        fin>> x>> y;
        v[x].push_back(y);
        v[y].push_back(x);
        vec[x]++;
        vec[y]++;
    }
    for(int i=1; i<=n; ++i)
    {
        if(vec[i]%2)
        {
            fout<<-1;
            return 0;
        }
    }
    euler(1);
    c.pop_back();
    for(int i: c)fout<<i<<' ';
    return 0;

}
