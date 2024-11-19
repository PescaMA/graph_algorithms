#include <iostream>
#include <vector>
#include <fstream>
using std::vector,std::pair;

template<typename T, typename Y>
auto operator<<(std::ostream& stream, std::pair<T,Y> const& p) -> std::ostream& {
    stream << '(' << p.first << ' ' << p.second << ')';
    return stream;
}

template <class t=pair<int,int>>
class Graf{
    const int N;
    int n;
    vector<vector<t>>v;

    public:
    ///CONSTRUCTORS:
    Graf(int MAX_N):N(MAX_N){
        v.reserve(N);
        v[N-1].push_back({2,3});
    }

    /// OPERATORS:
    vector<t> operator[](size_t i){
        return v[i];
    }
    friend std::istream operator>>(std::istream& fin, Graf g){
        int n, m, x;
        t nod;
        fin >> n >> m;
        while(m--){
            fin >> x >> nod;
            g[x].push_back(nod);
        }
        return fin;
    }
    friend std::ostream& operator<<(std::ostream& fout, Graf g){
        for(size_t i =0 ; i < g.v.size(); i++){
            fout << i << ' ';
            for(auto x:g[i])
                fout << x << ' ';
            fout << '\n';
        }
        return fout;
    }
    /// ACTUAL FUNCTIONS:

    void print(){
        std::cout << "HMM";
    }
};


int main()
{
    Graf g(100);
    std::cout << g;
    g.print();
}
