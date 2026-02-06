// --- Your code here
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>


std::string repeatString(std:: string a, int b){
    std:: string result;
    if(b==0){
        result="";
    }else{
        for(int i=0;i<b;i++){
            result+=a;
        }
    }
    return result;
}

long double multiply(long long a, long long b){
    return static_cast<long double>(a)*static_cast<long double>(b);
}

// ---

// include the standard library files that defines the std:: functions
int main() {
    // --- Your code here
    double some_number;
    std:: string some_string;
    long long large_number;
    long long even_larger_number;
    int negative_number;

    // ---
    
	// declare the variables used below
	some_number = 5.5;
    // std::endl and '\n' are equivalent
	std::cout << some_number << ' ' << std::round(some_number + M_PI) << '\n';

    // this one may be a bit tricky since you can't assign a string literal to char* in C++ 
	some_string = "my string";
	std::cout << some_string << '\n';

    // implement this function
    // should print empty string
    std::cout << repeatString(some_string, 0) << std::endl;
    // should print it 5 times, with nothing separating them
    std::cout << repeatString(some_string, 5) << std::endl;
	
	// there are many numerical types, each with different signedness and size
	// declare the appropriate types for them such that none of them overflow
    // note that 2^32 ~= 4 billion
    large_number = 1000000;
    large_number *= 3;
    std::cout << large_number << std::endl;

    even_larger_number = large_number * large_number;
    std::cout << even_larger_number << std::endl;

    // implement this multiply function
    std::cout << std::fixed << std::setprecision(1) << multiply(large_number, even_larger_number) << std::endl;

    // beware of numeric types' signedness
    negative_number = -250;
    std::cout << negative_number << std::endl;
}