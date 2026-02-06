#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;


using State = vector<int>; //this defines the type State to be a vector of ints
using Action = vector<int>; //this defines the type Action to be a vector of ints


//this function should print out a state to the given stream
//the ostream could be something like cout, or cerr
//or it could be a filestream
void printState(const State& state, ostream & stream){
    // --- Your code here
    for (int i = 0; i < state.size(); i++) {
      if (i > 0) stream << " "; 
      stream << state[i];
    }
    stream << endl; 
    // ---
}


State dynamics(const State& state, const Action& action)
{
    State next_state(state.size());
    for (int j = 0; j < state.size();j++)
    {
        next_state[j] = state[j] + action[j];
    }
    return next_state;
}

int main () {
    
    ifstream policyfile("policy.txt");
    ofstream outputfile("output.txt");

    const int StateSize = 2;
    const int ActionSize = 2;    

    State key(StateSize);
    Action value(ActionSize);
    map<State,Action> policy;

    //read the policy file information into std::pair objects,
    //insert each std::pair into the map
    // --- Your code here
    while (policyfile.peek() != std::ifstream::traits_type::eof()) {
      std::string line;
      std::getline(policyfile, line);
      std::istringstream iss(line);
      std::vector<std::string> tokens;
      std::string token;

      while (std::getline(iss, token, ' ')) {
          if (!token.empty()) {  
            tokens.push_back(token);
          }
        }
      key[0]=stoi(tokens[0]);
      key[1]=stoi(tokens[1]);
      value[0]=stoi(tokens[2]);
      value[1]=stoi(tokens[3]);
      policy.emplace(key,value);
    }
    // ---

    //optional (but recommended) print out the policy to cout
    //to make sure that it was read in correctly
    // --- Your code here
    // ---

    //read in rollout
    ifstream rolloutfile ("rollout.txt");
    State startState(StateSize); //this stores the start stae
    int numSteps; //this is the number of steps in the rollout
    rolloutfile>>startState[0];
    rolloutfile>>startState[1];
    rolloutfile>>numSteps;
    rolloutfile.close();
    //Now use the the policy map to do the rollout
    // --- Your code here
    State current = startState;
    for(int i=0; i<numSteps; i++){
      if (policy.find(current) == policy.end()) {
      cerr << "State " << current[0]<< " "<< current[1]<< " is not in policy, terminating." << endl;
      return 1;
      }
      Action ac = policy[current];
      printState(current,outputfile);
      State next = dynamics(current, ac);
      current = next;
      if(i==numSteps-1){
        printState(next,outputfile);
      }
    }
    // ---

    outputfile.close();
    return 0;
}
