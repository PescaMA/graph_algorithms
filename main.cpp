#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>

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
