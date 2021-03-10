#include <iostream>
#include <fstream>
#include <climits>
#include <string>
using namespace std;
ifstream fin("rj.in");
ofstream fout("rj.out");

int dx[]={-1,-1,0,1,1,1,0,-1};
int dy[]={0,1,1,1,0,-1,-1,-1};

struct coordonate
{
    int x, y;
};

int interior(int x, int y, int n,int m)
{
    return 1<=x && x<=n && 1<=y && y<=m;
}

void BF( int a,int b, int s[][101], int n , int m)
{
    coordonate c[10001];
    int u=1, i, p=1, xd, yd, xp, yp;
    c[p].x = a;
    c[p].y = b;
    while(p<=u)
    {
        xd = c[p].x;
        yd = c[p++].y;
        for(i=0; i<=7; ++i)
        {
            xp = xd + dx[i];
            yp = yd + dy[i];
            if(interior(xp, yp, n, m) && !s[xp][yp])
            {
                c[++u].x = xp;
                c[u].y = yp;
                s[xp][yp] = s[xd][yd] + 1;
            }
        }
    }
    s[a][b] = 0;
}


int main()
{
    int i, j, n, m, min = INT_MAX, xr, yr, xj, yj, a[101][101], b[101][101], xm, ym;
    char s[101];
    fin>>n>>m;
    fin.getline(s, 101);
    for(i=1; i<=n;++i)
    {
        fin.getline(s, 101);
        for(j=1;j<=m;++j)
        {
            if(s[j-1] == 'R')
            {
                a[i][j] = 0;
                b[i][j] = 0;
                xr = i;
                yr = j;
            }
            else if(s[j-1]=='J')
            {
                a[i][j] = 0;
                b[i][j] = 0;
                xj = i;
                yj = j;
            }
            else if(s[j-1]=='X')
            {
                a[i][j] = -1;
                b[i][j] = -1;
            }
            else
            {
                a[i][j] = 0;
                b[i][j] = 0;
            }
        }
    }

    BF(xr, yr, a, n, m);
    BF(xj, yj, b, n, m);
    for(i=1; i<=n; ++i)
    {
        for(j=1; j<=m; ++j)
        {
            if(a[i][j] == b[i][j] && a[i][j]>0 && a[i][j]<min)
            {
                min=a[i][j];
                xm = i;
                ym = j;
            }
        }
    }
    fout<< min+1<< ' '<< xm << ' '<<ym;
    return 0;
}
