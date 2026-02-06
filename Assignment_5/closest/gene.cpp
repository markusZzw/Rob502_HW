#include <bits/stdc++.h>
using namespace std;

struct Problem {
    array<double,5> requiredHours {10,25,15,5,20};  // How long a job takes
    array<double,4> costPerRobot {75,128,70,34};    // How much each robot cost per hour
    // Capability A[i][r]: contribution of robot r to task i per hour.
    array<array<double,4>,5> A {{
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1},
        {1,1,1,1}
    }};
    double penaltyPerHour = 200.0;  // Penalty for each unfinished job
};

struct Solution {
    array<double,4> x {0,0,0,0};
    double fitness = numeric_limits<double>::infinity();
};

Solution RandomSolution() {
    // Generate Random Solutions
    Solution S;
    for (double& v : S.x) {
        v = (rand()/(RAND_MAX + 1.0)) * 3.0; // in [0,3]
    }
    return S;
}

double ComputeFitness(const Problem& P, const array<double,4>& x) {
    double cost = 0.0;
    // Base total cost of all robot:
    for (int r=0; r<4; ++r) cost += P.costPerRobot[r] * x[r];

    array<double,5> fulfilled{}; // zeros
    // How much work has been done:
    for (int i=0; i<5; ++i)
        for (int r=0; r<4; ++r)
            fulfilled[i] += P.A[i][r] * x[r];

    // Penalize unfinished work
    double penalty = 0.0;
    for (int i=0; i<5; ++i) {
        double shortfall = max(0.0, P.requiredHours[i] - fulfilled[i]);
        penalty += shortfall * P.penaltyPerHour;
    }

    return cost + penalty;
}


Solution Crossover(const Solution& A, const Solution& B) {
    Solution C;
    C.x[0] = A.x[0];
    C.x[1] = A.x[1];

    C.x[2] = B.x[2];
    C.x[3] = B.x[3];

    return C;
}

void Mutate(Solution& S) {
    for (double& v : S.x) {
        double delta = (rand()/(RAND_MAX + 1.0)) * 0.2 - 0.1; // Randomly mutate each gene
        v = max(0.0, v + delta);                              // Make sure nothing is negative (- hour = nonsense)
    }
}


Solution GeneticAlgorithm(const Problem& P, int populationSize, int eliteCount, int iterations) {
    
    // Generate Random Solution & Compute Fitness:
    vector<Solution> current_generation(populationSize);

    for (auto& s : current_generation) {
        s = RandomSolution();
        s.fitness = ComputeFitness(P, s.x);
    }

    // Sort through the list of random solution & find best fits (elites):

    for (int t=0; t<iterations; ++t) {
        sort(current_generation.begin(), current_generation.end(), [](const Solution& a, const Solution& b){
            return a.fitness < b.fitness;
        });

        // Init a new vector to keep best solutions (so far)
        vector<Solution> new_generation;
        new_generation.reserve(populationSize);

        // keep n number of elites
        for (int i=0; i<eliteCount; ++i) new_generation.push_back(current_generation[i]);

        // fill the rest with children of elites
        while ((int)new_generation.size() < populationSize) {
            const Solution& A = current_generation[rand() % eliteCount];
            const Solution& B = current_generation[rand() % eliteCount];

            Solution C = Crossover(A, B);
            Mutate(C);
            
            C.fitness = ComputeFitness(P, C.x);
            
            new_generation.push_back(C);
        }

        // swap data from 'new_generation' to 'current_generation'
        current_generation.swap(new_generation);
    }

    // sort by fitness again & return best one
    sort(current_generation.begin(), current_generation.end(), [](const Solution& a, const Solution& b){
        return a.fitness < b.fitness;
    });

    return current_generation.front();
}

int main() {
    srand(0);
    Problem P;

    // quick checks that match the lab narrative structure
    array<double,4> zero{0,0,0,0};
    cout << "fitness(zero): " << ComputeFitness(P, zero) << "\n";
    array<double,4> test{2.0,2.0,2.5,2.0};
    cout << "fitness(test): " << ComputeFitness(P, test) << "\n";

    int populationSize = 1000, eliteCount = 10, iterations = 100;
    Solution best = GeneticAlgorithm(P, populationSize, eliteCount, iterations);

    cout << "Best fitness: " << best.fitness << "\n";
    cout << "x: ";
    for (double v : best.x) cout << v << " ";
    cout << "\n";
    return 0;
}