#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

long long count(vector<long long> &to_count, int left, int right,
                vector<long long> &buffer);
long long count_split_inv(vector<long long> &C, int left, int mid, int right,
                          vector<long long> &buffer);

int main() {
	// vector<long long> to_count = {1, 3, 5, 2, 4, 6};

	vector<long long> to_count;

	ifstream file("IntegerArray.txt");
	long long number;

	while (file >> number) {
		to_count.push_back(number);
	}

	vector<long long> buffer(to_count.size());

	long long answer = count(to_count, 0, to_count.size() - 1, buffer);
	cout << answer << endl;
	return 0;
}

long long count(vector<long long> &to_count, int left, int right,
                vector<long long> &buffer) {
	if (left >= right)
		return 0;

	long long mid = (left + right) / 2;

	long long x = count(to_count, left, mid, buffer);
	long long y = count(to_count, mid + 1, right, buffer);
	long long z = count_split_inv(to_count, left, mid, right, buffer);

	return x + y + z;
}

long long count_split_inv(vector<long long> &C, int left, int mid, int right,
                          vector<long long> &buffer) {
	long long i = left;
	long long j = mid + 1;
	long long k = left;
	long long count = 0;

	while (i <= mid && j <= right) {
		if (C[i] <= C[j]) {
			buffer[k++] = C[i++];
		} else {
			buffer[k++] = C[j++];
			count += (mid - i + 1);
		}
	}

	while (i <= mid)
		buffer[k++] = C[i++];
	while (j <= right)
		buffer[k++] = C[j++];

	for (long long l = left; l <= right; ++l) {
		C[l] = buffer[l];
	}

	return count;
}
