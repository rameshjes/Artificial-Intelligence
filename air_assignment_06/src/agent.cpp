/*
 * Daniel Vazquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 6
 *
 * agent.cpp
 * */
#include "agent.hpp"
#include <iostream>
#include <queue>
#include <algorithm>
#include <math.h>
#include<map>


int goalArray[] = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };
bool alreadyPresent = false;
bool inClosed = false;
int iterations ;
int visited_states;

pair<int,int> position_of_zero;     //coordinates of 0

int h;
int g;
int f;
Agent::Agent(Puzzle puzzle, Solver solver, Heuristic heuristic) :puzzle(puzzle), solver(solver), heuristic(heuristic) {

}

Agent::~Agent() {

}

void Agent::run() {
	clock_t start, end;
	double msecs;
	start = clock();

	if (solver == Solver::GREEDY) {
		cout << "Solver: Greedy Search" << endl;
		if (heuristic == Heuristic::MISPLACED_TILES) {
			cout << "Heuristic: Misplaced tiles" << endl;
		}

		else {
			cout << "Heuristic: Manhattan distance" << endl;
		}
		greedy_search (heuristic);
	}
	if (solver == Solver::A_STAR) {
		cout << "Solver: A*" << endl;
		if (heuristic == Heuristic::MISPLACED_TILES) {
			cout << "Heuristic: Misplaced tiles" << endl;
		}

		else {
			cout << "Heuristic: Manhattan distance" << endl;
		}
		a_star(heuristic);
	}
	end = clock();
	msecs = ((double) (end - start)) * 1000 / CLOCKS_PER_SEC;
	cout <<"Execution time: "<<msecs<<"ms"<<endl;
}


