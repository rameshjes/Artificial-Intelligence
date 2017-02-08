/*
 * Daniel Vázquez
 * Aritifiacial Intelligence for Robots
 * MAS SS 2016
 * Assignment 3
 *
 * agent.cpp
 * */

#include "agent.hpp"
#include <time.h>
#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
using namespace std;

int maxQueueSize = 1;
double elapsed_time;

Agent::Agent(vector<vector<string> > map, const pair<int, int> initial_pos,
		int number_of_goals, int search_option) :
																																								map(map), initial_pos(initial_pos), number_of_goals(number_of_goals), search_option(
																																										search_option), number_of_stored_nodes(0), number_of_visited_nodes(
																																												0) {

}

Agent::~Agent() {

}

void Agent::run() {

	if (search_option == 1) {
		cout << "Running BFS " << endl;
		cout << "Number of goals " << number_of_goals << endl;
		bfs();
	} else {
		cout << "Running DFS " << endl;
		cout << "Number of goals " << number_of_goals << endl;
		dfs();
	}

}

void Agent::print_map() {
	system("clear");

	for (int row = 0; row < map_rows; row++) {
		for (int col = 0; col < map_cols; col++) {
			cout << map[row][col];
		}
		cout << endl;
	}

	this_thread::sleep_for(chrono::milliseconds(10));

}

void Agent::bfs() {
	//queue stores a pair in the form (row, col)
	queue<pair<int, int> > nodes_queue;
	pair<int, int> current_node;

	//Note: Elements stored in a pair can be accessed by calling the .first and .second attributes. E.g:
	//int row = current_node.first
	//int col = current_node.second

	//Add the initial node to the queue
	//Note: To add a new pair to the queue you can use the std::make_pair method e.g:

	nodes_queue.push(make_pair(initial_pos.first, initial_pos.second));
	number_of_stored_nodes++;

	time_t start;
	time_t end;
	time(&start);
	while (nodes_queue.size() > 0) {

		current_node = nodes_queue.front();
		nodes_queue.pop();
		int row = current_node.first;
		int col = current_node.second;
		if(map[row][col] == "-" || map[row][col] == "|" || map[row][col] == "=" )
			continue;
		if(map[row][col] == "*" || map[row][col] == " "|| map[row][col] == "S"||map[row][col] == "s") {
			if(map[current_node.first][current_node.second] == "*" ){
				goal_positions.push_back(current_node);
			}
			map[current_node.first][current_node.second] = "-";
			number_of_visited_nodes +=1;
		}
		nodes_queue.push(make_pair(current_node.first,current_node.second+1));
		nodes_queue.push(make_pair(current_node.first,current_node.second-1));
		nodes_queue.push(make_pair(current_node.first+1,current_node.second));
		nodes_queue.push(make_pair(current_node.first-1,current_node.second));
		number_of_stored_nodes += 4;
		
		/*if(map[current_node.first][current_node.second] == "*") {
			goal_positions.push_back(current_node);

		} */
		if(maxQueueSize < nodes_queue.size()) {
			maxQueueSize = nodes_queue.size();
		}

		print_map();

	}
	time(&end);
	elapsed_time = difftime(end, start);
	print_evaluation_metrics("queue");
}

void Agent::dfs() {
	//the stack stores a pair in the form (row, col)
	stack<pair<int, int> > nodes_stack;
	pair<int, int> current_node;
	pair<int, int> up_node;
	pair<int, int> down_node;
	pair<int, int> left_node;
	pair<int, int> right_node;
	//Note: Elements stored in a pair can be accessed by calling the .first and .second attributes. E.g:
	//int row = current_node.first
	//int col = current_node.second

	//Add the initial node to the stack
	//Note: To add a new pair to the stack you can use the std::make_pair method e.g:
	nodes_stack.push(make_pair(initial_pos.first, initial_pos.second));
	number_of_stored_nodes++;
	int counter = 0;
	time_t start_dfs;
	time_t end_dfs;
	time(&start_dfs);
	while (nodes_stack.size() > 0) {

		current_node = nodes_stack.top();
		nodes_stack.pop();

		int row = current_node.first;
		int col = current_node.second;

		if(map[row][col] == "-" || map[row][col] == "|" || map[row][col] == "=" ) {

			continue;
		}
		if(map[current_node.first][current_node.second] == "*" || map[current_node.first][current_node.second] == " "|| map[row][col] == "S"|| map[row][col] == "s") {
			if(map[current_node.first][current_node.second] == "*" ){
				goal_positions.push_back(current_node);
				map[current_node.first][current_node.second] = "-";
				number_of_visited_nodes +=1;
				if(goal_positions.size() == number_of_goals) {
					break;
				}
				else {
					continue;
				}
			}
			else {
				map[current_node.first][current_node.second] = "-";
				number_of_visited_nodes +=1;
			}

		}

		nodes_stack.push(make_pair(current_node.first,current_node.second-1));
		nodes_stack.push(make_pair(current_node.first-1,current_node.second));
		nodes_stack.push(make_pair(current_node.first+1,current_node.second));
		nodes_stack.push(make_pair(current_node.first,current_node.second+1));

		number_of_stored_nodes += 4;

		if(maxQueueSize < nodes_stack.size()) {
			maxQueueSize = nodes_stack.size();
		}

		print_map();

	}
	time(&end_dfs);

	elapsed_time = difftime(end_dfs, start_dfs);
	print_evaluation_metrics("stack");

}

void Agent::print_evaluation_metrics(string data_structure_name) {
	print_map();
	cout << "All the possible nodes have been explored " << endl;
	cout << "Found " << goal_positions.size() << " of " << number_of_goals
			<< endl;
	cout << "Maximum size of the " << data_structure_name << " : "
			<< maxQueueSize << endl;
	cout << "Number of stored nodes: " << number_of_stored_nodes << endl;
	cout << "Total of visited nodes: " << number_of_visited_nodes << endl;
	cout << "Elapsed Time : " << elapsed_time << endl;
	print_goal_positions();
}

void Agent::print_goal_positions() {
	cout << "Goals: " << endl;
	for (int i = 0; i < goal_positions.size(); i++) {
		cout << i + 1 << ": (" << goal_positions[i].first << ", "
				<< goal_positions[i].second << ")" << endl;
	}
}

