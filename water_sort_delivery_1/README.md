# Colored Water Sort Solver

C++ console program that solves the Colored Water Sort puzzle using BFS,
returning a minimum-move solution or reporting that none exists.

## Build

```
g++ -std=c++17 -O2 -o water_sort src/State.cpp src/Solver.cpp src/main.cpp
```

## Run

```
./water_sort < tests/test1_solvable_input.txt
```

or run it interactively and type the input by hand (see input format below).

## File structure

- `src/State.h` / `src/State.cpp` — puzzle state representation (tubes,
  colors), the pour rule (`isValidMove` / `applyMove`), and the goal test
  (`isGoal`). Kept separate from the search so the pour logic can be
  reasoned about and tested on its own.
- `src/Solver.h` / `src/Solver.cpp` — the BFS search itself: explores the
  state graph level by level (guaranteeing minimum moves, since every move
  costs 1) and reconstructs the winning move sequence via parent pointers.
- `src/main.cpp` — I/O only: reads the puzzle from stdin, calls the
  solver, and prints the result in the required format.

## Input format

```
<number of tubes N>
<tube capacity C>
<tube 1: bottom color ... top color>
...
<tube N: bottom color ... top color>
```

Positive integers are color codes (1 = red, 2 = blue, ...); `0` marks an
empty slot and must appear at the end (top) of a tube's line.

## Test cases (tests/)

| File | Description | Expected result |
|---|---|---|
| `test1_solvable_input.txt` | Spec's Example A: 4 tubes, capacity 2, 2 colors | Solved in 3 moves |
| `test2_no_solution_input.txt` | Spec's Example B: 2 tubes, capacity 2, both mixed | No solution exists |
| `test3_larger_input.txt` | 5 tubes, capacity 4, 3 colors, 2 empty tubes | Solved in 10 moves |
| `test4_already_solved_input.txt` | Already-solved puzzle (edge case) | Solved in 0 moves |

Each `*_input.txt` has a matching `*_output.txt` with the program's actual
output, for reference.
