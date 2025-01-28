#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>


using std::vector;
using std::pair;
/*
int thestart;
std::ifstream dfsin("dfs.in");
std::ofstream dfsout("dfs.out");

template<typename T, typename Y>
std::ostream& operator<<(std::ostream& stream, std::pair<T,Y> const& p) {
    stream << '(' << p.first << ' ' << p.second << ')';
    return stream;
}
template<typename T, typename Y>
std::istream& operator>>(std::istream& stream, std::pair<T,Y>& p) {
    stream >> p.first >> p.second;
    return stream;
}

template <class extra=void* >
class Graf{
    typedef pair<int,extra> Edge;
    const int N;
    int n;
    vector<vector<Edge> >edges;

    public:
    ///CONSTRUCTORS:
    Graf(int MAX_N):N(MAX_N + 5){
        edges.resize(N);

    }

    /// OPERATORS:
    vector<Edge>& operator[](size_t i){
        return edges[i];
    }
    friend std::istream& operator>>(std::istream& fin, Graf& g){
        int m, x, node;
        extra ex;

        fin >> g.n >> m >> thestart;
        while(m--){
            fin >> x >> node;

            if(!std::is_same<extra,void*>::value){
                fin >> ex;
            }
            Edge edge  = {node,ex};
            g[x].push_back(edge);
            g[node].push_back({x,ex});
        }
        return fin;
    }
    friend std::ostream& operator<<(std::ostream& fout, Graf g){
        for(size_t i =0 ; i < g.edges.size(); i++){
            if(g[i].empty())
                continue;
            fout << i << ": ";
            for(Edge x:g[i])
                fout << x << ' ';
            fout << '\n';
        }
        return fout;
    }
    /// ACTUAL FUNCTIONS:
    void sortEdges(){
        for(auto& e : edges)
            std::sort(e.begin(),e.end());
    }

    void dfs(int startNode){
        using std::stack;

        struct dfsTemp{
        int const N;
        enum COLOR{
            WHITE,
            GRAY,
            BLACK};
        vector<int> startTime,endTime, vizited;
        int time = 0;

        dfsTemp(int N):N(N){
            vizited.resize(N);
            std::fill(vizited.begin(),vizited.end(),COLOR::WHITE);
            startTime.resize(N),endTime.resize(N);
        }
        void dfs(Graf g,int node){
            vizited[node] = COLOR::GRAY;
            time++;
            startTime[node] = time;

            dfsout << node <<' ';

            for(Edge e:g.edges[node]){
                if(vizited[e.first] == COLOR::WHITE)
                    dfs(g,e.first);
            }
            vizited[node] = COLOR::BLACK;
            endTime[node]=time;

        }

        } g(N);
        g.dfs(*this,startNode);
    }
};
void runDFS(){
    Graf<void*> g(100);
    std::cin >> g;
    g.sortEdges();
    g.dfs(thestart);
}
*/

namespace SortareTopologica{
    /// 	05 Februarie 2022
using namespace std;
ifstream fin("topsort.in");
ofstream fout("topsort.out");
int const N=100005;
vector <int> v[N];
int n,m,grd[N];
void top()
{
    queue <int> q;
    for(int i=1;i<=n;i++)
        if(!grd[i])
            {q.push(i);
            fout<<i<<' ';}
    while(q.size())
    {
        int nod=q.front();
        vector <int>::iterator it;
        for(it=v[nod].begin();it!=v[nod].end();it++)
        {
            grd[*it]--;
            if(!grd[*it])
            {

                q.push(*it);
                if(!grd[*it])
                    fout<<*it<<' ';
            }
        }
        q.pop();
    }
}
void run()
{
    fin>>n>>m;
    while(m--)
    {
        int x,y;
        fin>>x>>y;
        grd[y]++;

        v[x].push_back(y);
    }
    top();
}
}

namespace RoyFloyd{
    /// 	17 Martie 2022
using namespace std;
int const N=105,inf=(int)1e9;
int a[N][N],n;
ifstream fin("roy-floyd.in");
ofstream fout("roy-floyd.out");
void aa(int k,int i,int j)
{
    if(a[i][k]+a[k][j]<a[i][j])
        a[i][j]=a[i][k]+a[k][j];
}
void RF()
{
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(a[i][j]==0 && i!=j)
                a[i][j]=inf;
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                aa(k,i,j);
}
void afs()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            if(a[i][j]==inf)
                fout<<"-1 ";
            else
                fout<<a[i][j]<<' ';
        fout<<'\n';
    }
}
void run()
{
    int m;
    fin>>n>>m;
    while(m--)
    {
        int x,y,c;
        fin>>x>>y>>c;
        a[x][y]=c;
    }
    RF();
    afs();
}
}

namespace Dijkstra{
    /// 2022-03-24
using namespace std;
int const N=105;
ifstream fin("dijkstra.in");
ofstream fout("dijkstra.out");
int n,nx;
vector <pair<int,int>> v[N];
priority_queue <pair<int,int>> h;
int dp[N];
void solve(int start)
{
    fill(dp,dp+n+1,INT_MAX);
    dp[start]=0;
    h.push({0,start});
    while(!h.empty())
    {
        int cost=-h.top().first;
        int nod=h.top().second;
        h.pop();
        for(auto y:v[nod])
        {
            if(dp[y.first]>cost+y.second)
            {
                dp[y.first]=cost+y.second;
                h.push({-dp[y.first],y.first});
            }
        }
    }
}
void run()
{
    fin>>n>>nx;
    int x,y,c;
    while(fin>>x>>y>>c)
        v[x].push_back({y,c});
    solve(nx);
    for(int i=1;i<=n;i++)
    {
        if(dp[i]==INT_MAX)
            fout<<"-1 ";
        else
            fout<<dp[i]<<' ';
    }
}
}

