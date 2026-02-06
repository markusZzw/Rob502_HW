#include "maze.h"
#include "bfs.h"
#include "dfs.h"
#include <algorithm>


/** \brief Return the valid next states from a given state */
std::vector<State> ProblemDefinition::validStates(const State &state) const
{
    // HINT: use isStateValid()
    // --- Your code here
    std::vector<State> success;
    std::vector<std::pair<int, int>> moves = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
    if(allow_diagonal_){
        moves.push_back({1,1});
        moves.push_back({1,-1});
        moves.push_back({-1,1});
        moves.push_back({-1,-1});
    }
    for(const auto& move: moves){
        int next_x= state.x+move.first;
        int next_y= state.y+move.second;
        State next_state(next_x, next_y);
        if (isStateValid(next_state)) {
            success.push_back(next_state);
        }
    }
    return success;
    // ---
}

/** \brief Given a node, extract the path from it to the root */
void TreeSearch::extractPath(NodePtr node){
    // --- Your code here
    path_.clear();
    NodePtr current = node;
    while (current != nullptr){
        path_.push_back((*current).state);
        current = (*current).parent;
    }
    std::reverse(path_.begin(), path_.end());
    // ---
}

/** \brief Solve the planning problem. Override TreeSearch::solve() */
bool BFS::solve()
{
    // check start and goal are valid
    if (!pdef_.isStateValid(pdef_.startState()) ||
        !pdef_.isStateValid(pdef_.goalState()))
    {

        return false;
    }

    // if start and goal coincide, terminate
    auto start = pdef_.startState();
    if (pdef_.isGoal(start))
    {
        // std::cout << "Start and goal are equal\n";
        return true;
    }

    NodePtr solution;
    // --- Your code here
    NodePtr start_node = std::make_shared<Node>();
    (*start_node).state = pdef_.startState();
    (*start_node).cost_to_come = 0.0;
    addNode(start_node);
    visited_.push_back((*start_node).state);

    while(!_queue_.empty()){
        NodePtr current = _queue_.front();
        _queue_.pop();
        std::vector<State> next_states = pdef_.validStates((*current).state);
        for(const auto& ns: next_states){
            bool already_visited = false;
            if(!visited_.empty()){
                if (std::find(visited_.cbegin(), visited_.cend(), ns)!= visited_.cend()) {
                    already_visited = true;
                }
            }

            if(!already_visited){
                NodePtr new_node = std::make_shared<Node>();
                (*new_node).state = ns;
                (*new_node).parent= current;
                double cost = 1.0;
                    if(pdef_.allow_diagonal_){
                        if(std::abs((*new_node).state.x - (*current).state.x)==1 && 
                           std::abs((*new_node).state.y - (*current).state.y) == 1){
                            cost=sqrt(2.0);
                           }
                    }
                    (*new_node).cost_to_come=(*current).cost_to_come +cost;

                    if(pdef_.isGoal((*new_node).state)){
                        solution=new_node;
                        goto solution_found;
                    }

                    addNode(new_node);
                    visited_.push_back((*new_node).state);
               }
        }
    }
    return false;

    // ---
    solution_found:
    // get the path from last node to root
    extractPath(solution);
    return true;
}

/** \brief add node to the tree */
bool BFS::addNode(const NodePtr &node){
    // --- Your code here
    _queue_.push(node);
    return true;
    // ---
}

/** \brief Solve the planning problem. Override TreeSearch::solve() */
bool DFS::solve()
{
    // check start and goal are valid
    if (!pdef_.isStateValid(pdef_.startState()) ||
        !pdef_.isStateValid(pdef_.goalState()))
    {
        return false;
    }

    // if start and goal coincide, terminate
    auto start = pdef_.startState();
    if (pdef_.isGoal(start))
    {
        std::cout << "Start and goal are equal\n";
        return true;
    }

    NodePtr solution;
    // --- Your code here
    NodePtr start_node = std::make_shared<Node>();
    (*start_node).state = pdef_.startState();
    (*start_node).cost_to_come = 0.0;
    addNode(start_node);
    visited_.push_back((*start_node).state);

    while(!_stack_.empty()){
        NodePtr current = _stack_.top();
        _stack_.pop();
        std::vector<State> next_states = pdef_.validStates((*current).state);
        for(const auto& ns: next_states){
            bool already_visited = false;
            if (std::find(visited_.cbegin(), visited_.cend(), ns) != visited_.cend()) {
                already_visited = true;
            }

            if(!already_visited){
                NodePtr new_node = std::make_shared<Node>();
                (*new_node).state = ns;
                (*new_node).parent = current;
                double cost = 1.0;
                if (pdef_.allow_diagonal_) {
                    if (std::abs((*new_node).state.x - (*current).state.x) == 1 && 
                        std::abs((*new_node).state.y - (*current).state.y) == 1) {
                        cost = std::sqrt(2.0); 
                    }
                }
                (*new_node).cost_to_come = (*current).cost_to_come + cost;

                if (pdef_.isGoal((*new_node).state)) {
                    solution = new_node;
                    goto solution_found; 
                }
                addNode(new_node);
                visited_.push_back((*new_node).state);
            }
        }
    }
    return false;
    solution_found:
    // ---

    // get the path from last node to root
    extractPath(solution);

    return true;
}

/** \brief add node to the tree */
bool DFS::addNode(const NodePtr &node)
{
    // --- Your code here
    _stack_.push(node);
    return true;
    // ---
}