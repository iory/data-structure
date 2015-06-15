#include <iostream>
#include <vector>
using namespace std;

class UnionFind
{
public:
    UnionFind(int N) : N(N)
        {
            init();
        };
    UnionFind(int N, int root_node)
        : N(N), root_node(root_node)
        {
            init();
        }
    ~UnionFind(){};
    friend std::ostream& operator<< (std::ostream& os, const UnionFind& cls) {
        os << "#<UnionFind root_node=" << cls.root_node << " N=" << cls.N;
        os << ">" << endl;
        return os;
    }
    int find(int x){
        if(par[x] == x)
            return x;
        else
            return par[x] = find(par[x]);
    }
    bool is_connected(int x, int y){
        return find(x) == find(y);
    }
    void unite(int x, int y){
        x = par[x];
        y = par[y];
        if(x==y)
            return;
        if(rank[x] < rank[y]){
            par[x] = y;
        } else {
            par[y] = x;
            if(rank[x] == rank[y])
                rank[x]++;
        }
    }
private:
    void init() {
        par = std::vector<int>(N, 0);
        rank = std::vector<int>(N, 0);
        for(int i=0;i<N;++i){
            par[i] = i;
        }
    }
    int N;
    int root_node;
    std::vector<int> par;
    std::vector<int> rank;
};


int main(){
    UnionFind uf(100);
    uf.unite(1, 2);
    cout << uf << endl;
    return 0;
}
