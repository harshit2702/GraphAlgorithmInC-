#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Graph;

enum class node_state{
    unvisited,
    visited,
    visiting
};

class cycleDetector{
    private:
        const Graph graph;
        vector<node_state> state;
        bool hasCycle = false;

    public:
        cycleDetector(Graph _graph)
            : graph(_graph), 

            state{vector<node_state>(graph.size(), node_state::unvisited)}
            {}
        void dfs(int u){
            this->state[u] = node_state::visiting;

            for(int v: this->graph[u]){
                switch(this->state[v]){
                    case node_state::unvisited:
                        this->dfs(v);
                        break;
                    case node_state::visiting:
                        this->hasCycle = true;
                        break;
                    case node_state::visited:
                        break;
                }
            }

            this->state[u] = node_state::visited;
    
        }
        bool contiansCycle(){
            for(int u = 0; u < this->graph.size(); u++){
                if(this->state[u] == node_state::visited){
                    continue;;
                }
                dfs(u);
            }
            return this->hasCycle;
        }

};
int main(){
    cout<<"Depth First Search\n";
    int n = 5;
    Graph graph(n);
    vector<pair<int, int>> edges = {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 4},
        {2, 4}
    };
    for(auto[u, v]: edges){
        graph[u].push_back(v);
    }   
    cout<<"Graph has cycle: "<<cycleDetector(graph).contiansCycle()<<endl;
    return 0;
}