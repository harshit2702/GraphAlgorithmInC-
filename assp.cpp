#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef vector<vector<int>> Graph;

class NoPathExistsException: public runtime_error {
    public:
        NoPathExistsException() : runtime_error("No path exists between the nodes.") {}
};

class assp{
    private:
    Graph distanceMatrix;
    Graph predecessorMatrix;

    static constexpr int UNKNOWN = -1;
    static constexpr int infinity = 10000;

    void initialize(Graph const &graph){
        int n = graph.size();
        this->distanceMatrix = vector<vector<int>>(n, vector<int>(n, infinity));
        this->predecessorMatrix = vector<vector<int>>(n, vector<int>(n, UNKNOWN));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i == j){
                    this->distanceMatrix[i][j] = 0;
                    this->predecessorMatrix[i][j] = i;
                } else if(graph[i][j] > 0){
                    this->distanceMatrix[i][j] = graph[i][j];
                    this->predecessorMatrix[i][j] = i;
                }
            }
        }

    }
    void compute(){
        int n = distanceMatrix.size();

        for(int k = 0; k < n; k++){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(distanceMatrix[i][k] + distanceMatrix[k][j] < distanceMatrix[i][j]){
                        distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                        predecessorMatrix[i][j] = predecessorMatrix[k][j];
                    }
                }
            }
        }

    }

    
    public:
    assp(Graph const &_graph){
        this->initialize(_graph);
        this->compute();
    }

    pair<int,vector<int>> shortestPath(int start, int end){
        int distance = this->distanceMatrix[start][end];
        if(distance == infinity){
            throw NoPathExistsException();
        }
        vector<int> path {end};
        int current = end;
        while(current != start){
            current = this->predecessorMatrix[start][current];
            path.push_back(current);
        }
        reverse(path.begin(), path.end());
        return make_pair(distance, path);
    }

};
int main(){
    int n = 4;
    Graph graph(n, vector<int>(n, 0));
    vector<tuple<int, int, int>> edges {
        make_tuple(0, 1, 6), 
        make_tuple(0, 2, 3), 
        make_tuple(0, 3, 12), 
        make_tuple(1, 2, 9), 
        make_tuple(1, 3, 5), 
        make_tuple(2, 3, 2),
        make_tuple(3, 1, 4),
        make_tuple(3, 2, 1)
    };
    for (auto [v, u, w] : edges) {
        graph[v][u] = w;
    }
    assp a(graph);
    auto [distance, path] = a.shortestPath(0, 3);
    cout << "Shortest path from 0 to 3:";
    for (int u : path) {
        cout << " " << u;
    }
    cout << endl << "Length of the path: " << distance << endl;
    
    try {
        a.shortestPath(2, 0);
    } catch (NoPathExistsException exc) {
        cout << "No path from 2 to 0.";
    }  



    return 0;
}