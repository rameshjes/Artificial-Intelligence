/*
 * Daniel Vázquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 8
 *
 * agent.cpp
 * */
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <agent.hpp>
#include <matplotlibcpp.h>
#include <math.h>
#include <random>
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

double total_travel_cost = 0;
pair<double,double>  presentCity;
pair<double,double>  neighbourCity;
vector<City> current;
vector<City> neighbour;
vector<City> visited_cities;
vector<City> best_tour;
vector<City> new_cities;
double least_cost = 0 ;
Agent::Agent(vector<City> cities):cities(cities)
{


}

Agent::~Agent()
{

}

void Agent::run()
{
	//example

	simulated_annealing(cities);

	//TODO
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
// This function converts decimal degrees to radians
double deg2rad(double deg) {
	return (deg * pi / 180);
}
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

double  Agent:: compute_total_travel_cost(vector<City> cities) {
	double travel_cost = 0;
	for (int i = 0; i < cities.size()-1; i++) {
		travel_cost += check_distance_between_cities(cities[i].get_x(),cities[i].get_y(),cities[i+1].get_x(),cities[i+1].get_y());
	}
	return travel_cost;
}

// Calculate the acceptance probability
double  Agent::acceptanceProbability(double energy, double newEnergy, double temperature) {
	// If the new solution is worse, calculate an acceptance probability
	return exp((energy - newEnergy) / temperature);
}

double Agent::getAlpha(int runtime) {

	switch(runtime) {
	case 1 : return 0.825404185268018;
			 break;
	case 3 : return 0.93804186639814;
	 	 	 break;
	case 5 : return 0.962350626398089;
 	 	 	 break;
	case 10: return 0.980994712726877;
 	 	 	 break;
	case 15: return 0.987289332240862;
	 	 	 break;
	case 30: return 0.9936243;
 	 	 	 break;

	}

}

vector<City> Agent::simulated_annealing(vector<City> cities) {
	// Set initial temp
	int ti = 0;
	double T ;
	int choice = 0;
	int runTime = 0;
	double alpha = 0;
	cout<<"Select runtime for simulated annealing:"<<endl;
	cout<<"1.)1 min 2.) 3 min 3.)5 min 4.)10 min 5.)15 min 6.)30 min"<<endl;
	cin>>choice;
	time_t seconds;
	switch(choice) {
		case 1 : runTime = 1;
				 seconds = 60;
				 break;
		case 2:	 runTime = 3;
				 seconds = 180;
		 	 	 break;
		case 3:	 runTime = 5;
				 seconds = 300;
		 	 	 break;
		case 4:	 runTime = 10;
		 	 	 seconds = 600;
	 	  	 	 break;
		case 5:	 runTime = 15;
				 seconds = 1200;
 	 	 	 	 break;
		case 6:	 runTime = 30;
				 seconds = 2400;
				 break;
	}
	alpha = getAlpha(runTime);


	total_travel_cost = compute_total_travel_cost(cities);
	current = cities;
	double probability = 0;
	best_tour = cities;
	cout<<"Initial solution distance : "<<compute_total_travel_cost(cities)<<endl;
	int iterations = 0;

	time_t endwait;
	time_t start = time(NULL);
	 // after 900s, end loop.

	endwait = start + seconds;

	while (true) {
		iterations++;
		time_t current_time = time(NULL);
		T = 1000*pow(alpha,current_time - start) - 0.01;
		//start = time(NULL);
		if(T<0.0001 or start >=endwait) {
			cout<<"Iterations :"<<iterations<<endl;
			print_cities(best_tour);
			save_cities_image(best_tour, 1);
			return best_tour;
		}
		neighbour.clear();
		neighbour = current;
		visited_cities.clear();
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0,1);
		int city1 = (int) rand() *cities.size()/RAND_MAX;
		int city2 = (int) rand()*cities.size()/RAND_MAX;
		//cout<<"Swapping city number "<<i<<" with city number "<<j<<endl;
		visited_cities.push_back(neighbour[city1]);
		neighbour[city1] = neighbour[city2];
		neighbour[city2] = visited_cities.front();


		// Get energy of solutions
		double currentEnergy = compute_total_travel_cost(current);
		double neighbourEnergy = compute_total_travel_cost(neighbour);
		//neighbour.second = neighbourEnergy;



		// Decide if we should accept the neighbour
		if(neighbourEnergy < currentEnergy) {
			//cout<<neighbourEnergy<<endl;
			current = neighbour;


		}

		else if (neighbourEnergy > currentEnergy) {
			probability = acceptanceProbability(currentEnergy, neighbourEnergy, T);
			double randome_number = dis(gen);
			if(probability > randome_number) {
				//cout<<"Probability :"<<probability<<" and random number :"<<randome_number<<endl;
				//cout<<neighbourEnergy<<endl;
				current = neighbour;
			}

		}
		else {
			continue;
			//ti++;
		}
		// Keep track of the best solution found
		if (compute_total_travel_cost(current) < compute_total_travel_cost(best_tour)) {
			best_tour = current;
			cout<<compute_total_travel_cost(best_tour)<<endl;
			T = 1000*pow(alpha,current_time - start) - 0.01;
			cout<<"Temperature :"<<T<<endl;
			if(T<0.0001 or start >=endwait) {
				cout<<" Iterations:"<<iterations<<endl;
				print_cities(best_tour);
				save_cities_image(best_tour, 1);
				return best_tour;
			}
		}

	}

}

