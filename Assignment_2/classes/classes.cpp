#include <iostream>
#include <initializer_list>
#include <vector>
// needed for setting printing precision
#include <iomanip>
#include <fstream>

using Coefficient = double;
class UnivariatePolynomial {
public:
    UnivariatePolynomial() = default;
    // constructor from an initializer list of coefficients
    UnivariatePolynomial(std::vector<Coefficient>);

    // the degree of the polynomial; for simplicity, we will let the degree of
    // the zero polynomial be -1
    int degree() const;
    
    // change the symbol for the polynomial such as 'y' or 'x'
    void setSymbol(char c);
    // get the symbol
    char symbol() const;

    // return the derivative of the polynomial
    UnivariatePolynomial derivative() const;

    // addition operation with another polynomial
    UnivariatePolynomial operator+(const UnivariatePolynomial&) const;

    // multiplication with a scalar
    UnivariatePolynomial operator*(Coefficient) const;


    // return its coefficients
    // note that we have both a const and non-const version
    // the const version is needed when the object is const
    // this is an example of method overloading
    const std::vector<Coefficient>& coeffcients() const;
    std::vector<Coefficient>& coeffcients();


private:
    std::vector<Coefficient> _coef;
    // default initialization via assignment
    char _symbol = 'x';
};

// overload the output operator
// note that the polynomial parameter is const, so we can only use const methods on it
std::ostream& operator<< (std::ostream& out, const UnivariatePolynomial& polynomial) {
    // --- Your code here
    std::vector <Coefficient> Now= polynomial.coeffcients();
    if(Now[0]==0 && Now.size()==1){
        out<<'0';
        return out;
    }
    bool first_term=true;
    char symbol= polynomial.symbol();
    for(int i=0; i<Now.size(); i++){
        if(Now[i]==0){
            continue;
        }
        if(!first_term){
            out<<" + ";
        }
        if(Now[i]<0){
            out << '-';
        }else if(!first_term){}
        

        first_term=false;
        double abs_coef= std::abs(Now[i]);
        out << std::setprecision(1) << std::fixed << abs_coef;  
        
        if (i >= 1) {
            out << symbol;          
            if (i > 1) {
                out << "^" << i;    
            }
        }
    }

    // --- 

    return out; // return std::ostream so we can chain calls to operator<<
}

// similarly for the input stream operator
// a bit tricky because we want to only read a single line for our coefficients
// the next line belongs to the next polynomial
std::istream& operator>> (std::istream& input, UnivariatePolynomial& polynomial) {
    // --- Your code here
    std::string line;
    if(std::getline(input, line)){
        std::istringstream iss(line);
        std::vector <Coefficient> Recent;
        double coef;
        while(iss >> coef){
            Recent.push_back(coef);
        }
        polynomial.coeffcients()=Recent;
    }
    // --- 
    return input;
}


// implementation of the constructor
UnivariatePolynomial::UnivariatePolynomial(std::vector<Coefficient> l) {
    // --- Your code here
    _coef=l;
    // ---
}

int UnivariatePolynomial::degree() const {
    // --- Your code here
    if (_coef.empty()) {
        return -1;
    }else{
        return _coef.size()-1;
    }
    // ---
}

void UnivariatePolynomial::setSymbol(char c) {
    _symbol = c;
}

char UnivariatePolynomial::symbol() const {
    return _symbol;
}

UnivariatePolynomial UnivariatePolynomial::derivative() const {
    // --- Your code here
    std::vector <Coefficient> deri_coef;
     if(_coef.empty()){
        return UnivariatePolynomial();
     }else{
        for(int i=1; i<_coef.size(); i++){
            deri_coef.push_back(i*_coef[i]);
        }
     }
     return UnivariatePolynomial(deri_coef);
    // ---
}

UnivariatePolynomial UnivariatePolynomial::operator+(const UnivariatePolynomial& p) const {
    // --- Your code here
    int max_size = std::max(_coef.size(), p._coef.size());
    std::vector <Coefficient> result_coef(max_size, 0.0);
    for(int i=0; i<max_size; i++){
        double c1 = (i<_coef.size())? _coef[i]:0;
        double c2 = (i<p._coef.size())? p._coef[i]:0;
        result_coef[i]=c1+c2;
    }
    return  UnivariatePolynomial(result_coef);
    // ---
}

// multiplication with a scalar
UnivariatePolynomial UnivariatePolynomial::operator*(Coefficient scalar) const {
    // --- Your code here
    if(_coef.empty()){
        return UnivariatePolynomial();
    }
    std::vector <Coefficient> result_coef;
    for(int i=0; i<_coef.size(); i++){
        result_coef.push_back(scalar*_coef[i]);
    }
    return UnivariatePolynomial(result_coef);
    // ---
}

const std::vector<Coefficient>& UnivariatePolynomial::coeffcients() const {
    return _coef;
}

std::vector<Coefficient>& UnivariatePolynomial::coeffcients() {
    return _coef;
}

int main() {
    // p(x) = 1.5 + 0.2x + 5.5x^3
    UnivariatePolynomial p1{std::vector<Coefficient>{1.5, 0.2, 0, 5.5}};
    // coefficients should be printed to 1 decimal place
    // do not print monomials with 0 coefficient
    // monomials with exponent above 1 should have ^exponent behind the symbol

    // make sure these prints to cout are commented out when submitting, or they will make your answer wrong
    // should print 1.5 + 0.2x + 5.5x^3
    //std::cout << p1 << std::endl;

    // create p2(x) = -0.1 + -1.4x^2
    // --- Your code here
    UnivariatePolynomial p2{std::vector<Coefficient>{-0.1, 0, -1.4}};
    // ---

    // should print -0.1 + -1.4x^2
    // std::cout << p2 << std::endl;

    // should print 0.2 + 16.5x^2
    // std::cout << p1.derivative() << std::endl;

    // should print 1.2 + 0.2x + -4.2x^2 + 5.5^3
    // std::cout << p1 + p2 * 3 << std::endl;

    std::ifstream input{"input.txt"};
    std::ofstream output{"output.txt"};

    output << p1 + p2 * 3 << std::endl;
    UnivariatePolynomial p_total;
    while (input.peek() != std::ifstream::traits_type::eof()) {
        UnivariatePolynomial p;
        input >> p;
        output << p << std::endl;
        output << p.derivative() << std::endl;
        p_total = p_total + p;
    }
    output << p_total << std::endl;
    output << p_total.derivative() << std::endl;
}