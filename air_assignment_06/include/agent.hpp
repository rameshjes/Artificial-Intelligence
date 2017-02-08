/*
 * Daniel Vazquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 6
 *
 * agent.hpp
 * */

#ifndef AGENT_HPP
#define AGENT_HPP

#include <vector>
#include <string>
#include <utility> 
#include<map>

#define NUM_COLS 3
#define NUM_ROWS 3

using namespace std;

typedef vector<vector<int> > Puzzle;

enum Heuristic{
MISPLACED_TILES,
MANHATTAN_DISTANCE
};

enum Solver{
GREEDY,
A_STAR
};

class Agent {
public:
	Agent(Puzzle puzzle, Solver solver, Heuristic heuristic);
	~Agent();

	void run();

private:

	vector<vector<int> > puzzle;

	Solver solver;
	Heuristic heuristic;
	multimap<Puzzle ,int > open; // pair of the current puzzles and their heuristics
	multimap<Puzzle ,int > closed; // pair of the visited puzzle and their heuristic

	vector<vector<int> > current_puzzle;


	void greedy_search(Heuristic heuristic);
	void a_star(Heuristic heuristic);
	int misplaced_tiles(Puzzle puzzle);
	int manhattan_distance(Puzzle puzzle);

	void find_children(Puzzle puzzle,pair<int,int> position_of_zero,Heuristic heuristic);  //Given current puzzle, generate the children
	void find_children_a_star(Puzzle puzzle,pair<int,int> position_of_zero,Heuristic heuristic);  //Given current puzzle, generate the children
	pair<int,int> find_position_of_zero(Puzzle puzzle);  // Find where the zero position is in the puzzle
	bool goal_test(Puzzle puzzle);						//Check if the puzzle has all tiles in goal position
	void print_puzzle(Puzzle& puzzle);

};

#endif
