#ifndef Darwin_h
#define Darwin_h

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include <vector>	 //vector
#include <utility>	 //pair
#include <typeinfo>

#include "gtest/gtest.h"

using namespace std;

class Species {
	private:

		pair<string, int> instruction_;

		vector<pair<string, int>> program;

		string name_;

		int line_;

		void incrementLine (int&);

		FRIEND_TEST(DarwinFixture, addIntructions_1);
		FRIEND_TEST(DarwinFixture, addIntructions_2);
		FRIEND_TEST(DarwinFixture, addIntructions_3);
		FRIEND_TEST(DarwinFixture, createCreature_1);
		FRIEND_TEST(DarwinFixture, createCreature_2);
		FRIEND_TEST(DarwinFixture, createCreature_3);

	public:

		Species ();

		Species (string const name);

		const void addInstruction (string const instruction);

		const void addInstruction (string const, int const);

		template<typename Cl>
		char operator>> (Cl c);

		template<typename Cl>
		int operator> (Cl c);

		void operator< (int x);

		int execute (const bool wall, const bool empty, const bool enemy);
};

class Creature {
	private:

		string direction_;

		int program_counter;

		FRIEND_TEST(DarwinFixture, createCreature_1);
		FRIEND_TEST(DarwinFixture, createCreature_2);
		FRIEND_TEST(DarwinFixture, createCreature_3);
		
	public:

		Species specie_;

		Creature ();

		Creature (Species&, string const);

		Creature (Creature&, string const, int const pc = 0);

		bool operator== (string direction);

		template<typename Cl>
		auto operator>> (Cl c) -> decltype(specie_ >> this);

		bool operator== (Creature& c);

		int execute (const bool wall, const bool empty, const bool enemy);
		
};

class Darwin {
	private:

		typedef vector<string> _turns_;

		vector<vector<char>> grid;

		vector<string> turns;

		string currentTurn;

		int width_, height_, index, add;

		bool wall_, empty_, enemy_;

		vector<vector<Creature*>> creatures;

		template<typename T>
		void managerWallEmptyInfect (Creature&, T, int, int);

		string direction (Creature&);

		FRIEND_TEST(DarwinFixture, addCreature_1);
		FRIEND_TEST(DarwinFixture, addCreature_2);
		FRIEND_TEST(DarwinFixture, addCreature_3);
		FRIEND_TEST(DarwinFixture, runSimulations_1);
		FRIEND_TEST(DarwinFixture, runSimulations_2);
		FRIEND_TEST(DarwinFixture, runSimulations_3);

	public:

		Darwin (int, int);

		const void addCreature (Creature&, int const, int const);

		typedef _turns_::iterator Iterator;

		typedef _turns_::iterator* pointer;

		Iterator it;

		int size();

  		const Iterator begin();

		const Iterator end();

		Iterator operator++();

		Iterator operator++(int);

		bool operator==(const Darwin& rhs);

		bool operator!=(const Darwin& rhs);

		template<typename T>
		T& operator* ();

		const string& at(int i) const;

		string& operator[](int); 

		void turn (int, bool display = true);

		void makeTurn(bool display = true);

		void run (int const, bool display = true);

	private:
		pointer ptr_;

};

#endif // Darwin_h