namespace bfs{
/// 05 Februarie 2022, pbinfo
using namespace std;
ifstream fin("BFS.in");
ofstream fout("BFS.out");
int const N=(int)1e5+5;
vector <int> v[N];
int n,m,s,d[N];
void BFS(int start)
{
    queue <int>q;
    q.push(s);
    fout<<s<<' ';
    d[s]=1;
    while(q.size())
    {
        int nod=q.front();
        vector <int>::iterator it;
        for(it=v[nod].begin();it!=v[nod].end();it++)
        {
            if(!d[*it])
            {
                fout<<*it<<' ';
                d[*it]=d[nod]+1;
                q.push(*it);
            }
        }
        q.pop();
    }
}
void run()
{
    fin>>n>>m>>s;
    int x,y;
    while(m--)
    {
        fin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for(int i=1;i<=n;i++)
        sort(v[i].begin(),v[i].end());
    BFS(s);
}
}


/// luata de pe infoarena de la mine dar nici nu compileaza lol (si e in general f dubioasa)
namespace domino{
using namespace std;
ifstream fin("domino.in");
ofstream fout("domino.out");
#define cin fin
#define cout fout
int const N =50005;
int m;
struct info
{
    int nod,pos;
    bool intors = false;
    info(int nod,int pos,bool intors):nod(nod),pos(pos),intors(intors){}
    bool operator==(const info a)const{
        return a.pos == pos;}
};
class hashh
{
    public:
    int operator()(const info &val)const
    {return hash<int>()(val.pos);}
};
unordered_multiset<info,hashh> v[22];
bool viz[22];
void dfs(int node,int pos=-1,bool type=false)
{
    while(!v[node].empty())
    {
        info del = *(v[node].begin());
        v[node].erase(del);
        v[del.nod].erase(del);
        dfs(del.nod,del.pos,!del.intors);
    }
    if(pos != -1)
        cout << pos <<' '<< type <<'\n';
}
int run()
{
    cin>>m;
    int alfa = -1;
    for(int i=0;i<m;i++)
    {
        int x,y;
        cin >> x >> y;
        v[x].emplace(y,i+1,false);
        v[y].emplace(x,i+1,true);
        alfa = x;
    }
    int nr1=-1,nr2=-1;
    for(int i=0;i<20;i++)
        if(v[i].size()%2)
        {
            if(nr1 == -1) nr1 = i;
            else if(nr2 == -1)nr2 = i;
            else{cout << 0;return 0;}
        }
    if(nr2 == -1 && nr1!= -1){cout << 0;return 0;}
    cout << "1\n";
    if(nr1==-1)
        dfs(alfa);
    else
        dfs(nr1);
    return 0;
}
}


namespace hamilton{

    #ifdef fakeFILES
    std::ifstream fin("input.in");
    std::ofstream fout("input.out");
    #else
    std::ifstream fin("hamilton.in");
    std::ofstream fout("hamilton.out");
    #endif
    int n;
    int const INF = 2e7;
    vector< vector< std::pair<int,int> > >  g;
    int hamilton(vector< vector< std::pair<int,int> > > g = g){

        int m[n + 2][n + 2];
        for(int i = 0; i < n; i++ ){
            for(int j = 0; j < n; j ++){
                if(i == j)
                    m[i][j] = 0;
                else
                    m[i][j] = INF;
            }
        }
        for(int i = 0; i < n; i++ ){
            for(size_t j = 0; j < g[i].size(); j ++){
                m[i][g[i][j].first] = g[i][j].second;
                ///std::cout << i << ' ' << g[i][j].first << ' ' << m[i][g[i][j].first] << '\n';
            }
        }


        int din[n + 2][(1<<n) + 2];
        /// din = C[j][k] = min lantului de la 0 la k care contine toate nodurile din binarul lui j
        din[0][0] = 0;
        for (int j = 1; j < (1<<(n-1)); j++){
            for(int k = 1; k < n ; k ++){
                din[k][j] = INF;
                int p = (1<<k)/2;

                if(p > j)
                    break;


                if( !(p & j))
                    continue;

                //std::cout << din[2][6] << "    ";
                int jc = j - p;
                if(jc == 0){
                    din[k][j] = m[0][k];

                    //std::cout << k<< ' ' << j << ' ' << din[k][j] << '\n';

                    continue;
                }

                while(jc > 0){
                    int lsb = jc & (-jc);
                    jc -= lsb;
                    int node = std::log2(lsb) + 1;
                    if(m[node][k] != INF && din[node][j - p] < INF)
                        din[k][j] = std::min(din[k][j], din[node][j - p] + m[node][k]);
                }

                //std::cout << k<< ' ' << j << ' ' << din[k][j] << '\n';
            }
        }
        int sol = INF, j = (1<<(n-1)) - 1;
        for(int k = 1; k< n; k++){
            if(din[k][j] < INF && m[k][0] != INF)
                sol = std::min(sol, din[k][j] + m[k][0]);
        }

        if(sol == INF)
            return -1;
        return sol;
    }
    void run(){
        int m;
        fin >> n >> m;
        g.resize(n);
        while(m--){
            int u,v,c;
            fin >> u  >> v >> c;
            g[u].emplace_back(v,c);
        }
        int rez = hamilton(g);
        if(rez == -1)
            fout << "Nu exista solutie";
        else
            fout << rez;

    }

}



int main()
{
    hamilton::run();
}
