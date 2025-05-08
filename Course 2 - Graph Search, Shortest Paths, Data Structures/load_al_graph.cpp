#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

void load_al_graph(std::string fileName, std::vector<int> &vertices, std::vector<std::vector<int>> &edges) {
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
