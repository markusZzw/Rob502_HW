#include <cmath>
#include <fstream>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

// iterative version of binary search; you should handle the case when the
// element is not in the sequence
template <typename T>
int iterativeBinarySearch(const std::vector<T>& vals, T key,
                          int& numTimesCalled) {
    // --- Your code here
    int L = 0;
    int R = vals.size()-1;
    while(L <= R){
        numTimesCalled+=1;
        int mid = L + (R-L)/2;
        if (vals[mid] < key){
            L = mid+1;
        }else if(vals[mid] > key){
            R = mid-1;
        }else{
            return mid;
        }
    }
    return -1;
    // ---
}

template <typename T>
int recursiveBinarySearch(const std::vector<T>& vals, T key, int l, int r,
                          int& numTimesCalled) {
    // --- Your code here
    numTimesCalled++;
    if(l > r){
        return -1;
    }
    int mid = l + (r -l)/2;
    if(vals[mid]==key){
        return mid;
    }else if(vals[mid] < key){
        return recursiveBinarySearch(vals, key, mid+1, r, numTimesCalled);
    }else{
        return recursiveBinarySearch(vals, key, l,mid-1, numTimesCalled);
    }
    // ---
}

int main() {
    std::ifstream input{"input.txt"};
    std::ofstream output{"output.txt"};

    std::string line;

    int num;
    while (input.peek() != EOF) {
        std::vector<int> nums;
        int num;
        while ((input.peek() != '\n') && (input >> num)) {
            nums.push_back(num);
        }
        if (input.peek() == '\n') {
            input.get();
        }
        int lookup;
        input >> lookup;
        if (input.peek() == '\n') {
            input.get();
        }

        int numIterativeCalled = 0;
        int numRecursiveCalled = 0;

        int indexIterative =
            iterativeBinarySearch(nums, lookup, numIterativeCalled);

        int indexRecursive = recursiveBinarySearch(
            nums, lookup, 0, nums.size() - 1, numRecursiveCalled);

        if (indexIterative != indexRecursive) {
            output << "inconsistent indices found via iterative and recursive binary search\n";
        }

        if (indexIterative == -1) {
            output << "ERROR" << std::endl;
        } else {
            output << indexIterative << ' ' << numIterativeCalled << ' '
                << numRecursiveCalled << std::endl;
        }
    }
}