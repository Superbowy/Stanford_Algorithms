#include <fstream>
#include <iostream>
#include <vector>

void print_vec(std::vector<int> &vec);
void quick_sort(std::vector<int> &A, long long left, long long right);
long long partition(std::vector<int> &A, long long left, long long right);

int main() {
	// std::vector<int> to_sort = {34, 72, 19, 85, 41, 56, 97, 12, 63, 8,
	//                            54, 20, 89, 37, 2,  46, 91, 65, 23, 77};

	std::ifstream file("IntegerArray.txt");
	std::vector<int> to_sort;

	int x;

	while (file >> x) {
		to_sort.push_back(x);
	}

	std::cout << "Initial array : " << std::endl;
	print_vec(to_sort);

	quick_sort(to_sort, 0, to_sort.size() - 1);

	std::cout << std::endl << "Sorted array: " << std::endl;
	print_vec(to_sort);
	return 0;
}

void quick_sort(std::vector<int> &A, long long left, long long right) {

	if (left < right && A.size() > 1) {
		// Can also be random, or last element of A;
		long long split = partition(A, left, right);

		quick_sort(A, left, split - 1);
		quick_sort(A, split + 1, right);
	}
}

long long partition(std::vector<int> &A, long long left, long long right) {
	int pivot = A[left];
	long long i = left;

	for (long long j = left + 1; j <= right; j++) {
		if (A[j] < pivot) {
			i++;
			std::swap(A[i], A[j]);
		}
	}
	std::swap(A[i], A[left]);
	return i;
}

void print_vec(std::vector<int> &A) {

	for (long long i = 0; i < A.size(); i++) {
		std::cout << A.at(i) << " ";
	}
}
