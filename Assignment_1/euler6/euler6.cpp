#include <iostream>

int main() {
    // --- Your code here
    int sum1=0;
    int sum20=0;
    for(int i=1; i<=100; i++){
        sum1=sum1+i*i;
    }
    for(int j=1; j<=100; j++){
        sum20=sum20+j;
    }
    int sum2=sum20*sum20;
    int difference=sum2-sum1;


    // ---
    std::cout << difference << std::endl;
    return 0;
}