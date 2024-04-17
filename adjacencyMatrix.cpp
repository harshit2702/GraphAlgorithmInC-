#include <vector>
#include <iostream>
#include <tuple>
using namespace std;

 class AdjacencyMatrix {
private:
    vector<bool> adj;
    int n;
public:
  AdjacencyMatrix(int _n) 
      : n {_n} 
      , adj {vector<bool>(_n*_n, 0)}
  {}
  void addEdge(int source, int target) {
      this->adj[this->n * source + target] = true;
  }
  void removeEdge(int source, int target) {
      this->adj[this->n * source + target] = false;
  }
  bool getEdge(int source, int target) {
      return this->adj[this->n * source + target];
  }
};

int main() {
    int n = 4;
    vector<vector<int>> adjacencyMatrix(n, vector<int>(n, 0)); // initialize with zeros

    // add edges using a loop over a vector of (source, target) pairs
    vector<pair<int, int>> edges {{0, 1}, {1, 0}, {1, 2}, {1, 3}, {2, 0}, {2, 3}};
    for (auto [u, v] : edges) {
        adjacencyMatrix[u][v] = 1;
    }
    cout << "Edge from 0 to 1: " << adjacencyMatrix[0][1] << endl;
    cout << "No edge from 0 to 3: " << adjacencyMatrix[0][3] << endl;

    // print the adjacency matrix
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }

    AdjacencyMatrix adjacencyMatrix2(n); // create empty matrix

    // add edges using a loop over a vector of (source, target) pairs
    vector<pair<int, int>> edges2 {{0, 1}, {1, 0}, {1, 2}, {1, 3}, {2, 0}, {2, 3}};
    for (auto [u, v] : edges2) {
        adjacencyMatrix2.addEdge(u, v);
    }
    cout << boolalpha; // print booleans as true / false
    cout << "Edge from 0 to 1: " << adjacencyMatrix2.getEdge(0, 1) << endl;
    cout << "No edge from 0 to 3: " << adjacencyMatrix2.getEdge(0, 3) << endl;
    cout << "Adjacency Matrix2:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << adjacencyMatrix2.getEdge(i, j) << " ";
        }
        cout << endl;
    }
    adjacencyMatrix2.addEdge(0, 3);
    adjacencyMatrix2.removeEdge(1, 0);
    cout << "Adjacency Matrix2:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << adjacencyMatrix2.getEdge(i, j) << " ";
        }
        cout << endl;
    }
    vector<vector<int>> weightedAdjacencyMatrix(n, vector<int>(n, 0)); // initialize with zeros

    // add edges using a loop over a vector of (source, target, weight) tuples
    vector<tuple<int, int, int>> weightedEdges {
        make_tuple(0, 1, 5), 
        make_tuple(1, 0, 3), 
        make_tuple(1, 2, 7), 
        make_tuple(1, 3, 4), 
        make_tuple(2, 0, 11), 
        make_tuple(2, 3, 4)
    };
    for (auto [v, u, w] : weightedEdges) {
        weightedAdjacencyMatrix[v][u] = w;
    }
    cout << "Edge from 0 to 1: weight " << weightedAdjacencyMatrix[0][1] << endl;
    cout << "No edge from 0 to 3: " << weightedAdjacencyMatrix[0][3] << endl;
    cout << "Weighted Adjacency Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << weightedAdjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }



    return 0;
}

