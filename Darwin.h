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

using namespace std;

class Species {
	private:

		pair<string, int> instruction_;

		vector<pair<string, int>> program;

		string name_;

		int line_;

		void incrementLine (int&);

	public:

		Species ();

		Species (string const name);

		~Species();

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
		
	public:

		Species specie_;

		Creature ();

		Creature (Species&, string const);

		Creature (Creature&, string const, int const);

		~Creature();

		bool operator== (string direction);

		template<typename Cl>
		auto operator>> (Cl c) -> decltype(specie_ >> this);

		int execute (const bool wall, const bool empty, const bool enemy);
		
};

class Darwin {
	private:

		typedef vector<Creature> Creatures_;

		vector<vector<char>> grid;

		Creatures_ data_;

		int width_, height_, index, add;

		bool wall_, empty_, enemy_;

		vector<vector<Creature*>> creatures;

		template<typename T>
		void managerWallEmptyInfect (Creature&, T, int, int);

		string direction (Creature&);

		void printGrid ();

		Darwin ();

	public:

		Darwin (int, int);

		~Darwin();

		const void addCreature (Creature&, int const, int const);

		typedef Creatures_::iterator Iterator;

  		typedef Creatures_::const_iterator const_Iterator;

  		Iterator begin();

		Iterator end();

		template<typename T>
		const T& at(int i);

		void turn (int, bool);

		void run (int const turns);

};

#endif // Darwin_h
