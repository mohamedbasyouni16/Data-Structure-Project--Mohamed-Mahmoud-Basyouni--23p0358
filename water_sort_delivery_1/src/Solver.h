// Solver.h
// Colored Water Sort Solver
//
// The search algorithm, isolated from state/pour rules (State.h/.cpp)
// and I/O (main.cpp).
//
// Approach: BFS over the puzzle's state graph. Every move costs 1, so the
// first time BFS reaches a goal state, the path taken to get there is
// guaranteed to be a minimum-move solution (unlike DFS, which finds *a*
// solution but not necessarily the shortest one).

#pragma once

#include <vector>
#include "State.h"

struct SearchResult {
    bool solved = false;
    std::vector<Move> moves;   // empty if !solved, or if already solved
};

// Runs BFS from `start` and returns the minimum-move solution, if one
// exists.
SearchResult solve(const State& start);
