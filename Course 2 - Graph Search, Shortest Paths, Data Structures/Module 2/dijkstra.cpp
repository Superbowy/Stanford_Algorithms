#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

typedef std::vector<std::vector<std::pair<int, int>>> graph_;

void load_data(graph_ &graph) {
	std::ifstream file("djikstra.txt");
	std::string line;

	while (std::getline(file, line)) {
		std::vector<std::pair<int, int>> pairs;

		std::istringstream ss(line);
		std::string neighbor_info;

		while (ss >> neighbor_info) {
			size_t comma_pos = neighbor_info.find(',');
			if (comma_pos != std::string::npos) {
				int neighbor = std::stoi(neighbor_info.substr(0, comma_pos));
				int distance = std::stoi(neighbor_info.substr(comma_pos + 1));

				pairs.push_back(std::pair(distance, neighbor - 1));
			}
		}
		graph.push_back(pairs);
	}
}

const int djikstra(graph_ &graph, int target, int source = 0) {

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
	std::vector<int> distances(graph.size(), 1e9);
	std::vector<bool> visited(graph.size(), false);

	distances[source] = 0;
	pq.push(std::pair(0, source));

	while (true) {
		int curr = pq.top().second;
		pq.pop();

		if (curr == target) {
			return distances[curr];
		}

		for (std::pair<int, int> &p : graph[curr]) {
			if (!visited[p.second]) {
				int neighbor = p.second;
				int dist_neighbor = p.first;
				if (distances[neighbor] > distances[curr] + dist_neighbor) {
					distances[neighbor] = distances[curr] + dist_neighbor;
					pq.push(std::pair(distances[curr] + dist_neighbor, neighbor));
				}
			}
		}
		if (pq.size() == 0) {
			return 0;
		}
		visited[curr] = true;
	}
}

int main() {

	graph_ graph;

	load_data(graph);
    
    std::vector<int> goals = {7,37,59,82,99,115,133,165,188,197};

    for(int &goal : goals){

	std::cout << djikstra(graph, goal - 1) << ",";

    }

	return 0;
}