bool Agent::goal_test(Puzzle puzzle) {
	bool goalTest = true;
	int index = 0;
	for (int rows = 0; rows < NUM_ROWS; rows++) {
		for (int cols = 0; cols < NUM_COLS; cols++) {
			if(puzzle[rows][cols] != goalArray[index++]){
				goalTest = false;
			}
		}
	}
	return goalTest;
}
void Agent::find_children(Puzzle puzzle,pair<int,int> position_of_zero,Heuristic heuristic) {

	vector<vector<int>> new_puzzle = puzzle;

	//left child
	if(position_of_zero.second > 0) {
		int temp = new_puzzle[position_of_zero.first][position_of_zero.second-1];
		new_puzzle[position_of_zero.first][position_of_zero.second-1] = 0;
		new_puzzle[position_of_zero.first][position_of_zero.second] = temp;

		if(heuristic == Heuristic::MISPLACED_TILES) {
			h = misplaced_tiles(new_puzzle);
		}
		else if(heuristic == Heuristic::MANHATTAN_DISTANCE) {
			h = manhattan_distance(new_puzzle);
		}

		multimap<Puzzle,int>::iterator it = open.begin();
		while(it !=  open.end()) {
			alreadyPresent = (it->first == new_puzzle);
			if(alreadyPresent) {
				break;
			}
			++it;
		}

		multimap<Puzzle,int>::iterator it1 = closed.begin();
		while(it1 !=  closed.end()) {
			inClosed = (it1->first == new_puzzle);
			if(inClosed) {
				break;
			}
			++it1;
		}
		if(!alreadyPresent and !(inClosed)) {
			open.insert(make_pair(new_puzzle, h));
			visited_states++;
		}

	}

	new_puzzle = puzzle;
	//right child
	if(position_of_zero.second < 2) {
		int temp = new_puzzle[position_of_zero.first][position_of_zero.second+1];
		new_puzzle[position_of_zero.first][position_of_zero.second+1] = 0;
		new_puzzle[position_of_zero.first][position_of_zero.second] = temp;

		if(heuristic == Heuristic::MISPLACED_TILES) {
			h = misplaced_tiles(new_puzzle);
		}
		else if(heuristic == Heuristic::MANHATTAN_DISTANCE) {
			h = manhattan_distance(new_puzzle);

		}

		multimap<Puzzle,int>::iterator it = open.begin();
		while(it !=  open.end()) {
			alreadyPresent = (it->first == new_puzzle);
			if(alreadyPresent) {
				break;
			}
			++it;
		}

		multimap<Puzzle,int>::iterator it1 = closed.begin();
		while(it1 !=  closed.end()) {
			inClosed = (it1->first == new_puzzle);
			if(inClosed) {
				break;
			}
			++it1;
		}
		if(!alreadyPresent and !(inClosed)) {
			open.insert(make_pair(new_puzzle, h));
			visited_states++;
		}

	}

	new_puzzle = puzzle;
	//up child

	if(position_of_zero.first > 0) {
		int temp = new_puzzle[position_of_zero.first-1][position_of_zero.second];
		new_puzzle[position_of_zero.first-1][position_of_zero.second] = 0;
		new_puzzle[position_of_zero.first][position_of_zero.second] = temp;

		if(heuristic == Heuristic::MISPLACED_TILES) {
			h = misplaced_tiles(new_puzzle);
		}
		else if(heuristic == Heuristic::MANHATTAN_DISTANCE) {
			h = manhattan_distance(new_puzzle);

		}

		multimap<Puzzle,int>::iterator it = open.begin();
		while(it !=  open.end()) {
			alreadyPresent = (it->first == new_puzzle);
			if(alreadyPresent) {
				break;
			}
			++it;
		}

		multimap<Puzzle,int>::iterator it1 = closed.begin();
		while(it1 !=  closed.end()) {
			inClosed = (it1->first == new_puzzle);
			if(inClosed) {
				break;
			}
			++it1;
		}
		if(!alreadyPresent and !(inClosed)) {
			open.insert(make_pair(new_puzzle, h));
			visited_states++;
		}

	}
	new_puzzle = puzzle;
	//down child
	if(position_of_zero.first <2) {

		int temp = new_puzzle[position_of_zero.first+1][position_of_zero.second];
		new_puzzle[position_of_zero.first+1][position_of_zero.second] = 0;
		new_puzzle[position_of_zero.first][position_of_zero.second] = temp;

		if(heuristic == Heuristic::MISPLACED_TILES) {
			h = misplaced_tiles(new_puzzle);
		}
		else if(heuristic == Heuristic::MANHATTAN_DISTANCE) {
			h = manhattan_distance(new_puzzle);

		}

		multimap<Puzzle,int>::iterator it = open.begin();
		while(it !=  open.end()) {
			alreadyPresent = (it->first == new_puzzle);
			if(alreadyPresent) {
				break;
			}
			++it;
		}

		multimap<Puzzle,int>::iterator it1 = closed.begin();
		while(it1 !=  closed.end()) {
			inClosed = (it1->first == new_puzzle);
			if(inClosed) {
				break;
			}
			++it1;
		}
		if(!alreadyPresent and !(inClosed)) {
			open.insert(make_pair(new_puzzle, h));
			visited_states++;
		}


	}

}

