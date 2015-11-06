// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <typeinfo>
#include <vector>
#include <math.h>

#include "Darwin.h"

using namespace std;

Species::Species () {
	name_ = "best";
	instruction_.first = "";
	instruction_.second = -1;
	line_ = 0;
}

Species::Species (string const name): name_(name) {
	instruction_.first = "";
	instruction_.second = -1;
	line_ = 0;
}

const void Species::addInstruction (string const action) {
	instruction_.first = action;
	instruction_.second = -1;
	program.push_back(instruction_);
}

const void Species::addInstruction (string const control, int const step) {
	instruction_.first = control;
	instruction_.second = step;
	program.push_back(instruction_);
}

void Species::incrementLine (int& line_) {
	if (line_ == int(program.size()) - 1) line_ = 0;
	else line_++;
}

int Species::execute (const bool wall, const bool empty, const bool enemy) {
	while (1) {
		int ret = 0;
		if (program[line_].first.compare("hop") == 0) {
			ret = 1;
		}
		if (program[line_].first.compare("left") == 0) {
			ret = 2;
		}
		if (program[line_].first.compare("right") == 0) { 
			ret = 3;
		}
		if (program[line_].first.compare("infect") == 0) { 
			ret = 4;
		}
		if (ret != 0) {
			incrementLine (line_);
			return ret;
		} 
		if (program[line_].first.compare("if_empty") == 0) {
			if (empty) line_ = program[line_].second;
			else incrementLine (line_);	
		}
		if (program[line_].first.compare("if_wall") == 0) {
			if (wall) line_ = program[line_].second;
			else incrementLine (line_);
		}
		if (program[line_].first.compare("if_random") == 0) {
			int r = rand();
			if (r % 2) line_ = program[line_].second;
			else incrementLine (line_);
		}
		if (program[line_].first.compare("if_enemy") == 0) {
			if (enemy) line_ = program[line_].second;
			else incrementLine (line_);
		}
		if (program[line_].first.compare("go") == 0) {
			line_ = program[line_].second;
		}
	}
	return 0;
}

// First Letter Character
template<typename Cl>
char Species::operator>> (Cl c) {
	return name_[0];
}

template<typename Cl>
int Species::operator> (Cl c) {
	return line_;
}

void Species::operator< (int x) {
	line_ = x;
}

Species::~Species(){

}

Creature::Creature () {
	program_counter = 0;
}

Creature::Creature (Species& specie, string const direction):
					direction_(direction) {
	specie_ = specie; 
	program_counter = 0;
}

Creature::Creature(Creature& fromCreature, string const direction, int const pc):
					direction_(direction) {
	specie_ = fromCreature.specie_;
	specie_ < pc;
	program_counter = pc;
}

int Creature::execute(const bool wall, const bool empty, const bool enemy) {
	int toDoHere = specie_.execute(wall, empty, enemy);
	program_counter = (specie_ > this);
	if (toDoHere == 2) {
		if (direction_.compare("north") == 0) direction_ = "west";

		if (direction_.compare("west") == 0) direction_ = "south";

	    if (direction_.compare("south") == 0) direction_ = "east";

	    if (direction_.compare("east") == 0) direction_ = "north";
	}
	if (toDoHere == 3) {
		if (direction_.compare("north") == 0) direction_ = "east";

		if (direction_.compare("west") == 0) direction_ = "north";

	    if (direction_.compare("south") == 0) direction_ = "west";

	    if (direction_.compare("east") == 0) direction_ = "south";
	}
	int toDoThere = toDoHere;
	return toDoThere;
}

// Direction
bool Creature::operator== (string direction) {
	return direction.compare(direction_) == 0;
}

// First Letter Character 
template<typename Cl>
auto Creature::operator>> (Cl c) -> decltype(specie_ >> this) { return specie_ >> this; }

Creature::~Creature(){

}


Darwin::Darwin (int height, int width):
				width_(width), height_(height) {
	grid.resize(height_, vector<char>(width_, '.'));
	creatures.resize(height_, vector<Creature*>(width_, NULL));
	wall_ = empty_ = enemy_ = false;
}

const void Darwin::addCreature (Creature& creature_, int const i, int const j) {
	decltype(creature_ >> this) letter_ = (creature_ >> this);
	grid[i][j] = char(letter_);
	creatures[i][j] = &creature_;
}

