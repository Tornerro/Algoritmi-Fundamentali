#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("royfloyd.in");
ofstream fout("royfloyd.out");

int d[101][101], p[101][101];

int main()
{
    int n;
    fin>>n;

    for(int i= 1; i<=n; ++i)
    {
        for(int j=1; j<=n; ++j)
        {
            fin>>d[i][j];
            if(d[i][j])p[i][j] = i;
            else
            {
                if(i!=j)d[i][j] = 1001;
            }
        }
    }
    for(int k=1; k<=n; ++k)
    {
        for(int i=1; i<=n; ++i)
        {
            for(int j=1; j<=n; ++j)
            {
                if(d[i][j]>d[i][k] + d[k][j] )
                {
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = p[k][j];
                }
            }
        }
    }
    for(int i =1; i<=n; ++i)
    {
        for(int j =1; j<=n; ++j)
        {
            if(d[i][j]==1001)fout<<0<<' ';
            else fout<<d[i][j]<<' ';
        }
        fout<<'\n';
    }

    // pt detectare de circuit negativ se verifica pozitiile d[i][i] sa nu fie negative.
    // daca exista d[i][i] < 0 atunci datele de intrare sunt gresite


    return 0;
}