void Agent :: find_children_a_star(Puzzle puzzle,pair<int,int> position_of_zero,Heuristic heuristic) {
	vector<vector<int>> new_puzzle = puzzle;
	g += 1;
	//left child
	if(position_of_zero.second > 0) {

		int temp = new_puzzle[position_of_zero.first][position_of_zero.second-1];
		new_puzzle[position_of_zero.first][position_of_zero.second-1] = 0;
		new_puzzle[position_of_zero.first][position_of_zero.second] = temp;

		if(heuristic == Heuristic::MISPLACED_TILES) {
			h = misplaced_tiles(new_puzzle);
			f = g + h;
		}
		else {
			h = manhattan_distance(new_puzzle);
			f = g + h;
		}

		multimap<Puzzle,int>::iterator it = open.begin();
		while(it !=  open.end()) {
			alreadyPresent = (it->first == new_puzzle);
			if(alreadyPresent) {
				break;
			}
			++it;
		}

		multimap<Puzzle,int>::iterator it1 = closed.begin();
		while(it1 !=  closed.end()) {
			inClosed = (it1->first == new_puzzle);
			if(inClosed) {
				break;
			}
			++it1;
		}
		if(!alreadyPresent and !(inClosed)) {
			open.insert(make_pair(new_puzzle, f));
			visited_states++;
		}
		else if (alreadyPresent and !(inClosed)) {
			if(f < it->second) {
				it->second = f;
				visited_states++;
			}
		}
		else if(!alreadyPresent and inClosed) {
			if(f < it1->second) {
				open.insert(make_pair(new_puzzle, f));
				closed.erase(new_puzzle);
				visited_states++;
			}
		}

	}

	new_puzzle = puzzle;
	//right child
	if(position_of_zero.second < 2) {

		int temp = new_puzzle[position_of_zero.first][position_of_zero.second+1];
		new_puzzle[position_of_zero.first][position_of_zero.second+1] = 0;
		new_puzzle[position_of_zero.first][position_of_zero.second] = temp;

		if(heuristic == Heuristic::MISPLACED_TILES) {
			h = misplaced_tiles(new_puzzle);
			f = g + h;
		}
		else {
			h = manhattan_distance(new_puzzle);
			f = g + h;
		}

		multimap<Puzzle,int>::iterator it = open.begin();
		while(it !=  open.end()) {
			alreadyPresent = (it->first == new_puzzle);
			if(alreadyPresent) {
				break;
			}
			++it;
		}

		multimap<Puzzle,int>::iterator it1 = closed.begin();
		while(it1 !=  closed.end()) {
			inClosed = (it1->first == new_puzzle);
			if(inClosed) {
				break;
			}
			++it1;
		}
		if(!alreadyPresent and !(inClosed)) {
			open.insert(make_pair(new_puzzle, f));
			visited_states++;
		}
		else if (alreadyPresent and !(inClosed)) {
			if(f < it->second) {
				it->second = f;
				visited_states++;
			}
		}
		else if(!alreadyPresent and inClosed) {
			if(f < it1->second) {
				open.insert(make_pair(new_puzzle, f));
				closed.erase(new_puzzle);
				visited_states++;
			}
		}

	}

	new_puzzle = puzzle;
	//up child

	if(position_of_zero.first > 0) {
		int temp = new_puzzle[position_of_zero.first-1][position_of_zero.second];
		new_puzzle[position_of_zero.first-1][position_of_zero.second] = 0;
		new_puzzle[position_of_zero.first][position_of_zero.second] = temp;

		if(heuristic == Heuristic::MISPLACED_TILES) {
			h = misplaced_tiles(new_puzzle);
			f = g + h;
		}
		else {
			h = manhattan_distance(new_puzzle);
			f = g + h;
		}

		multimap<Puzzle,int>::iterator it = open.begin();
		while(it !=  open.end()) {
			alreadyPresent = (it->first == new_puzzle);
			if(alreadyPresent) {
				break;
			}
			++it;
		}

		multimap<Puzzle,int>::iterator it1 = closed.begin();
		while(it1 !=  closed.end()) {
			inClosed = (it1->first == new_puzzle);
			if(inClosed) {
				break;
			}
			++it1;
		}
		if(!alreadyPresent and !(inClosed)) {
			open.insert(make_pair(new_puzzle, f));
			visited_states++;
		}
		else if (alreadyPresent and !(inClosed)) {
			if(f < it->second) {
				it->second = f;
				visited_states++;
			}
		}
		else if(!alreadyPresent and inClosed) {
			if(f < it1->second) {
				open.insert(make_pair(new_puzzle, f));
				closed.erase(new_puzzle);
				visited_states++;
			}
		}
	}
	new_puzzle = puzzle;
	//down child
	if(position_of_zero.first <2) {

		int temp = new_puzzle[position_of_zero.first+1][position_of_zero.second];
		new_puzzle[position_of_zero.first+1][position_of_zero.second] = 0;
		new_puzzle[position_of_zero.first][position_of_zero.second] = temp;

		if(heuristic == Heuristic::MISPLACED_TILES) {
			h = misplaced_tiles(new_puzzle);
			f = g + h;
		}
		else {
			h = manhattan_distance(new_puzzle);
			f = g + h;
		}

		multimap<Puzzle,int>::iterator it = open.begin();
		while(it !=  open.end()) {
			alreadyPresent = (it->first == new_puzzle);
			if(alreadyPresent) {
				break;
			}
			++it;
		}

		multimap<Puzzle,int>::iterator it1 = closed.begin();
		while(it1 !=  closed.end()) {
			inClosed = (it1->first == new_puzzle);
			if(inClosed) {
				break;
			}
			++it1;
		}
		if(!alreadyPresent and !(inClosed)) {
			open.insert(make_pair(new_puzzle, f));
			visited_states++;
		}
		else if (alreadyPresent and !(inClosed)) {
			if(f < it->second) {
				it->second = f;
				visited_states++;
			}
		}
		else if(!alreadyPresent and inClosed) {
			if(f < it1->second) {
				open.insert(make_pair(new_puzzle, f));
				closed.erase(new_puzzle);
				visited_states++;
			}
		}
	}
}

