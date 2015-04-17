#include <vector>
#include <utility>
#include <queue>

struct edge {
    edge(int _to, int _cost) : to(_to), cost(_cost) {};
    int to, cost;
};
typedef std::vector<std::vector<edge>> Graph;
std::vector<int> dijkstra(const Graph &graph, const int s){
    typedef std::pair<int, int> P;
    const int INF = 1e9;
    int V = graph.size();
    std::vector<int> dist(V, INF);
    std::vector<bool> used(V, false);
    std::priority_queue<P, std::vector<P>, std::greater<P>> q;
    q.push(P(0, s));
    while(!q.empty()){
        P current = q.top(); q.pop();
        int d = current.first;
        int current_node = current.second;
        if(used[current_node]) continue;
        used[current_node] = true;
        dist[current_node] = d;
        for(edge e: graph[current_node]){
            if(dist[e.to] <= d + e.cost) continue;
            q.push(P(d+e.cost, e.to));
        }
    }
    return dist;
}
