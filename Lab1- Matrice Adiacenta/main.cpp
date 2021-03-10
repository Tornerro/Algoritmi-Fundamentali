#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("graf.in");

int main()
{
    int n, m, i, j, x, y;
    fin>>n >>m;
    int a[n+1][n+1];
    for(i=1;i<=n;++i)
    {
        for(j=1;j<=n;++j)a[i][j]=0;
    }
    for(i = 1; i<=m; ++i)
    {
        fin>> x>> y;
        a[x][y] ++;
        a[y][x] ++;
    }
    for(i=1;i<=n;++i)
    {
        for(j=1;j<=n;++j)cout<<a[i][j]<<' ';
        cout<<'\n';
    }
    return 0;
}
