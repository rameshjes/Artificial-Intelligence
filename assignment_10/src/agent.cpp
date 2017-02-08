/*
 * Daniel Vázquez
 * AIR SS16
 * Assignment 11
 * agent.cpp
 * */
#include <agent.hpp>
#include <climits>
#include <cmath>
#include <utility> 
#include <iostream>
#include <cstdlib>


using namespace std;
vector<pair<int, int> > min_values_1;
vector<pair<int, int> > max_values_1;
int col = 0;
int v ;
/*
 * Max_symbol: The simbol used by the agent Max
 * Min_symbol: The simbos used be the agent Min
 * */
Agent::Agent(std::string max_symbol, std::string min_symbol):
												max_symbol(max_symbol),
												min_symbol(min_symbol),
												total_tiles(NUM_COLS * NUM_ROWS)
{

}

Agent::~Agent()
{

}

//minimax initial method, returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::minimax(Puzzle puzzle, int free_tiles,int depth,bool maximisingPlayer)
{
	int utility_value = 0,col = 0;
	bool checkWin = false;
	if(maximisingPlayer) {
		checkWin = checkWinCondition(puzzle, max_symbol);
	}
	else {
		checkWin = checkWinCondition(puzzle, min_symbol);
	}
	if(depth == 0 || checkWin) {
		utility_value = utility(puzzle, max_symbol);
		return std::make_pair<int, int>(col, utility_value);
	}
	else if(maximisingPlayer){
		utility_value  = -99999;
		vector<pair<Puzzle,int> > possible_moves;
		possible_moves = getAllPossibleMoves(puzzle, free_tiles, max_symbol);

		for(int i = 0; i<possible_moves.size();i++) {
			int temp = possible_moves[i].second;

			int v = minimax(possible_moves[i].first, free_tiles-1, depth-1, false).second;
			if(v > utility_value) {
				col = temp;
				utility_value = v;
			}
		}
		return std::make_pair<int, int>(col, utility_value);
	}
	else {
		utility_value = 99999;
		vector<pair<Puzzle,int> > possible_moves;
		possible_moves = getAllPossibleMoves(puzzle, free_tiles, min_symbol);
		for(int i = 0; i<possible_moves.size();i++) {
			//col = possible_moves[i].second;
			int temp = possible_moves[i].second;
			int v = minimax(possible_moves[i].first, free_tiles-1, depth-1, true).second;
			if(v < utility_value) {
				col = temp;
				utility_value = v;
			}
		}
		return std::make_pair<int, int>(col, utility_value);
	}

}


//max returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::max(Puzzle puzzle, int free_tiles, int depth)
{
	int col = 0, utility_value = 0;

	return std::make_pair<int, int>(col, v);
}

//min returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::min(Puzzle puzzle, int free_tiles, int depth)
{

	int col = 0, utility_value = 0;
	return std::make_pair<int, int>(col, v);

}

//alpha_beta returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::alpha_betha(Puzzle puzzle, int free_tiles, int alpha, int beta,int depth,bool maximisingPlayer)
{
	int col = 0, utility_value = 0;
	bool checkWin = false;
	vector<pair<Puzzle,int> > possible_moves;
	if(maximisingPlayer) {
		checkWin = checkWinCondition(puzzle, max_symbol);
	}
	else {
		checkWin = checkWinCondition(puzzle, min_symbol);
	}


	if(depth == 0 || checkWin) {
		utility_value = utility(puzzle, max_symbol);
		return std::make_pair<int, int>(col, utility_value);
	}
	else if(maximisingPlayer){
		utility_value = -99999;

		possible_moves = getAllPossibleMoves(puzzle, free_tiles, max_symbol);
		for(int i = 0; i<possible_moves.size();i++) {
			int temp = alpha_betha(possible_moves[i].first, free_tiles, alpha, beta, depth-1, false).second;
			if(temp > utility_value) {
				utility_value = temp;
				col = possible_moves[i].second;

			}
			if (utility_value >= beta ){
				return std::make_pair<int, int>(col, utility_value);

			}
			if (alpha < utility_value){
				alpha = utility_value;
			}
		}

		return std::make_pair<int, int>(col, utility_value);
	}
	//Minimum
	else {
		utility_value = 99999;
		vector<pair<Puzzle,int> > possible_moves;
		possible_moves = getAllPossibleMoves(puzzle, free_tiles, min_symbol);
		for(int i = 0; i<possible_moves.size();i++) {
			int temp = alpha_betha(possible_moves[i].first, free_tiles, alpha, beta, depth-1, true).second;
			if(temp < utility_value) {
				utility_value = temp;
				col = possible_moves[i].second;
			}
			if ( utility_value <= alpha){
				return std::make_pair<int, int>(col, utility_value);

			}
			if(beta > utility_value){
				beta = utility_value;
			}
		}
		return std::make_pair<int, int>(col, utility_value);
	}

}

//max_value returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::max_alpha_betha(Puzzle puzzle, int free_tiles, int depth, int alpha, int beta)
{
	int col = 0, utility_value = 0;
	return std::make_pair<int, int>(col, utility_value);
}


//max_value returns the pair that holds the <col, utility_value> of the selected move
std::pair<int, int> Agent::min_alpha_betha(Puzzle puzzle, int free_tiles, int depth, int alpha, int beta)
{
	int col = 0, utility_value = 0;
	return std::make_pair<int, int>(col, utility_value);
}

