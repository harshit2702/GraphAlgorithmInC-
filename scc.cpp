#include<iostream>
#include<vector>

using namespace std;

typedef vector<vector<int>> Graph;
enum class node_state{
    unvisited,
    visited,
    visiting
};

class stronglyConnectedComponent{
    private:
    Graph graph;
    vector<node_state> state;
    vector<int> finishOrder;

    vector<vector<int>> scc;

    void transpose(){
        Graph tmp = Graph(this->graph.size());
        for(int u = 0; u < this->graph.size(); u++){
            for(int v: this->graph[u]){
                tmp[v].push_back(u);
            }
        }
        this->graph = tmp;
    }
    public: 
    stronglyConnectedComponent(Graph _graph)
        : graph(_graph),
        state{vector<node_state>(graph.size(), node_state::unvisited)}
        {}

    void dfs(int u){
        this->state[u] = node_state::visiting;
        for(int v: this->graph[u]){
            if(this->state[v] == node_state::unvisited){
                this->dfs(v);
            }

        }
        this->state[u] = node_state::visited;
        this->finishOrder.push_back(u);
    }
    vector<vector<int>> computeSCC(){
        for(int u = 0; u < this->graph.size(); u++){
            if(this->state[u] == node_state::visited){
                continue;
            }
            this->dfs(u);
        }

        vector<int> traverseOrder(this->finishOrder.rbegin(), this->finishOrder.rend());
        this->transpose();
        fill(this->state.begin(), this->state.end(), node_state::unvisited);
        this->finishOrder.clear();

        for (int u : traverseOrder) {
            if (this->state[u] == node_state::unvisited) {
                this->dfs(u);
                this->scc.push_back(this->finishOrder);
                this->finishOrder.clear();
            }
        }

        this->transpose();
        fill(this->state.begin(), this->state.end(), node_state::unvisited);
        return this->scc;
    }
};
int main(){
    int n = 7;
    Graph adjacencyList(n);
    vector<pair<int, int>> edges {{0, 1}, {0, 6}, {1, 4}, {2, 3}, {2, 5}, {3, 2}, {3, 5}, {4, 0}, {4, 5}, {6, 4}};
    for (auto [u, v] : edges) {
        adjacencyList[u].push_back(v);
    }

    stronglyConnectedComponent components(adjacencyList);
    auto scc = components.computeSCC();
    cout << "Strongly connected components:" << endl;
    for (auto component : scc) {
        for (int u : component) {
            cout << u << " ";
        }
        cout << endl;
    }
    return 0;
}