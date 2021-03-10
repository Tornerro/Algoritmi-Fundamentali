#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("secvente.in");

int n, s, t, viz[100001], tata[100001], in[100001], out[100001];

struct arc
{
    int y, flux, cap;
};

vector<arc> v[100001];

vector<int> w[100001];

int lant_nesat() // caut un lant nesaturat
{
    int x, y, f, c;
    for(int i=s; i<=t;++i)
    {
        tata[i]= -100001;
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
                if(y==t)return 1; // daca ajung la varful t am gasit lantul nasaturat
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
    return 0; // daca ajung la final nu mai este niciun lant nesaturat
}

void revizuire_flux()
{
    int e = 100001, y=t, x, invers;
    while(tata[y]!=-100001)
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
    while(tata[y]!=-100001)
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
    int x, y, ok =1;
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

    int diferenta_flux = 0;

    for(auto p: v[s]) // pentru fiecare arc care pleaca din s verific daca fluxul este egal cu capacitatea
    {                 // daca gasesc oricare arc unde nu este egalitate, atunci nu exsita graful cautat
        if(p.flux!=p.cap)
        {
            ok = 0;
            diferenta_flux += p.cap- p.flux;
        }
    }
    cout<<"a)\n";
    if(ok)
    {
        for(int i=1; i<=n;++i)
        {
            for(auto p: v[i])
            {
                if(p.flux)cout<<i<<' '<<p.y-n<<'\n';
            }
        }
        return 0;
    }
    cout<<"nu exista.\nb)\n";
    if(diferenta_flux > 1)
    {
        cout<<"nu exista.\nc)\n";
    }
    else
    {
        x=0;
        y=0;
        for(auto p: v[s])
        {
            if(p.flux!=p.cap)
            {
                x = p.y;
                break;
            }
        }
        for(int i= n+1; i<=2*n && y == 0; ++i)
        {
            for(auto p: v[i])
            {
                if(p.y == t && p.flux != p.cap)
                {
                    y = i-n;
                    break;
                }
            }
        }
        for(int i=1; i<=n;++i)
        {
            for(auto p: v[i])
            {
                if(p.flux)cout<<i<<' '<<p.y-n<<'\n';
            }
        }
        cout<<"(i="<<x<<",j="<<y<<")\nc)\n";
    }
    cout<<"no time left.";
    return 0;
}
