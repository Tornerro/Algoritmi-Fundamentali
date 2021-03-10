#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("graf.in");

int main()
{
    int n, m, i, j, x, y;
    fin>> n>> m;
    int a[n+1][n+1];
    for(i=1;i<=n;++i)a[i][0]=0;
    for(int i=1; i<=m;++i)
    {
        fin>>x>>y;
        a[x][++a[x][0]] = y;
        a[y][++a[y][0]] = x;
    }
    for(int i=1;i<=n;++i)
    {
        cout<< i<<": ";
        for(j = 1; j<= a[i][0]; ++j)cout<<a[i][j]<<' ';
        cout<<'\n';
    }
    return 0;
}
