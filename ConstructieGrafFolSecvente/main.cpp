#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("secvente.in");
ofstream fout("secvente.out");

int n, s, t, viz[101], tata[101], in[101], out[101];

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
        tata[i]= -10001;
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
        for(int i=1; i<=n; ++i)
        {
            if(i!=x)
            {
                for(arc p: v[i])
                {
                    y=p.y;
                    f=p.flux;
                    if(y==x && viz[i]==0 && f>0)
                    {
                        viz[i]= 1;
                        q.push(i);
                        tata[i] = -x;
                        if(i == t)return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void revizuire_flux()
{
    int e = 10001, y=t, x, invers;
    while(tata[y]!=-10001)
    {
        invers = 0;
        x = tata[y];
        if(x<0)
        {
            invers = 1;
        }
        if(invers == 0)
        {
            for(auto p: v[x])
            {
                if(p.y == y )
                {
                    if(p.cap - p.flux < e)e = p.cap - p.flux;
                }
            }
            y = x;
        }
        else
        {
            for(auto p: v[y])
            {
                if(p.y == -x )
                {
                    if(p.flux < e) e = p.flux;
                }
            }
            y = -x;
        }
    }
    y = t;
    while(tata[y]!=-10001)
    {
        invers = 0;
        x = tata[y];
        if(x<0)
        {
            invers = 1;
        }
        if(invers == 0)
        {
            for(int i = 0 ; i<=v[x].size(); ++i)
            {
                if(v[x][i].y == y )
                {
                    v[x][i].flux += e;
                    out[x] += e;
                    in[y] += e;
                }
            }
            y = x;
        }
        else
        {
            for(int i = 0 ; i<=v[y].size(); ++i)
            {
                if(v[y][i].y == -x )
                {
                    v[y][i].flux -= e;
                    out[y] -=e;
                    in[-x] -= e;
                }
            }
            y = -x;
        }
    }
}

int main()
{
    int x, y;
    arc p;
    fin>>n;
    for(int i=1; i<=n; ++i)fin>>in[i];
    for(int i=1; i<=n; ++i)fin>>out[i];
    s = 0;
    t = 2*n+1;
    for(int i=1;i<=n;++i)
    {
        p.y = i;
        p.flux = 0;
        p.cap = out[i];
        v[s].push_back(p);

        p.y = t;
        p.flux = 0;
        p.cap = in[i];
        v[i+n].push_back(p);

        for(int j=n+1; j<=2*n; ++j)
        {
            if(i+n != j)
            {
                p.y = j;
                p.flux = 0;
                p.cap = 1;
                v[i].push_back(p);
            }
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

    for(auto p: v[s])
    {
        if(p.flux!=p.cap)
        {
            fout<<"NU";
            return 0;
        }
    }

    for(int i=1; i<=n;++i)
    {
        for(auto p: v[i])
        {
            if(p.flux)fout<<i<<' '<<p.y-n<<'\n';
        }
    }
    return 0;
}
