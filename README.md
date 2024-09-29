
# Maze Solving with Stack and Queue Algorithms

## Overview

This project implements two algorithms to solve a maze using **stack** and **queue** data structures. These algorithms simulate depth-first search (DFS) and breadth-first search (BFS) respectively, allowing for exploration of different strategies to find a path through the maze. The project provides insight into how different data structures influence traversal patterns and efficiency in maze-solving tasks. Project for UCLA CS 32 class.

## Features

- **Stack-Based Maze Solver (DFS)**: Implements a depth-first search algorithm to explore the maze by continuously moving along a path until a dead end is encountered, at which point the algorithm backtracks to the last available choice.
  
- **Queue-Based Maze Solver (BFS)**: Implements a breadth-first search algorithm that explores all possible paths from a point incrementally, ensuring all nodes at a given level are explored before moving deeper into the maze.

- **Maze Input and Output**: The maze is represented as a grid where each cell can either be free or blocked. The algorithm reads in the maze configuration and outputs the solution path based on the chosen traversal strategy.

## Algorithmic Approach

### Stack-Based Approach (DFS)
- The stack-based algorithm simulates **depth-first search** by always exploring a single path as far as possible before backtracking to the last unvisited branching point.
- **Backtracking**: When the algorithm encounters a dead end, it pops elements off the stack to backtrack to the last position where other paths were available.
- **Efficiency**: DFS can be more memory efficient for deeply nested paths, but it may miss shorter paths due to its depth-first nature.

### Queue-Based Approach (BFS)
- The queue-based algorithm simulates **breadth-first search**, exploring all adjacent cells at the current depth before moving to the next level.
- **Exploration**: BFS guarantees that the shortest path will be found (if one exists), as it explores all possible routes level by level.
- **Memory Use**: BFS may require more memory as it stores all the nodes at the current level, making it less memory efficient than DFS in certain scenarios.

### Comparison
- **DFS (Stack)**: Explores one path to its end, backtracks only when necessary, potentially missing shorter paths.
- **BFS (Queue)**: Explores all paths level by level, guaranteeing the shortest path but at the cost of higher memory usage.

## Example Output

### Stack (DFS)
The first twelve values popped off during DFS are:
```
34, 33, 35, 25, 15, 16, 17, 18, 28, 36, 44, 54
```

### Queue (BFS)
The first twelve values popped off during BFS are:
```
34, 44, 35, 33, 54, 36, 25, 64, 55, 15, 74, 56
```

## How the Algorithms Differ
- **DFS (Stack)**: Continuously explores one path until a dead end is reached, then backtracks to the last unvisited branching point.
- **BFS (Queue)**: Explores all branching points incrementally, ensuring all possible paths at the current depth are considered before moving deeper into the maze.

## Project Structure

- **eval.cpp**: Contains code for evaluating maze states, likely including path validation and checking if the maze has been solved.
- **mazestack.cpp**: Implements the stack-based depth-first search algorithm for solving the maze.
- **mazequeue.cpp**: Implements the queue-based breadth-first search algorithm for solving the maze.

## How to Build and Run

### Requirements
- **C++11** or later
- A compatible C++ compiler (e.g., `g++`)

### Build Instructions
1. Clone the repository and navigate to the project directory.

2. Compile the project:
   ```bash
   g++ -std=c++11 mazestack.cpp mazequeue.cpp eval.cpp -o maze_solver
   ```

3. Run the executable:
   ```bash
   ./maze_solver
   ```

4. Provide the maze input when prompted or through a file.

## Conclusion

This project demonstrates the impact of different traversal strategies in maze-solving problems using stack-based depth-first search (DFS) and queue-based breadth-first search (BFS). Each approach has its strengths and weaknesses, making it suitable for different types of problems.

