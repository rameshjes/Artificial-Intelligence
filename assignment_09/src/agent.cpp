/*
 * Daniel Vázquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 9
 *
 * agent.cpp
 * */
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <agent.hpp>
#include <stack>
#include <queue>



double total_time;
double total_path_cost;
//bool result = false;
vector<Location> result_cities;
int iterations;

Agent::Agent(vector<Location> scenario1, vector<Location> scenario2, vector<Location> scenario3, vector<Location> scenario4, vector<Location> scenario5):scenario1(scenario1),
		scenario2(scenario2),
		scenario3(scenario3),
		scenario4(scenario4),
		scenario5(scenario5)
{


}

Agent::~Agent()
{

}

void Agent::run()
{
	//unassigned_set = scenario1;
	//order_domain_values = scenario1;
	vector<Location> new_scenario;
	for(int values = 0;values<5;values++) {
		cout<<"##############  Scenario "<<values+1<<" ##########"<<endl<<endl;
		cout<<endl;
		if(values == 0) {
			new_scenario  = scenario1;
		}
		else if(values == 1) {
			new_scenario  = scenario2;
		}
		else if(values == 2) {
			new_scenario  = scenario3;
		}
		else if(values == 3) {
			new_scenario  = scenario4;
		}
		else if(values == 4) {
			new_scenario  = scenario5;
		}
		cout<<"***************** By Line number ******************"<<endl;
		for(int i=0;i<new_scenario.size();i++) {
			order_domain_values.push_back(new_scenario[i]);
			if(i==0) {
				assigned_set.push_back(make_pair(new_scenario[i],i));
			}
		}
		bool final_result_of_assignment = dbs_bactracking(order_domain_values);
		if(!final_result_of_assignment) {
			cout<<"Solution does not exist"<<endl;

		}
		else {
			for(int i=0;i<assigned_set.size();i++) {
				std::cout << "Location: " << assigned_set[i].second<<endl;

			}
			cout<<"Number of evaluations:"<<iterations<<endl;
			cout<<"Time to visit all cities :"<<get_total_path_cost(assigned_set)<<endl;
		}
		cout<<"***************** By Deadline ******************"<<endl;
		assigned_set.clear();
		assigned_set.push_back(make_pair(new_scenario[0],0));
		sort_by_deadlines();
		bool final_result_of_assignment2 = dbs_bactracking(order_domain_values);
		if(!final_result_of_assignment) {
			cout<<"Solution does not exist"<<endl;

		}
		else {
			for(int i=0;i<assigned_set.size();i++) {
				std::cout << "Location: " << assigned_set[i].second<<endl;

			}
			cout<<"Number of evaluations:"<<iterations<<endl;
			cout<<"Time to visit all cities :"<<get_total_path_cost(assigned_set)<<endl;
		}
		cout<<"***************** By Euclidean distance ******************"<<endl;
		assigned_set.clear();
		assigned_set.push_back(make_pair(new_scenario[0],0));
		sort_by_euclidean_distance();
		bool final_result_of_assignment3 = dbs_bactracking(order_domain_values);
		if(!final_result_of_assignment) {
			cout<<"Solution does not exist"<<endl;
			order_domain_values.clear();
			assigned_set.clear();
			euclidean_sort.clear();
		}
		else {
			for(int i=0;i<assigned_set.size();i++) {
				std::cout << "Location: " << assigned_set[i].second<<endl;

			}
			cout<<"Number of evaluations:"<<iterations<<endl;
			cout<<"Time to visit all cities :"<<get_total_path_cost(assigned_set)<<endl;
			order_domain_values.clear();
			assigned_set.clear();
			euclidean_sort.clear();
		}
		cout<<"########################################################################"<<endl<<endl;
	}

	//print_scenario(assigned_set);
	//get_unassigned_variable_set(scenario1,order_domain_values);
	// print_scenario(scenario1); //first element corresponds to the start position of the robot

	//TODO
}
double Agent::get_total_path_cost(vector<pair<Location,int>> assigned) {

	for(int i = 0; i<assigned.size()-1;i++) {
		total_path_cost += compute_time_to_travel(assigned[i].first,assigned[i+1].first);
	}
	return total_path_cost;
}
void Agent::print_scenario(vector<Location>& scenario) {

	std::vector<double> x, y;
	for (int i = 0; i < scenario.size(); i++) {
		std::cout << "Location: " << scenario[i].get_x() << "," << scenario[i].get_y() << " Deadline: " << scenario[i].get_deadline() << std::endl;
	}

}
bool Agent::is_consistent(Location currentCity,Location nextCity,double time_from_root_to_current){
	double time_to_visit_nextCity = compute_time_to_travel(currentCity,nextCity);

	if(time_to_visit_nextCity + time_from_root_to_current > nextCity.get_deadline()) {
		return false;
	}
	else {
		total_time = time_to_visit_nextCity;
		return true;
	}
}


