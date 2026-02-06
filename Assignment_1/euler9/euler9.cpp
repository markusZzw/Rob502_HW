#include <iostream>

int euler9() {
    // --- Your code here
    for(int a=1; a<1000; a++){
        for(int b=1; b<1000; b++){
            int c=1000-a-b;
            if(c>0 && a*a+b*b == c*c){
                   int product = a*b*c;
                   return product;
            }
        }
    }
    return 0;
    // ---
}

int main() {
    // This code is a lot cleaner if you write it as a function, because you can use `return` once you find the answer
    int const product = euler9();
    std::cout << product << std::endl;
    return 0;
}