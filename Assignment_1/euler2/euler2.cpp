#include <iostream>
#include <string>

int main() {
    // you'll need to store the answer in a variable named 'sum'
    // --- Your code here
    unsigned long sum = 2;
    int x1=1;
    int x2=2;
    int now=x1+x2;
    while(now<=4000000){
        if(now%2==0){
           sum=sum + now;
        }
        x1=x2;
        x2=now;
        now=x1+x2;
    }

    // ---
    std::cout << sum << std::endl;
    return 0;
}