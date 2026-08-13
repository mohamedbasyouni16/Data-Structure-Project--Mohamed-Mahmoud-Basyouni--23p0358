// main.cpp
// Colored Water Sort Solver — entry point.
// Handles input parsing and output formatting only; all puzzle logic
// lives in State.h/.cpp and Solver.h/.cpp.

#include <iostream>
#include "State.h"
#include "Solver.h"

State readState(int n, int c) {
    State state(n, Tube(c, 0));
    for (int t = 0; t < n; ++t) {
        for (int i = 0; i < c; ++i) {
            std::cin >> state[t][i];
        }
    }
    return state;
}

void printState(const State& state) {
    for (size_t t = 0; t < state.size(); ++t) {
        std::cout << "Tube " << (t + 1) << ": [";
        for (size_t i = 0; i < state[t].size(); ++i) {
            std::cout << state[t][i];
            if (i + 1 < state[t].size()) std::cout << ",";
        }
        std::cout << "]\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, c;
    if (!(std::cin >> n)) return 0;
    std::cin >> c;
    State start = readState(n, c);

    SearchResult result = solve(start);

    if (!result.solved) {
        std::cout << "No solution exists.\n";
        return 0;
    }

    std::cout << "Solution found.\n";
    std::cout << "Minimum number of moves: " << result.moves.size() << "\n\n";

    State cur = start;
    for (size_t i = 0; i < result.moves.size(); ++i) {
        const Move& m = result.moves[i];
        std::cout << (i + 1) << ". Tube " << (m.src + 1) << " -> Tube " << (m.dst + 1) << "\n";
        cur = applyMove(cur, m.src, m.dst);
    }

    std::cout << "\nFinal state:\n";
    printState(cur);

    return 0;
}