double Agent::compute_time_to_travel(Location currentCity,Location nextCity) {
	double eucl_dist = sqrt(pow((currentCity.get_x() - nextCity.get_x()),2) + pow((currentCity.get_y() - nextCity.get_y()),2));
	return eucl_dist;
}

bool Agent::check_if_location_already_assigned(vector<Location> assigned,Location testCity) {
	for(int i=0;i<assigned.size();i++) {
		if(assigned[i].get_x() == testCity.get_x() and assigned[i].get_y() == testCity.get_y()) {
			return true;
		}
	}
	return false;
}
bool Agent::check_if_variable_already_assigned(int var) {
	bool already_assigned = false;
	for(int i=0;i<assigned_set.size();i++) {
		if(assigned_set[i].second==var) {
			already_assigned = true;
			break;
		}
	}
	return already_assigned;
}

void Agent::sort_by_deadlines() {

	bool swapp = true;
	while(swapp)
	{
		swapp = false;
		for (int i = 0; i < order_domain_values.size()-1; i++)
		{
			if (order_domain_values[i].get_deadline()>order_domain_values[i+1].get_deadline() )
			{
				Location temp = order_domain_values[i];
				order_domain_values[i] = order_domain_values[i+1];
				order_domain_values[i+1] = temp;
				swapp = true;
			}
		}
	}


}

void Agent::sort_by_euclidean_distance() {

	for(int i = 0;i<order_domain_values.size();i++) {

		euclidean_sort.push_back(make_pair(order_domain_values[i], compute_time_to_travel(order_domain_values[0],order_domain_values[i])));
	}

	bool eucl_swap = true;
	while(eucl_swap)
	{
		eucl_swap = false;
		for (int i = 0; i < euclidean_sort.size()-1; i++)
		{
			if (euclidean_sort[i].second>euclidean_sort[i+1].second )
			{

				pair<Location,double> temp = euclidean_sort[i];
				euclidean_sort[i] = euclidean_sort[i+1];
				euclidean_sort[i+1] = temp;
				eucl_swap = true;
			}
		}
	}
	order_domain_values.clear();
	for(int j = 0;j<euclidean_sort.size();j++) {
		order_domain_values.push_back(euclidean_sort[j].first);
	}

}
bool Agent::recursive_dbs(vector<Location> ordered_cities,int current_city_index, double time_from_parent_to_current) {

	bool result = false;
	bool assignment_is_consistent = false;

	//cout<<"assigned cities:"<<assigned_set.size()<<endl;

	if(assigned_set.size() == ordered_cities.size()) {
		return true;
	}
	for(int i = 1;i<ordered_cities.size();i++) {

		if(i!=current_city_index and !check_if_variable_already_assigned(i) ) {
			assignment_is_consistent = is_consistent(ordered_cities[current_city_index],ordered_cities[i],time_from_parent_to_current);
			if(assignment_is_consistent) {

				assigned_set.push_back(make_pair(ordered_cities[i],i));
				iterations++;
				//assigned_set.front().set_index(i);
				result = recursive_dbs(ordered_cities, i, time_from_parent_to_current + total_time);
				total_path_cost = time_from_parent_to_current + total_time;
				if(result) {
					return assignment_is_consistent;
				}
				else {
					assigned_set.erase(assigned_set.begin() + (assigned_set.size()-1));
				}
			}
		}

	}
	return result;
}

bool Agent::dbs_bactracking(vector<Location> scenario) {
	iterations = 0;
	total_time = 0;
	total_path_cost = 0;
	bool result_of_recursion = recursive_dbs(order_domain_values,0,0);
	return result_of_recursion;
}

