#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>

int main()
{
    double a, b, c;
    std::cout << "Type in a, b, and c. Press 'Enter' between each\n";
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    std::cout << std::setprecision(4);
    // --- Your code here
    double x2=0;
    double x1=0;
    double deter = b*b - 4*a*c;
    if (deter > 0){
        x2=(-b-sqrt(deter))/(2*a);
        x1=(-b+sqrt(deter))/(2*a);
        std::cout << x2 << std::endl;
        std::cout << x1 << std::endl;
    } else if(deter ==0){
        x2=(-b-sqrt(deter))/(2*a);
        if (x2 == 0){
            std::cout << std::abs(x2) << std::endl;
        }else{
            std::cout << x2 << std::endl;
        }
    } else{
        std::cout << "None" << std::endl;
    }
    
    // ---
    return 0;
}