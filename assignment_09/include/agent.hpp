/*
 * Daniel Vázquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 9
 *
 * agent.hpp
 * */
#ifndef Agent_H_
#define Agent_H_

#include <vector>
#include <fstream>
#include <environment.hpp>
#include <map>
using namespace std;

class Agent {
    private:
        vector<Location> scenario;
        vector<pair<Location,double>> euclidean_sort;
        vector<pair<Location,int>> assigned_set;
        vector<Location> order_domain_values;
        bool dbs_bactracking(vector<Location> scenario);
        vector<Location> scenario1, scenario2, scenario3, scenario4, scenario5; //first element corresponds to the start position of the robot
        
        

    public:

        Agent(vector<Location> scenario1, vector<Location> scenario2, vector<Location> scenario3, vector<Location> scenario4, vector<Location> scenario5 );
        ~Agent();
        void run();
        void run_for_each_scenario(vector<Location> scenario);
        void print_scenario(vector<Location>&);
        double get_total_path_cost(vector<pair<Location,int>> assigned);
        double compute_time_to_travel(Location currentCity,Location nextCity);
        bool is_consistent(Location currentCity,Location nextCity,double time_from_root_to_current);
        bool check_if_location_already_assigned(vector<Location> assigned,Location testCity);
        bool check_if_variable_already_assigned(int var);
        void sort_by_deadlines();
        void sort_by_euclidean_distance();
        bool recursive_dbs(vector<Location> scenario,int current_city_index, double time_from_parent_to_current);

};

#endif // Agent_H_