pair<int,int> Agent :: find_position_of_zero(Puzzle puzzle) {

	for (int rows = 0; rows < NUM_ROWS; rows++) {
		for (int cols = 0; cols < NUM_COLS; cols++) {
			if(puzzle[rows][cols] == 0){
				return make_pair(rows, cols);
			}
		}
	}

}

int Agent::misplaced_tiles(Puzzle puzzle) {
	//TODO
	int index = 0;
	int moves = 0;
	for (int rows = 0; rows < NUM_ROWS; rows++) {
		for (int cols = 0; cols < NUM_COLS; cols++) {
			if(puzzle[rows][cols] != goalArray[index++]){
				moves++;
			}
		}
	}
	return moves;
}

int Agent::manhattan_distance(Puzzle puzzle) {
	//TODO
	int value=0;
	int manhattanDistance = 0;
	int index = 0;
	for(int row = 0; row < NUM_ROWS; row++){
		for(int col = 0; col < NUM_COLS; col++){
			value = puzzle[row][col];
			if (value != 0){
				int targetX = (value - 1) / NUM_ROWS; // expected x-coordinate (row)
				int targetY = (value - 1) % NUM_COLS; // expected y-coordinate (col)
				int dx = row - targetX; // x-distance to expected coordinate
				int dy = col - targetY; // y-distance to expected coordinate
				manhattanDistance += abs(dx) + abs(dy);
			}

		}
	}

	return manhattanDistance;
}

void Agent::greedy_search(Heuristic heuristic) {
	//TODO
	//Note: In this assignment you must find the proper way to
	//keep track of repeated states.

	current_puzzle = puzzle;
	if(heuristic == Heuristic::MISPLACED_TILES) {
		h = misplaced_tiles(current_puzzle);
	}
	else {
		h = manhattan_distance(current_puzzle);
	}

	open.insert(make_pair(puzzle, h));
	iterations = 0;
	visited_states = 0;

	while(open.size() > 0) {
		iterations++;
		if(goal_test(current_puzzle)) {
			print_puzzle(current_puzzle);
			cout<<"Iterations : "<<iterations<<"  Visited states: "<<visited_states<<endl;
			return;
		}
		else {

			closed.insert(make_pair(current_puzzle, h));
			find_children(current_puzzle, find_position_of_zero(current_puzzle),heuristic);
			multimap<Puzzle,int>::iterator it = open.begin();
			current_puzzle = it->first;
			h = it->second;
			open.erase(it);
			visited_states--;
		}
	}


}

void Agent::a_star(Heuristic heuristic) {
	//TODO
	//Note: In this assignment you must find the proper way to
	//keep track of repeated states.
	g = 0;
	current_puzzle = puzzle;
	if(heuristic == Heuristic::MISPLACED_TILES) {
		h = misplaced_tiles(current_puzzle);
		f = g + h;
	}
	else {
		h = manhattan_distance(current_puzzle);
		f = g + h;
	}

	open.insert(make_pair(current_puzzle, f));
	iterations = 0;
	visited_states = 0;

	while(open.size() > 0) {

		iterations++;

		if(goal_test(current_puzzle)) {

			print_puzzle(current_puzzle);
			cout<<"Iterations : "<<iterations<<"  Visited states: "<<visited_states<<endl;

			return;
		}
		else {
			closed.insert(make_pair(current_puzzle, h));
			find_children_a_star(current_puzzle, find_position_of_zero(current_puzzle),heuristic);
			multimap<Puzzle,int>::iterator it = open.begin();
			current_puzzle = it->first;
			f = it->second;
			open.erase(it);
			visited_states--;
		}
	}


}

void Agent::print_puzzle(Puzzle& puzzle) {
	for (int rows = 0; rows < NUM_ROWS; rows++) {
		for (int cols = 0; cols < NUM_COLS; cols++) {
			std::cout << "|" << puzzle[rows][cols];
		}
		std::cout << "|" << std::endl;
	}
}

