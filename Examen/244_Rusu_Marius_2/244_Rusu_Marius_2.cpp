#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

ifstream fin("graf.in");

int d[100001], tata[100001], grad[100001];
vector<pair<int,int>> v[100001]; // lista de adiacenta
vector<int> st; // vector pt sortare topologica


void afisare(int x)
{
    if(tata[x])afisare(tata[x]);
    cout<<x<<' ';
}


int main()
{
    int n, m, x, y, s, c, p, k, t[100001];
    fin>>n>>m;

    for(int i=1; i<=n;++i)
    {
        d[i]=INT_MAX;
    }
    for(int i=1; i<=m;++i)
    {
        fin>>x>>y>>c;
        v[x].push_back({y,c});
        grad[y]++;
    }
    queue<int> q;
    for(int i=1; i<=n; ++i)
    {
        if(!grad[i])q.push(i);
    }
    while(!q.empty()) // sortare topologica pt ca nu sunt circuite
    {
        x = q.front();
        q.pop();
        st.push_back(x);
        for(auto i: v[x])
        {
            grad[i.first]--;
            if(!grad[i.first])q.push(i.first);
        }
    }
    fin >> s;
    d[s] = 0;
    for(int i: st) // folosesc algoritmul dag pt ca nu sunt circuite in graf
    {
        for(auto j: v[i])
        {
            if(d[i] + j.second < d[j.first] )
            {
                d[j.first] = d[i] + j.second;
                tata[j.first] = i;
            }
        }
    }
    fin>>k;
    for(int i=1; i<=k; ++i)fin>>t[i];
    p = t[1];
    for(int i=2; i<=k; ++i)
    {
        x = d[t[i]];
        if(x != INT_MAX && x > d[p])p = t[i];
    }
    if(d[p] == INT_MAX)
    {
        cout<<"Nu exista varf accesibil.";
        return 0;
    }
    cout<<"a) \n"<<p<<"\nb)\n";

    int dmin = INT_MAX, nr_drumuri = 0, w[100001]; // dmin tine distanta minima a drumui, nr_drumuri tine minte cate drumuri au aceasta distanta
                                                   // si w tine minte din ce varfuri pleaca ultima muchie din drum spre p, varful destinatie de la punctul a

    for(int i=1 ;i<=n; ++i) // merg prin toate varfurile si verific daca au arc orientat spre p, varful destinatie de la punctul a
    {
        if(i!=p)
        {
            for(auto j: v[i])
            {
                if(j.first == p && d[i] + j.second < dmin) // daca gasesc un nou drum minim resetez w si nr_drumuri si actualizez dmin
                {
                    dmin = d[i] + j.second;
                    nr_drumuri = 1;
                    w[nr_drumuri] = i;
                }
                else if(j.first == p && d[i] + j.second == dmin) // aca gasesc un drum cu acceasi lungime a cel mai mic il adaug la w
                {
                    nr_drumuri++;
                    w[nr_drumuri] = i;
                }
            }
        }
    }
    if(nr_drumuri == 1) // daca e un singur drum minim il afisez
    {
        afisare(w[1]);
        cout<<p;
    }
    else // aca sunt mai multe le afisez pe primele 2
    {

        afisare(w[1]);
        cout<<p<<'\n';
        afisare(w[2]);
        cout<<p;
    }
    return 0;
}
