#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
// --- Your code here


void calculate(std::vector<std::string>& tokens, std::ofstream& outfile){
  if (tokens.empty()) {
        outfile << "ERROR\n";
        return;
  }
  std::string op = tokens.back();
  if (op != "+" && op != "*" && op != "/") {
        outfile << "ERROR\n";
        return;
  }
  std::vector <double> numbers;

  for(int i=0; i<tokens.size()-1; i++){
    double num=std::stod(tokens[i]);
    numbers.push_back(num);
  }
  if (op == "+") {
        if (numbers.empty()) {
            outfile << "ERROR\n";
        } else {
            double sum = 0.0;
            for (double num : numbers) {
                sum += num;
            }
            outfile << sum << "\n";
        }
    } 
    else if (op == "*") {
        if (numbers.empty()) {
            outfile << "ERROR\n";
        } else {
            double product = 1.0;
            for (double num : numbers) {
                product *= num;
            }
            outfile << product << "\n";
        }
    } 
    else if (op == "/") {
        if (numbers.size() != 2) {
            outfile << "ERROR\n";
        } else {
            if (numbers[1] == 0.0) {
                outfile << "ERROR\n";
            } else {
                double quotient = numbers[0] / numbers[1];
                outfile << quotient << "\n";
            }
        }
    }
}


// ---
int main()
{
  std::ifstream infile("input.txt");
  std::ofstream outfile("output.txt");
  //Read in each line from the input file,
  //perform the specified operation on the numbers,
  //and write the results to the ouputfile.
  //Remember to check if the specified operation is possible!
  // --- Your code here
  while (infile.peek() != std::ifstream::traits_type::eof()) {
        std::string line;
        std::getline(infile, line);
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        
        while (std::getline(iss, token, ' ')) {
          if (!token.empty()) {  
            tokens.push_back(token);
          }
        }
        calculate(tokens, outfile);
  }
  // ---
  return 0;
}
