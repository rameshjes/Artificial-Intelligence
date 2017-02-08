/*
 * Daniel Vázquez
 * Aritificial Intelligence for Robotics
 * SS 2016
 * Assignment 8
 *
 * agent.hpp
 * */
#ifndef Agent_H_
#define Agent_H_

#include <vector>
#include <fstream>
#include <environment.hpp>

using namespace std;

class Agent {
    private:
        vector<City> cities;
        
        vector<City> simulated_annealing(vector<City> cities);
        
        

    public:
        Agent(vector<City> Cities);
        ~Agent();
        void run();
        void print_cities(vector<City>&);
        void save_cities_image(vector<City>& cities, int file_counter);
        double check_distance_between_cities(double lat_city_begin, double lon_city_begin, double lat_neigh_city, double lon_neigh_city);
        double compute_total_travel_cost(vector<City> cities);
        double acceptanceProbability(double energy, double newEnergy, double temperature);
        double getAlpha(int runtime);
        vector<City> getNeighbouringCity(vector<City> cities);


};

#endif // Agent_H_
