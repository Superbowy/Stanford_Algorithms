#include "bfs_graph.h"
#include "load_al_graph.h"
#include <vector>

int main() {

	std::vector<int> vertices;
	std::vector<std::vector<int>> edges;

	load_al_graph("long_graph.txt", vertices, edges);

    compute_bfs(vertices, edges, 5, 129);
	return 0;
}
