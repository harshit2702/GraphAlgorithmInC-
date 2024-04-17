#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

using namespace std;

typedef vector<vector<int>> Graph;
class NoPathExistsException: public runtime_error{
    public:
    NoPathExistsException() : runtime_error("No path exists between the nodes.") {}
};

class shortestPath{
    private:
    Graph graph;
    vector<int> distance;
    vector<int> parent;

    static constexpr int UNKNOWN = -1;
    public:
    shortestPath(Graph &_graph)
    : graph { _graph }
    , distance{ vector<int>(_graph.size(), UNKNOWN) }
    , parent{ vector<int>(_graph.size(), UNKNOWN) }
    {}

    void bfs(int start){
        this->distance.assign(this->graph.size(), UNKNOWN);
        this->parent.assign(this->graph.size(), UNKNOWN);
        queue<int> unexplored;
        unexplored.push(start);

        distance[start] = 0;
        parent[start] = start;

        // bfs main loop
        while (!unexplored.empty()) {
        int u = unexplored.front();
        unexplored.pop();
        for (int v : this->graph[u]) {
            if (this->parent[v] == UNKNOWN) {
                parent[v] = u;
                distance[v] = distance[u] + 1;
                unexplored.push(v);
                }
            }
        }
    }
    vector<int> computeShortestPath(int start, int end) {
    this->bfs(start);
    // end was not discovered -> no path
    if (this->parent[end] == UNKNOWN) {
        throw NoPathExistsException();
    }

    vector<int> path;
    path.push_back(end);
    int current = end;
    // go back along parents to build the path
    while (current != start) {
        current = parent[current];
        path.push_back(current);
    }
    // path was assembled in reverse order
    reverse(path.begin(), path.end());
    return path;
}


};

int main(){
    cout<<"Breadth First Search\n";
     int n = 6;
    Graph graph(n);
    vector<pair<int, int>> edges {{0, 1}, {0, 2}, {1, 3}, {2, 4}, {3, 0}, {3, 4}, {4, 3}, {4, 5}};
    for (auto [u, v] : edges) {
        graph[u].push_back(v);
    }

    shortestPath shortestPath(graph);
    vector<int> path04 = shortestPath.computeShortestPath(5, 0);
    cout << "Shortest path from 0 to 4: ";
    for (int u : path04) {
        cout << u << " ";
    }

    return 0;
}