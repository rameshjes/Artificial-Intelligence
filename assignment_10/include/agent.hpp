/*
 * Daniel Vázquez
 * AIR SS16
 * Assignment 11
 * agent.hpp
 * */

#ifndef AGENT_HPP
#define AGENT_HPP

#include <utility>
#include <string>
#include <iostream>
#include <vector>
#include "definitions.hpp"
#include <string>
#include <vector>
using namespace std;

class Agent
{
	
	
	
public:
	Agent(std::string max_symbol, std::string min_symbol);
	~Agent();
	
	std::pair<int, int> minimax(Puzzle puzzle, int free_tiles,int depth,bool maximisingPlayer);
	std::pair<int, int> alpha_betha(Puzzle puzzle, int free_tiles, int alpha, int beta,int depth,bool maximisingPlayer);

private:
	
	int total_tiles;
	std::string max_symbol;
	std::string min_symbol;
	
	//minimax methods
	std::pair<int, int> max(Puzzle puzzle, int free_tiles, int depth);
	std::pair<int, int> min(Puzzle puzzle, int free_tiles, int depth);
	
	//alpha betha methods
	std::pair<int, int> max_alpha_betha(Puzzle puzzle, int free_tiles, int depth, int alpha, int beta);
	std::pair<int, int> min_alpha_betha(Puzzle puzzle, int free_tiles, int depth, int alpha, int beta);
	
	vector<pair<Puzzle,int> > getAllPossibleMoves(Puzzle puzzle,int free_tiles,std::string player_symbol);
	int find_row(Puzzle puzzle,int col);
	bool checkWinCondition(Puzzle puzzle, std::string player_symbol);
	double utility(Puzzle puzzle, std::string player_symbol);
	
};



#endif
