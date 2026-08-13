// State.cpp
#include "State.h"
#include <algorithm>

std::string stateKey(const State& state) {
    std::string key;
    key.reserve(state.size() * (state.empty() ? 1 : state[0].size()) * 2);
    for (const Tube& tube : state) {
        for (int v : tube) {
            key += std::to_string(v);
            key += ',';
        }
        key += '|';
    }
    return key;
}

int topIndex(const Tube& tube) {
    for (int i = (int)tube.size() - 1; i >= 0; --i) {
        if (tube[i] != 0) return i;
    }
    return -1;
}

int topRunLength(const Tube& tube) {
    int top = topIndex(tube);
    if (top < 0) return 0;
    int color = tube[top];
    int count = 0;
    for (int i = top; i >= 0 && tube[i] == color; --i) count++;
    return count;
}

bool isValidMove(const State& state, int src, int dst) {
    if (src == dst) return false;
    const Tube& s = state[src];
    const Tube& d = state[dst];

    int srcTop = topIndex(s);
    if (srcTop < 0) return false;              // nothing to pour

    int dstTop = topIndex(d);
    int capacity = (int)d.size();
    if (dstTop == capacity - 1) return false;   // destination full

    // Destination must be empty, or its top color must match source's top color.
    if (dstTop >= 0 && d[dstTop] != s[srcTop]) return false;

    return true;
}

State applyMove(const State& state, int src, int dst) {
    State next = state;
    Tube& s = next[src];
    Tube& d = next[dst];

    int srcTop = topIndex(s);
    int color = s[srcTop];
    int runLen = topRunLength(s);

    int dstTop = topIndex(d);
    int freeSpace = (int)d.size() - (dstTop + 1);

    int amount = std::min(runLen, freeSpace);

    int sIdx = srcTop;
    int dIdx = dstTop + 1;
    for (int k = 0; k < amount; ++k) {
        d[dIdx++] = color;
        s[sIdx--] = 0;
    }
    return next;
}

// A tube is "solved" if it's empty, or completely full of a single color.
//
// Note: just checking "each nonempty tube holds one color" is NOT enough —
// that would accept a color split across two half-full tubes as "solved",
// which under-counts the true minimum moves. The standard water-sort win
// condition requires every unit of a given color to be consolidated into
// one full tube.
bool isGoal(const State& state) {
    for (const Tube& tube : state) {
        int top = topIndex(tube);
        if (top < 0) continue;                        // empty tube: fine
        if (top != (int)tube.size() - 1) return false; // not full: not solved
        int color = tube[0];
        for (int i = 0; i <= top; ++i) {
            if (tube[i] != color) return false;
        }
    }
    return true;
}
