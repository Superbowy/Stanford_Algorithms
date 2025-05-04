#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

void print_vec(vector<int>& vec);
vector<int> merge_sort(vector<int> vec);
vector<int> merge(vector<int>& A, vector<int>& B);

int main(){
    vector<int> to_sort = {34, 72, 19, 85, 41, 56, 97, 12, 63, 8, 54, 20, 89, 37, 2, 46, 91, 65, 23, 77};

    cout << "Initial array : " << endl;
    print_vec(to_sort);

    to_sort = merge_sort(to_sort);
   
    cout << endl << "Sorted array: " << endl;
    print_vec(to_sort);
    
    return 0;
}

vector<int> merge_sort(vector<int> vec){
    if (vec.size() == 1) return vec;

    int split = vec.size() / 2;
    
    vector<int> A(vec.begin(), vec.begin() + split);
    vector<int> B(vec.begin() + split, vec.end());

    A = merge_sort(A);
    B = merge_sort(B);

    return merge(A, B);
}

vector<int> merge(vector<int>& A, vector<int>& B){
    int i = 0;
    int j = 0;

    vector<int> result;

    while(i < A.size() && j < B.size()){
        if(A[i] < B[j]){
            result.push_back(A[i]);
            i++;
        } else {
            result.push_back(B[j]);
            j++;
        }
    }

    result.insert(result.end(), A.begin() + i, A.end());
    result.insert(result.end(), B.begin() + j, B.end());

    return result;
}

void print_vec(vector<int>& vec){
    for(int i = 0; i<vec.size(); i++){
        cout << vec[i] << " ";
    }
}
