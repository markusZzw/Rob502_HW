#include <iostream>
#include <vector>
#include <iomanip>

using ObjMassPair = std::pair<std::string, double>; //this defines the type ObjMassPair to be std::pair<std::string, double>

//define the operator << here
//define a function that compares ObjMassPair objects here (for use by std::sort)
// --- Your code here
bool compare(const ObjMassPair& a, const ObjMassPair& b){
  return a.second < b.second;
}

std::ostream& operator<<(std::ostream& os, const ObjMassPair& obj) {
    os << obj.first << " " << std::defaultfloat <<  obj.second;
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<ObjMassPair>& objs) {
    for (const auto& obj : objs) {
        os << obj << "\n";  
    }
    return os;  
}
// ---
