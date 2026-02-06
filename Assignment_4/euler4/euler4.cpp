#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
using namespace std;

bool isPalandrome(int num){
    string numStr = to_string(num);
    string reversed(numStr.rbegin(), numStr.rend());
    return numStr == reversed;
}

int main() {
    // HINT: consider using std::to_string and std::reverse
    unsigned long largest_palandrome{0};
    // --- Your code here
    for(int i=999; i>=100; i--){
        if(i*999 < largest_palandrome) break;
        for(int j=999; j>=i; j--){
            int product = i * j;
            if (product <= largest_palandrome) break;
            if (isPalandrome(product)) {
                largest_palandrome = product;
            }
        }
    }

    // ---
    std::cout << largest_palandrome << std::endl;
    return 0;
}