#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void print_vec(std::vector<int> &vertices);
void parse_data(std::string fileName, std::vector<int> &vertices, std::vector<std::vector<int>> &edges);
void contract(std::vector<int> &vertices, std::vector<std::vector<int>> &edges);

int main() {
	int min = 1000000;
	for (int i = 0; i < 1000; i++) {
		std::vector<int> vertices;
		std::vector<std::vector<int>> edges;

		parse_data("kargerMinCut.txt", vertices, edges);
		contract(vertices, edges);
		if (min > edges[vertices[0] - 1].size()) {
			min = edges[vertices[0] - 1].size();
		}
	}
	std::cout << "Minimum found out of 1000 attempts : " << min << "\n";
	return 0;
}
void contract(std::vector<int> &vertices, std::vector<std::vector<int>> &edges) {
	std::srand(std::time(NULL));

	while (vertices.size() > 2) {
		int i = std::rand() % vertices.size();
		int v1 = vertices[i];

		std::vector<int> &v1_edges = edges[v1 - 1];
		int v2 = v1_edges[std::rand() % v1_edges.size()];

		for (int e : edges[v2 - 1]) {
			if (e != v1) {
				edges[v1 - 1].push_back(e);
			}
		}

		for (auto &adj : edges) {
			for (int &val : adj) {
				if (val == v2)
					val = v1;
			}
		}

		std::vector<int> &new_edges = edges[v1 - 1];
		new_edges.erase(std::remove(new_edges.begin(), new_edges.end(), v1), new_edges.end());

		vertices.erase(std::remove(vertices.begin(), vertices.end(), v2), vertices.end());

		edges[v2 - 1].clear();
	}
}

void parse_data(std::string fileName, std::vector<int> &vertices, std::vector<std::vector<int>> &edges) {
	std::ifstream file(fileName);

	if (!file) {
		std::cout << "Failed to open the file.\n";
		return;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string token;
		std::vector<int> current_edges;

		std::getline(ss, token, '\t');
		int vertex = std::stoi(token);
		vertices.push_back(vertex);

		while (std::getline(ss, token, '\t')) {
			if (!token.empty() && token.find_first_not_of(" \n\r\t") != std::string::npos) {
				current_edges.push_back(std::stoi(token));
			}
		}

		edges.push_back(current_edges);
	}

	file.close();
}

void print_vec(std::vector<int> &A) {
	for (int i = 0; i < A.size(); i++) {
		std::cout << A[i] << "\n";
	}
}
