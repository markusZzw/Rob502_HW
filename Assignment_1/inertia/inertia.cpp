#include <cmath>
#include <iostream>
#include <fstream>

int main()
{
    double mass, w, h, d;
    std::ifstream ifs("inertia_input.txt");
    ifs >> mass;
    ifs >> w;
    ifs >> h;
    ifs >> d;
    // you'll need to store the outputs in variables Ih, Iw, and Id.
    // --- Your code here
    double H = static_cast<double>(h);
    double W = static_cast<double>(w);
    double D = static_cast<double>(d);

    double Ih=mass*(pow(W,2) + pow(D,2))/12;
    double Iw=mass*(pow(D,2) + pow(H,2))/12;
    double Id=mass*(pow(W,2) + pow(H,2))/12;


    // ---
    std::cout << "<ixx>" << Ih << "</ixx>\n";
    std::cout << "<iyy>" << Iw << "</iyy>\n";
    std::cout << "<izz>" << Id << "</izz>\n";
    return 0;
}