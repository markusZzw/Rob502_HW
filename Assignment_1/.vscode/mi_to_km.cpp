#include <iostream>
#include <iomanip>


int main() {
    double input, output=0;
    std::cout << "Type the Mile: ";
    std::cin >> input;
    output=input*1.609344;
    std::cout <<  std::setprecision(3) << output << std::endl;
    return 0;
}
