#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

typedef pair<int, int> nodeDistance;
typedef vector<vector<nodeDistance>> Graph;

class NoPathExistsException: public runtime_error {
public:
    NoPathExistsException() : runtime_error("No path exists between the nodes.") {}
};

class sssp{
    private:
        Graph graph;
        vector<int> distances;
        vector<int> parents;
        static constexpr int UNKNOWN = -1;
        void dijkstra(int n){
            auto comparator = [](nodeDistance a, nodeDistance b){
                return a.second > b.second || a.second == b.second && a.first > b.first;
            };
            priority_queue<nodeDistance, vector<nodeDistance>, decltype(comparator)> distanceQueue(comparator);
            vector<bool> visited(this->graph.size(), false);

            distanceQueue.push(make_pair(n, 0));
            parents[n] = n;
            distances[n] = 0;

            while (!distanceQueue.empty()) {
                auto [u, distance] = distanceQueue.top();
                distanceQueue.pop();
                if (visited[u]) continue;
                visited[u] = true;

                for (auto [v, weight] : this->graph[u]) {
                    if (distances[v] == UNKNOWN || distances[u] + weight < distances[v]) {
                        distances[v] = distances[u] + weight;
                        parents[v] = u;
                        distanceQueue.push(make_pair(v, distances[v]));
                    }
                }
            }

        }
    public:
        sssp(Graph &_graph)
        :graph { _graph }
        ,distances{vector<int>(graph.size(), UNKNOWN)}
        ,parents{vector<int>(graph.size(), UNKNOWN)}
        {}

        pair<int,vector<int>> shortestPath(int start,int end){
            this->dijkstra(start);
            if(this->parents[end] == UNKNOWN){
                throw NoPathExistsException();
            }   
            
            int distance = this->distances[end];

        // reconstruct the path from parents
        vector<int> path;
        path.push_back(end);
        int current = end;
        while (current != start) {
            current = parents[current];
            path.push_back(current);
        }

        std::reverse(path.begin(), path.end());
        return make_pair(distance, path);
        }

        

};
int main(){
    int n = 5;
    Graph graph(n);
    vector<tuple<int, int, int>> edges {
        make_tuple(0, 1, 6),
        make_tuple(0, 2, 10),
        make_tuple(0, 3, 4),
        make_tuple(1, 0, 2),
        make_tuple(1, 2, 3),
        make_tuple(1, 4, 5),
        make_tuple(3, 1, 1),
        make_tuple(3, 4, 2),
        make_tuple(4, 2, 1)
    };
    for (auto [u, v, w] : edges) {
        graph[u].push_back(make_pair(v, w));
    }

    sssp dijkstra(graph);
    auto [distance, path02] = dijkstra.shortestPath(0, 2);
    cout << "Shortest path from 0 to 2: ";
    for (int u : path02) {
        cout << u << " ";
    }
    cout << endl << "Length of the path: " << distance;
    cout << endl;
    return 0;
}
