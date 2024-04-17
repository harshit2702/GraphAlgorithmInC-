#include <vector>
#include <iostream>
using namespace std;

int main() {
    int n = 4;
    vector<vector<int>> adjacencyList(n); // create empty adjacency list

    // add edges using a loop over a vector of (source, target) pairs
    vector<pair<int, int>> edges {{0, 1}, {1, 0}, {1, 2}, {1, 3}, {2, 0}, {2, 3}};
    for (auto [u, v] : edges) {
        adjacencyList[u].push_back(v);
    }

    cout << "Neighbors of node 1:";
    for (int u : adjacencyList[1]) {
        cout << " " << u;
    }
    cout << endl;

    return 0;
}