#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("graf.in");
int main()
{
    int n, i, j, x;
    fin>>n;
    int a[n+1][n+1];
    for( i=1;i<=n;++i)a[i][0]=0;
    for(i = 1; i<=n;++i)
    {
        for(j=1;j<=n; ++j)
        {
            fin>>x;
            if(x)
            {
                a[i][++a[i][0]]=j;
            }
        }
    }
    for(int i=1;i<=n;++i)
    {
        cout<< i<<": ";
        for(j = 1; j<= a[i][0]; ++j)cout<<a[i][j]<<' ';
        cout<<'\n';
    }
    return 0;
}
