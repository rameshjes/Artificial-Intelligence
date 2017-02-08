/*
 * Daniel Vázquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 7
 *
 * agent.cpp
 * */
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <agent.hpp>
#include <environment.hpp>
#include <matplotlibcpp.h>
#include <string>
#include <vector>
#include <algorithm>
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0


double total_travel_cost = 0;
vector<City>  currentCityList;
pair<double,double>  presentCity;
pair<double,double>  neighbourCity;
pair<vector<City> , double > current;
pair<vector<City> , double > neighbour;
vector<City> visited_cities;
vector<City> final_cities;
double least_cost = 0 ;
Agent::Agent(vector<City> cities):cities(cities)
{

}

Agent::~Agent()
{

}

void Agent::run()
{

	random_restart_hill_climb();

}
// This function converts decimal degrees to radians
double deg2rad(double deg) {
	return (deg * pi / 180);
}


void Agent::print_cities(vector<City>& cities) {

	std::vector<double> x, y;
	for (int i = 0; i < cities.size(); i++) {
		x.push_back(cities[i].get_x());
		y.push_back(cities[i].get_y());
	}

	// Plot line from given x and y data.
	matplotlibcpp::plot(x, y);
	matplotlibcpp::show();
}

void Agent::save_cities_image(vector<City>& cities, int file_counter) {

	std::vector<double> x, y;
	for (int i = 0; i < cities.size(); i++) {
		x.push_back(cities[i].get_x());
		y.push_back(cities[i].get_y());
	}

	// Plot line from given x and y data.
	matplotlibcpp::plot(x, y);
	string file = "salesman_" + to_string(file_counter) + ".png";
	matplotlibcpp::save(file);
}
// Takes longitude and latitude of city and its neighbour and return distance between them.
double Agent::check_distance_between_cities(double lat_city_begin, double lon_city_begin, double lat_neigh_city, double lon_neigh_city) {
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = deg2rad(lat_city_begin);
	lon1r = deg2rad(lon_city_begin);
	lat2r = deg2rad(lat_neigh_city);
	lon2r = deg2rad(lon_neigh_city);

	double longitude = lon2r - lon1r;
	double latitude = lat2r - lat1r;
	double eucl_dist = sqrt(pow(longitude,2) + pow(latitude,2));
	//double a = pow(sin(longitude/2),2) + cos(lon1r)*cos(lon2r)*pow(sin(latitude/2),2);
	//double c = 2 * atan2(sqrt(a),sqrt(1-a));
	//double dist = earthRadiusKm * c;
	//return dist;
	return eucl_dist;

}

multimap<pair<double,double>, double> Agent::get_neighbouring_distances(pair<double,double> currentCity,vector<City>& cities){

	double distance = 0;
	pair<double,double> neighbouring_city_coord;
	neighbouring_cities_and_distances.clear();
	for (int i = 0; i < cities.size(); i++) {
		distance = check_distance_between_cities(currentCity.first,currentCity.second,cities[i].get_x(),cities[i].get_y());
		neighbouring_city_coord = make_pair(cities[i].get_x(), cities[i].get_y());
		neighbouring_cities_and_distances.insert(make_pair(neighbouring_city_coord, distance));
	}
	return neighbouring_cities_and_distances;
}
bool Agent:: check_if_city_is_visited(double latitude,double longitude) {

	for(std::vector<City>::size_type i = 0; i != visited_cities.size(); i++) {
		if(latitude == visited_cities[i].get_x() and longitude == visited_cities[i].get_y()) {
			return true;
		}
	}
	return false;
}
//computes total travel cost 
double  Agent:: compute_total_travel_cost(vector<City> cities) {
	double travel_cost = 0;
	for (int i = 0; i < cities.size()-1; i++) {
		travel_cost += check_distance_between_cities(cities[i].get_x(),cities[i].get_y(),cities[i+1].get_x(),cities[i+1].get_y());
	}
	return travel_cost;
}

int Agent:: find_city_index_in_list(vector<City> cities,pair<double , double> current_neighbour) {

	for (int i = 0; i < cities.size(); i++) {
		if(cities[i].get_x() == current_neighbour.first and cities[i].get_y() == current_neighbour.second) {
			return i;
		}
	}
	return 0;
}


vector<City> Agent::hillClimb(vector<City> cities) {
	total_travel_cost = compute_total_travel_cost(cities);
	current = make_pair(cities, total_travel_cost);
	multimap<pair<double,double>, double> city_distances;
	presentCity = make_pair(current.first[0].get_x(),current.first[0].get_y());

	for(int i = 0;i<current.first.size()-1;i++) {


		visited_cities.clear();

		city_distances = get_neighbouring_distances(presentCity,current.first);
		std::multimap<pair<double,double>, double>::iterator it=city_distances.begin();
		neighbourCity = it->first;
		int index = find_city_index_in_list(current.first,neighbourCity);
		visited_cities.push_back(current.first[index]);
		current.first[index] = current.first[i+1];
		current.first[i+1] = visited_cities.front();



		total_travel_cost = compute_total_travel_cost(current.first);
		neighbour = make_pair(current.first, total_travel_cost);
		presentCity =  make_pair(current.first[i].get_x(),current.first[i].get_y());

		if(neighbour.second < current.second) {
			current.second = neighbour.second;
			cout<<current.second<<endl;

		}
		else {
			for(int j=i+1;j<cities.size()-1;j++ ) {
				visited_cities.clear();

				visited_cities.push_back(current.first[i+1]);
				current.first[i+1] = current.first[j+1];
				current.first[j+1] = visited_cities.front();

				total_travel_cost = compute_total_travel_cost(current.first);
				if(total_travel_cost < neighbour.second) {
					current.second = total_travel_cost;
					cout<<current.second<<endl;
					break;
				}

			}

		}

	}

	return current.first;
}

void Agent::random_restart_hill_climb() {

	vector<City> returned_cities_from_hillclimb;
	least_cost = compute_total_travel_cost(cities);
	double min_travel_cost;
	for(int i = 0;i<5;i++) {
		std::srand ( unsigned (time(0) ) );
		random_shuffle(cities.begin(), cities.end());
		returned_cities_from_hillclimb = hillClimb(cities);
		if(least_cost > total_travel_cost) {
			least_cost = total_travel_cost;


			final_cities = returned_cities_from_hillclimb;
		}
		sleep(1);

	}

	cout<<"Minimum Travel cost:"<<least_cost<<endl;
	print_cities(final_cities);
	save_cities_image(final_cities, 1);
}