vector<pair<Puzzle,int> > Agent::getAllPossibleMoves(Puzzle puzzle,int free_tiles,std::string player_symbol) {
	vector<pair<Puzzle,int> > puzzle_col_pairs ;

	for(int i = 0;i<NUM_COLS;i++) {
		/* compute first empty square in column i */
		Puzzle newPuzzle = puzzle;
		int row = find_row(puzzle,i);
		if(row<NUM_ROWS && row != -1) {
			newPuzzle[row][i] = player_symbol;
			puzzle_col_pairs.push_back(make_pair(newPuzzle, i));
		}
	}
	return puzzle_col_pairs;
}
int Agent ::find_row(Puzzle puzzle,int col) {
	/* computes the row on which token ends when dropped in column col
	 */
	int row=NUM_ROWS - 1;
	while((row>-1) && puzzle[row][col]!=".") {
		row--;
	}
	return row;
}

bool Agent::checkWinCondition(Puzzle puzzle, std::string player_symbol) {

	bool win = false;
	/*Check win condition in columns*/
	for (int j=0;j<NUM_COLS;j++) {
		for(int i=0;i<NUM_ROWS-3;i++) /* check for group of four vertical tokens */
		{
			int count=0;  /* counts number of consecutive tokens */
			while((count < 4) && (puzzle[i+count][j]==player_symbol))  {
				/* check if token is owned by player and not 4 tokens yet */
				count++;
			}
			if (count==4) {/* four tokens in column */
				win = true;   /* win for player*/
				return win;
			}

		}
	}

	/*Check win condition in rows*/
	for (int j=0;j<NUM_COLS-3;j++) {
		for(int i=0;i<NUM_ROWS;i++) /* check for group of four vertical tokens */
		{
			int count=0;  /* counts number of consecutive tokens */
			while((count < 4) && (puzzle[i][j+count]==player_symbol))  {
				/* check if token is owned by player and not 4 tokens yet */
				count++;
			}
			if (count==4) { /* four tokens in column */
				win = true;   /* win for player*/
				return win;
			}

		}
	}
	/*Check win condition in upward diagonals*/
	for (int j=0;j<NUM_COLS-3;j++) {
		for(int i=0;i<NUM_ROWS-3;i++) /* check for group of four vertical tokens */
		{
			int count=0;  /* counts number of consecutive tokens */
			while((count < 4) && (puzzle[i+count][j+count]==player_symbol))  {
				/* check if token is owned by player and not 4 tokens yet */
				count++;
			}
			if (count==4) { /* four tokens in column */
				win = true;   /* win for player*/
				return win;
			}

		}
	}

	/*Check win condition in lower diagonals*/
	for (int j=0;j<NUM_COLS-3;j++) {
		for(int i=3;i<NUM_ROWS;i++) /* check for group of four vertical tokens */
		{
			int count=0;  /* counts number of consecutive tokens */
			while((count < 4) && (puzzle[i-count][j+count]==player_symbol))  {
				/* check if token is owned by player and not 4 tokens yet */
				count++;
			}
			if (count==4) { /* four tokens in column */
				win = true;   /* win for player*/
				return win;
			}

		}
	}
	return win;

}
/*
 * Utility method: Computes the numerical value of the give puzzle
 */
double Agent::utility(Puzzle puzzle, std::string player_symbol)
{
	int utilityValue = 0;

	if(checkWinCondition(puzzle, player_symbol)) {
		if(player_symbol==max_symbol) {
			return 99999;
		}
		if(player_symbol==min_symbol) {
			return -99999;
		}
	}
	/*Get the utility value in columns  as the sum of
	 * max number of consecutive tokens in each of the column */
	for (int j=0;j<NUM_COLS;j++) {
		int max = 0;
		for(int i=0;i<NUM_ROWS-3;i++)
		{
			int count=0;  /* counts number of consecutive tokens */
			while((puzzle[i+count][j]==player_symbol))  {

				count++;
			}
			/* get the max number of consecutive tokens in a column */
			if (count>max) {
				max = count;
			}
		}


		utilityValue +=max;
	}

	/*Get the utility value in rows  as the sum of
	 * max number of consecutive tokens in each of the rows */
	for (int j=0;j<NUM_COLS-3;j++) {
		int max = 0;
		for(int i=0;i<NUM_ROWS;i++)
		{
			int count=0;  /* counts number of consecutive tokens */
			while((puzzle[i][j+count]==player_symbol))  {

				count++;
			}
			/* get the max number of consecutive tokens in a row */
			if (count>max) {
				max = count;
			}
		}

		utilityValue +=max;
	}


	/*Check win condition in upward diagonals*/
	for (int j=0;j<NUM_COLS-3;j++) {
		int max = 0;
		for(int i=0;i<NUM_ROWS-3;i++)
		{
			int count=0;  /* counts number of consecutive tokens */
			while((puzzle[i+count][j+count]==player_symbol))  {

				count++;
			}
			/* get the max number of consecutive tokens in upward diagonal */
			if (count>max) {
				max = count;
			}
		}

		utilityValue +=max;
	}

	/*Get the utility value in lower diagonals  as the sum of
	 * max number of consecutive tokens in lower diagonals */
	for (int j=0;j<NUM_COLS-3;j++) {
		int max = 0;
		for(int i=3;i<NUM_ROWS;i++)
		{
			int count=0;  /* counts number of consecutive tokens */
			while((puzzle[i-count][j+count]==player_symbol))  {

				count++;
			}
			/* get the max number of consecutive tokens in lower diagonal */
			if (count>max) {
				max = count;
			}
		}

		utilityValue +=max;
	}

	return utilityValue;
}




