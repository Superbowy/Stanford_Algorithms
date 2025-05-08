#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>

void compute_bfs(std::vector<int> &vertices, std::vector<std::vector<int>> &edges, int root, int target) {
	std::unordered_set<int> explored{root};
	std::queue<int> Q;
	std::unordered_map<int, int> parent;
	Q.push(root);

	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();

		if (v == target)
			break;

		for (int neighbor : edges[v]) {
			if (!explored.contains(neighbor)) {
				explored.insert(neighbor);
				parent[neighbor] = v;
				Q.push(neighbor);
			}
		}
	}
	if (target != -1) {
		if (!explored.contains(target)) {
			std::cout << "BFS Done. No path found";
		} else {
			std::cout << "BFS Done. Path: ";

			std::vector<int> path;
			for (int at = target; at != root; at = parent[at])
				path.push_back(at);
			path.push_back(root);
			std::reverse(path.begin(), path.end());

			for (size_t i = 0; i < path.size(); ++i) {
				std::cout << path[i];
				if (i != path.size() - 1)
					std::cout << " -> ";
			}
			std::cout << "\n";
		}
	} else {
		std::cout << "BFS Done.";
	}
}
