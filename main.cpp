#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void parallelScan(vector<int>& input,vector<int>& output) {
    int n = input.size();
    vector<int> temp(n);

    for (int twod = 1; twod < n; twod *= 2) {
        for (int i = twod; i < n; i += 2 * twod) {
            input[i] += input[i - twod];
        }
    }

    input[n - 1] = 0;

    for (int twod = n / 2; twod >= 1; twod /= 2) {
        for (int i = twod; i < n; i += 2 * twod) {
            int temp = input[i];
            input[i] += input[i - twod];
            input[i - twod] = temp;
        }
    }

    for (int i = 0; i < n; ++i) {
        output[i] = input[i];
    }
}

int main() {
    vector<int> input = {5, 1, 7, 0, 4, 1, 6, 3};
    vector<int> output(input.size());
    parallelScan(input, output);
    cout << "Input: ";
    for (int num : input) {
        cout << num << " ";
    }
    cout <<endl;
    cout << "Output: ";
    for (int num : output) {
        cout << num << " ";
    }
    cout <<endl;

    return 0;
}