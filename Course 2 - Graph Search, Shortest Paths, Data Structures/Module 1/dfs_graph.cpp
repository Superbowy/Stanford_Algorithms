#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void compute_dfs(std::vector<int> &vertices, std::vector<std::vector<int>> &edges, int root, int target) {

	std::unordered_set<int> explored{root};
	std::stack<int> S;
	std::unordered_map<int, int> parent;
	S.push(root);

	while (!S.empty()) {
		int v = S.top();
		S.pop();

		if (v == target)
			break;

		for (int neighbor : edges[v]) {
			if (!explored.contains(neighbor)) {
				explored.insert(neighbor);
				parent[neighbor] = v;
				S.push(neighbor);
			}
		}
	}

	if (target != -1) {
		if (!explored.contains(target)) {
			std::cout << "DFS Done. No path found";
		} else {
			std::cout << "DFS Done. Path: ";

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
		std::cout << "DFS Done.";
	}
}