string Darwin::direction (Creature& c) {
	string direction_;
	if (c == string("north")) direction_ = "north";
	if (c == string("south")) direction_ = "south";
	if (c == string("west")) direction_ = "west";
	if (c == string("east")) direction_ = "east";
	return direction_;
}

template<typename T>
void Darwin::managerWallEmptyInfect (Creature& c, T letter_, int i, int j) {
	string direction_ = direction(c);
	index = -1;
	add = 0;
	if (direction_.compare("north") == 0) {
		if (i == 0) wall_ = true;
		else if (grid[i - 1][j] == '.') {
			empty_ = true;
			add = -1;
		} else {
			empty_ = false;
			if (grid[i - 1][j] != letter_) {
				enemy_ = true;
				add = -1;
			}
		}
		index = 1;
	}
	if (direction_.compare("south") == 0) {
		if (i == height_ - 1) wall_ = true;
		else if (grid[i + 1][j] == '.') {
			empty_ = true;
			add = 1;
		} else {
			empty_ = false;
			if (grid[i + 1][j] != letter_) {
				enemy_ = true;
				add = 1;
			}
		}
		index = 1;
	}
	if (direction_.compare("west") == 0) {
		if (j == 0) wall_ = true;
		else if (grid[i][j - 1] == '.') {
			empty_ = true;
			add = -1;
		} else {
			empty_ = false;
			if (grid[i][j - 1] != letter_) {
				enemy_ = true;
				add = -1;
			}
		}
		index = 0;
	}
	if (direction_.compare("east") == 0) {
		if (j == width_ - 1) wall_ = true;
		else if (grid[i][j + 1] == '.') {
			empty_ = true;
			add = 1;
		} else {
			empty_ = false;
			if (grid[i][j + 1] != letter_) {
				enemy_ = true;
				add = 1;
			}
		}
		index = 0;
	}
}
	
void Darwin::turn (int turn, bool display) {
	if (display) {
		cout << "Turn = " << turn << "." << "\n";
			if (turn == 0) {printGrid(); return;}
	}
	data_.resize(0);
	vector<bool> processed;
	processed.resize(height_ * width_, false);
	for (int i = 0; i < height_; i++) {
		for (int j = 0; j < width_; j++) {
			if (creatures[i][j] && !processed[j + width_ * i]) {
				wall_ = empty_ = enemy_ = false;
				int old_i = i;
				int old_j = j;
				decltype(*creatures[i][j] >> this) letter_ = char(*creatures[i][j] >> this);
				managerWallEmptyInfect((*creatures[i][j]), letter_, i, j);
				int toDoHere = (*creatures[i][j]).execute(wall_, empty_, enemy_);
				if ((toDoHere == 1) && (empty_)) {
					if (index == 0) j = j + add;
					else if (index == 1) i = i + add;
						else throw invalid_argument("Invalid Direction");
					grid[i][j] = letter_;
					grid[old_i][old_j] = '.';
					creatures[i][j] = &(*creatures[old_i][old_j]);
					creatures[old_i][old_j] = NULL;
					processed[j + width_ * i] = true;
				}

				int ii = i;
				int jj = j;
				if ((toDoHere == 4) && (enemy_)) {
					if (index == 0) jj = jj + add;
					else if (index == 1) ii = ii + add;
						else throw invalid_argument("Invalid Direction");
					Creature n((*creatures[i][j]), direction(*creatures[ii][jj]), 0);
					decltype(n >> this) let_ = (n >> this);
					grid[ii][jj] = char(let_);
					*creatures[ii][jj] = n;
					processed[jj + width_ * ii] = true;
				}
				data_.push_back(*creatures[i][j]);
			}
		}
	}
	if (display) printGrid();
}

void Darwin::printGrid () {
	cout << "  ";
	for (int j = 0; j < width_; ++j) {
		cout << j % 10;
	}
	for (int i = 0; i < height_; ++i) {
		cout << "\n";
		cout << i % 10;
		cout << " ";
		for (int j = 0; j < width_; ++j) {
			cout << grid[i][j];
		}
	}
	cout << "\n\n";
}

void Darwin::run (int const turns) {
	for (int i = 0; i <= turns; i++) {
		turn(i, true);
	}
}

Darwin::Iterator Darwin::begin() { return data_.begin(); }

Darwin::Iterator Darwin::end() { return data_.end(); }

template<typename T>
const T& Darwin::at(int i) { return data_.at(i); }

Darwin::~Darwin(){

}


