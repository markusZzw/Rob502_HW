#include <iostream>
#include <fstream>
// below are some includes that are hints for what could make things easier
#include <string>
#include <vector>
#include <algorithm>

void processLine(std::string& line, int lineNumber, int* counter) {
    // line is passed in by reference, so you can modify it directly
    // do not return anything from this function
    // --- Your code here
    std::string result;
    for(char n: line){
        switch(n){
            case 'e':
            result+='3';
            *counter+=3*lineNumber;
            break;

            case 'l':
            result+='1';
            *counter+=1*lineNumber;
            break;

            case 't':
            result+='7';
            *counter+=7*lineNumber;
            break;

            default:
            result+=n;
        }
    } 
    line=result;
}

int* createCounter() {
    // this is a contrived function to get you more familiar with heap allocation
    // if you return a pointer to a local variable (on the stack), that value will be invalid after the return
    // and accessing it will be unexpected behavior (probably a segfault)
    // remember to initialize it to 0
    // --- Your code here
    int * counter=new int(0);
    return counter;


    // ---
}

int main() {

    // you will need to read the API of std::ofstream and std::ifstream
    std::ifstream input{"input.txt"};
    std::vector<std::string> lines;
    std::string line;
    while(std::getline(input,line)){
        lines.push_back(line);
    }

    // create a reference to the pointed value
    // references can be used more conveniently than pointers
    // note that the processLine function takes counter as a pointer, so you have to address it with &
    // contrived example to get you more familiar with going between references and pointers
    // usually there will not be so many unnecessary conversions
    int& counter = *createCounter();

    // --- Your code here
    for(int i=0; i<lines.size(); i++){
        processLine(lines[i], i, &counter);
    }
    // ---

    // output
    // --- Your code here
    std::reverse(lines.begin(),lines.end());
    std::ofstream output("output.txt");
    for(const auto& line:lines){
        output<<line<<'\n';
    }
    output<< counter;

    // ---

    delete &counter;
}