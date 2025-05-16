#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int MAX_NODES = 875714;

vector<vector<int>> graph(MAX_NODES + 1);
vector<vector<int>> reversed_graph(MAX_NODES + 1);
vector<bool> visited(MAX_NODES + 1, false);
stack<int> finishing_order;
vector<int> scc_sizes;

void dfs1(int node) {
    visited[node] = true;
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) dfs1(neighbor);
    }
    finishing_order.push(node);
}

void dfs2(int node, int& size) {
    visited[node] = true;
    size++;
    for (int neighbor : reversed_graph[node]) {
        if (!visited[neighbor]) dfs2(neighbor, size);
    }
}

int main() {
    ifstream infile("SCC.txt");
    int tail, head;
    while (infile >> tail >> head) {
        graph[tail].push_back(head);
        reversed_graph[head].push_back(tail);
    }

    fill(visited.begin(), visited.end(), false);
    for (int i = 1; i <= MAX_NODES; ++i) {
        if (!visited[i]) dfs1(i);
    }

    fill(visited.begin(), visited.end(), false);
    while (!finishing_order.empty()) {
        int node = finishing_order.top();
        finishing_order.pop();
        if (!visited[node]) {
            int size = 0;
            dfs2(node, size);
            scc_sizes.push_back(size);
        }
    }

    sort(scc_sizes.rbegin(), scc_sizes.rend());
    for (int i = 0; i < 5; ++i) {
        if (i < scc_sizes.size()) cout << scc_sizes[i];
        else cout << 0;
        if (i != 4) cout << ",";
    }
    cout << endl;
    return 0;
}

