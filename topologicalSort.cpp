#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef vector<vector<int>> Graph;
enum class NodeState { UNVISITED, VISITING, EXPLORED };

class topologicalSort{
    private:
    Graph graph;
    vector<NodeState> state;

    vector<int> topologicalOrder;
    public:
    topologicalSort(Graph &_graph)
    : graph {_graph}
    , state{ vector<NodeState>(graph.size(), NodeState::UNVISITED) }
    {}

    void dfs(int u){
        this->state[u] = NodeState::VISITING;
        for(int v: this->graph[u]){
            switch (this->state[v])
            {
            case NodeState::UNVISITED:
                this->state[v] = NodeState::VISITING;
                dfs(v);
                break;
            case NodeState::VISITING:
                throw runtime_error("Cycle detected.");
                break;
            
            case NodeState::EXPLORED:
                break;
            }
        }
        this->state[u] = NodeState::EXPLORED;
        this->topologicalOrder.push_back(u);
    }

    vector<int> computeTopologicalOrder(){
        for(int u = 0; u < this->graph.size(); u++){
            if(this->state[u] == NodeState::UNVISITED){
                this->dfs(u);
            }
        }
        reverse(this->topologicalOrder.begin(), this->topologicalOrder.end());
        return this->topologicalOrder;
    }

};
int main() {
    int n = 5;
    Graph graph(n);
    vector<pair<int, int>> edges {{0, 1}, {0, 4}, {2, 4}, {2, 1}, {3, 0}, {4, 1}};
    for (auto [u, v] : edges) {
        graph[u].push_back(v);
    }

    topologicalSort topologicalSort(graph);
    vector<int> topSort = topologicalSort.computeTopologicalOrder();
    cout << "Topological sort:";
    for (int u : topSort) {
        cout << " " << u;
    }
    cout << endl;
    return 0;
}
