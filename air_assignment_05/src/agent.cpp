/*
 * Daniel Vazquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 5
 *
 * agent.cpp
 * */

#include "agent.hpp"

#include <iostream>
#include <string>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <stack>
#include <queue>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <sstream>
#define map_rows 25
#define map_cols 141

using namespace std;
pair<int, int> child1;
pair<int, int> child2;
pair<int,int> child3;
pair<int,int> child4;
bool result ;
bool cutoff =false;
bool failure = true;
int goal=1;

Agent::Agent(vector<vector<string> > selected_map, const pair<int, int> initial_pos, int number_of_goals):
																																								empty_map(selected_map),
																																								map(selected_map),
																																								initial_pos(initial_pos),
																																								number_of_goals(number_of_goals),
																																								max_number_of_stored_nodes(0),
																																								number_of_visited_nodes(0),
																																								total_of_stored_nodes(0),
																																								deepest_level(0)
{

	max_limit = map_rows * map_cols;
	print_map(empty_map);
}

Agent::~Agent()
{
}

void Agent::run()
{
	cout << "Running IDFS " << endl;
	cout << "Number of goals " << number_of_goals << endl;
	sleep(1);

	iterative_deepening_search();
}

void Agent::print_map(vector<vector<string> >& a_map)
{
	system("clear");

	int row = initial_pos.first;
	int col = initial_pos.second;


	for(int row = 0; row < map_rows; row++)
	{
		for(int col = 0; col < map_cols; col++)
		{
			cout << a_map[row][col];
		}
		cout << endl;
	}

	this_thread::sleep_for(chrono::milliseconds(20));
}


bool Agent::recursive_dls(pair<int, int> current_node, int goal, int limit, vector<pair<int, int> > current_path)
{
	//TODO

	//Notes:
	//Backtrack from here once you have found a goal.
	//If you have found a goal, do not forget to get a fresh copy of the map.
	//Stop searching if you have found a goal or reached the depth limit.
	//Only return true if a goal has been found.

	int row = current_node.first;
	int col = current_node.second;
	vector<vector<string> > freshmap = empty_map;
	ostringstream oss;
	oss << goal;
	string currentGoal = oss.str();
	if(freshmap[row][col] == currentGoal) {

		if(number_of_goals == goal) {
			backtrack_path(current_path);
			cout <<"Goal "<< goal<< " found "<< endl;
			deepest_level = limit;
			failure = false;
			return failure;
		}

		current_path = backtrack_path(current_path);

		cout <<"Goal "<< goal<< " found "<< endl;
		goal++;
		map = empty_map;
		sleep(1);
		recursive_dls(current_node, goal, limit-1, current_path);
	}
	else if (limit == 0) {
		if(number_of_goals != goal) {
			cout<<"Goal "<< goal<< " not found "<< endl;
			goal = goal+1;
			recursive_dls(current_node, goal, max_limit, current_path);
		}
		cutoff = true;
		return cutoff;
	}
	else {

		bool cutoff_occurred;
		cutoff_occurred = false;
		for(int action = 0;action<4;action++) {
			string character1 = map[current_node.first+1][current_node.second] ;
			string character2 = map[current_node.first-1][current_node.second] ;
			string character3 = map[current_node.first][current_node.second+1] ;
			string character4 = map[current_node.first][current_node.second-1] ;

			if(action == 0 and !(character1 == "=" || character1 == "|"||character1== "-") and (character1==" " ||character1==currentGoal)) {
				child1 = make_pair(current_node.first+1,current_node.second);
				current_path.push_back(child1);
				total_of_stored_nodes++;
				map[child1.first][child1.second] = "-";
				result = recursive_dls(child1, goal, limit-1, current_path);
				if(result == cutoff) {
					cutoff_occurred = true;
				}
				else if(result!=failure ) {
					return result;
				}
			}
			else if(action == 3 and !(character2 == "=" || character2 == "|"||character2 == "-") and (character2==" " ||character2==currentGoal)) {
				child2 = make_pair(current_node.first-1,current_node.second);
				current_path.push_back(child2);
				total_of_stored_nodes++;
				map[child2.first][child2.second] = "-";
				result = recursive_dls(child2, goal, limit-1, current_path);

				if(result == cutoff) {
					cutoff_occurred = true;
				}
				else if(result!=failure ) {
					return result;
				}
			}
			else if(action == 2 and !(character3 == "=" || character3 == "|"||character3 == "-") and (character3==" " ||character3==currentGoal)) {
				child3 = make_pair(current_node.first,current_node.second+1);
				current_path.push_back(child3);
				total_of_stored_nodes++;
				map[child3.first][child3.second] = "-";
				result = recursive_dls(child3, goal, limit-1, current_path);

				if(result == cutoff) {
					cutoff_occurred = true;
				}
				else if(result!=failure) {
					return result;
				}
			}
			else if(action == 1 and !(character4 == "=" || character4 == "|"||character4 == "-") and (character4==" " ||character4==currentGoal)) {
				child4 = make_pair(current_node.first,current_node.second-1);
				current_path.push_back(child4);
				total_of_stored_nodes++;
				map[child4.first][child4.second] = "-";
				result = recursive_dls(child4, goal, limit-1, current_path);

				if(result == cutoff) {
					cutoff_occurred = true;
				}
				else if(result!=failure) {
					return result;
				}
			}

		}
		if(cutoff_occurred)	{
			return cutoff;
		}
		else {
			return failure;
		}
	}

}
bool Agent::depth_limited_seach(int limit)
{
	vector<pair<int, int> >current_path;
	pair<int, int> current_node;
	if(limit > max_limit) {
		return false;
	}
	current_node = make_pair(initial_pos.first, initial_pos.second);
	current_path.push_back(current_node);
	return recursive_dls(current_node, goal, limit, current_path);
}
void Agent::iterative_deepening_search()
{

	depth_limited_seach(max_limit);
	if(failure == false || number_of_goals == goal) {
		print_final_results();
	}

}


void Agent::print_final_results()
{   
	cout << "Deepest level reached: " << deepest_level  << endl;
	cout << "Total of stored nodes: " << total_of_stored_nodes << endl;
	cout << "Total of visited nodes: " << number_of_visited_nodes << endl;

} 

vector<pair<int, int> > Agent::backtrack_path(vector<pair<int, int> > current_path)
{
	//use the original map to backtrace
	vector<vector<string> > local_map = empty_map;

	pair<int, int> current_data;
	//cout<<"inside backtrack";
	//TODO
	//Backtrace. Use the current path vector to set the path on the map.
	for (auto const& element:current_path) {

		current_data = element;
		current_path.pop_back();

		number_of_visited_nodes++;
		local_map[current_data.first][current_data.second] = ".";
	}
	print_map(local_map);
	return current_path;
}
