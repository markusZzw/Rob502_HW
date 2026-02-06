#include <iostream>
#include <vector>

#define ERROR_MESSAGE std::invalid_argument("Error: vectors must be the same size")

// --- Your code here
template <typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& vec){
    os<<"[";
    for(int i=0; i<vec.size(); i++){
        os<<vec[i];
        if(i<vec.size()-1){
            os<<", ";
        }
    }
    os<<"]";
    return os;
}

template <typename T>
std::vector<double> to_double_vector(const std::vector<T>& vec) {
    std::vector<double> result;
    for (const auto& elem : vec) {
        result.push_back(static_cast<double>(elem));
    }
    return result;
}

template <typename T1, typename T2>
std::vector<double> operator+(const std::vector<T1>& vec1, const std::vector<T2>& vec2){
    if(vec1.size()!=vec2.size()){
        throw ERROR_MESSAGE;
    }
    std::vector<double> result;
    for(int i=0; i<vec1.size(); i++){
        result.push_back(vec1[i]+vec2[i]);
    }
    return result;
}

template <typename T1, typename T2>
std::vector<double> operator-(const std::vector<T1>& vec1, const std::vector<T2>& vec2){
    if(vec1.size()!=vec2.size()){
        throw ERROR_MESSAGE;
    }
    std::vector<double> result;
    for(int i=0; i<vec1.size(); i++){
        result.push_back(vec1[i]-vec2[i]);
    }
    return result;
}

template <typename T1, typename T2>
std::vector<double> operator*(const std::vector<T1>& vec1, const std::vector<T2>& vec2){
    if(vec1.size()!=vec2.size()){
        throw ERROR_MESSAGE;
    }
    std::vector<double> result;
    for(int i=0; i<vec1.size(); i++){
        result.push_back(vec1[i]*vec2[i]);
    }
    return result;
}

template <typename T>
std::vector<double> operator*(const std::vector<T>& vec, double scalar){
    std::vector<double> result;
    for(int i=0; i<vec.size(); i++){
        result.push_back(vec[i]*scalar);
    }
    return result;
}

template <typename T>
std::vector<double> operator*(double scalar, const std::vector <T>& vec){
    return vec*scalar;
}

template <typename T>
std::vector<double> operator/(const std::vector<T>& vec, double scalar){
    std::vector<double> result;
    for(int i=0; i<vec.size(); i++){
        result.push_back(vec[i]/scalar);
    }
    return result;
}

template <typename T1, typename T2>
std::vector<double> operator,(const std::vector<T1>& vec1, const std::vector<T2>& vec2) {
    std::vector<double> result = to_double_vector(vec1);
    std::vector<double> vec2_double = to_double_vector(vec2);
    result.insert(result.end(), vec2_double.begin(), vec2_double.end());
    return result;
}
// ---
