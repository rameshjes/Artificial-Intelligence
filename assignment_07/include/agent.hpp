/*
 * Daniel Vázquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 7
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
	vector<City> cities;

	vector<City> hillClimb(vector<City> cities);
	void random_restart_hill_climb();



public:
	Agent(vector<City> Cities);
	~Agent();
	void run();
	void print_cities(vector<City>&);
	void save_cities_image(vector<City>& cities, int file_counter);

	int find_city_index_in_list(vector<City> cities,pair<double , double>);
	double check_distance_between_cities(double lat_city_begin, double lon_city_begin, double lat_neigh_city, double lon_neigh_city);
	bool check_if_city_is_visited(double latitude,double longitude);
	double compute_total_travel_cost(vector<City> cities);

	multimap<pair<double,double>, double>  get_neighbouring_distances(pair<double,double> currentCity,vector<City>& cities);
	multimap<pair<double,double>, double>  neighbouring_cities_and_distances;


};

#endif // Agent_H_
