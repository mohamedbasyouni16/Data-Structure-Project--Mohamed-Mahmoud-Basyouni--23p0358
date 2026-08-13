// State.h
// Colored Water Sort Solver
//
// Everything related to representing a puzzle state and the rules for
// pouring between tubes lives here, separate from the search algorithm
// (Solver.h/.cpp) and I/O (main.cpp). Keeping this isolated makes the
// pour rules easy to unit-test on their own.

#pragma once

#include <vector>
#include <string>

using Tube = std::vector<int>;      // size C, index 0 = bottom, 0 = empty slot
using State = std::vector<Tube>;    // size N (number of tubes)

struct Move {
    int src;   // 0-based source tube index
    int dst;   // 0-based destination tube index
};

// Serializes a state into a compact string key, for use in hash-based
// visited sets / parent maps (see Solver.h).
std::string stateKey(const State& state);

// Index of the topmost filled slot in a tube, or -1 if the tube is empty.
int topIndex(const Tube& tube);

// Number of consecutive same-color slots at the top of the tube.
int topRunLength(const Tube& tube);

// Returns true if pouring from tube `src` into tube `dst` is a legal move:
// src must have liquid, dst must not be full, and dst's top color must
// either be empty or match src's top color.
bool isValidMove(const State& state, int src, int dst);

// Returns a new state with the maximal contiguous top-color run poured
// from src into dst (as much as fits). Assumes isValidMove(state, src, dst).
State applyMove(const State& state, int src, int dst);

// A tube is "solved" if it's empty, or completely full of a single color.
// The puzzle is solved when every tube is solved.
bool isGoal(const State& state);
