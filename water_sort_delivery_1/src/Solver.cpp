// Solver.cpp
#include "Solver.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

SearchResult solve(const State& start) {
    SearchResult result;

    if (isGoal(start)) {
        result.solved = true;
        return result;
    }

    int n = (int)start.size();

    std::unordered_map<std::string, std::string> parentKey; // state key -> parent key
    std::unordered_map<std::string, Move> parentMove;       // state key -> move that produced it
    std::unordered_set<std::string> visited;

    std::queue<State> q;
    std::string startKey = stateKey(start);
    visited.insert(startKey);
    q.push(start);

    std::string goalKey;
    bool found = false;

    while (!q.empty() && !found) {
        State cur = q.front();
        q.pop();
        std::string curKey = stateKey(cur);

        for (int src = 0; src < n && !found; ++src) {
            for (int dst = 0; dst < n && !found; ++dst) {
                if (!isValidMove(cur, src, dst)) continue;

                State next = applyMove(cur, src, dst);
                std::string nextKey = stateKey(next);
                if (visited.count(nextKey)) continue;

                visited.insert(nextKey);
                parentKey[nextKey] = curKey;
                parentMove[nextKey] = Move{src, dst};

                if (isGoal(next)) {
                    found = true;
                    goalKey = nextKey;
                    break;
                }
                q.push(next);
            }
        }
    }

    if (!found) {
        result.solved = false;
        return result;
    }

    // Reconstruct path by walking parent pointers back to start.
    std::vector<Move> path;
    std::string cur = goalKey;
    while (cur != startKey) {
        path.push_back(parentMove[cur]);
        cur = parentKey[cur];
    }
    std::reverse(path.begin(), path.end());

    result.solved = true;
    result.moves = path;
    return result;
}
