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

/**
 * Species Class, keep manage and owner of
 * a program (a set of instructions).
 */
class Species {
	private:

		/**
     	* Two params constructor for Instruction. The command and target
     	* of the Instruction.
     	*/
		pair<string, int> instruction_;

		/**
     	* vector constructor if instruction pairs
     	*/
		vector<pair<string, int>> program;

		/**
     	* name of the this Specie object
     	*/
		string name_;

		/**
     	* line to execute in the set of instrauctions
     	*/
		int line_;

		/**
     	* the name says what it does
     	*/
		void incrementLine (int&);

		FRIEND_TEST(DarwinFixture, addIntructions_1);
		FRIEND_TEST(DarwinFixture, addIntructions_2);
		FRIEND_TEST(DarwinFixture, addIntructions_3);
		FRIEND_TEST(DarwinFixture, createCreature_1);
		FRIEND_TEST(DarwinFixture, createCreature_2);
		FRIEND_TEST(DarwinFixture, createCreature_3);

	public:

		/**
     	* default constructor that best is gonna use to 
     	* and match the example best format from the asigment
     	* instruction
     	*/
		Species ();


		/**
     	* all other species constructor 
     	*/
		Species (string const name);

		/**
     	* add instruction to this specie program
     	* in this case it will add an action type
     	* instruction
     	*/
		const void addInstruction (string const instruction);

		/**
     	* add instruction to this specie program
     	* in this case it will add a control(with 
     	* target) instruction
     	*/
		const void addInstruction (string const, int const);

		/**
     	* all >>, <<, >, <, means arrows with directions
     	* of how the data flows between objects, those 
     	* operators were overloaded to adapt to my design
     	*/
		template<typename Cl>
		char operator>> (Cl c);

		template<typename Cl>
		int operator> (Cl c);

		void operator< (int x);

		/**
     	* program manager
     	*/
		int execute (const bool wall, const bool empty, const bool enemy);
};


/**
 * class Creature has a specie, owner of the direction, 
 * and a program counter, it can be many creatures per 
 * one specie 
 */
class Creature {
	private:

		/**
 		 * direction at what this creature is facing
 		 */
		string direction_;

		/**
		 * program counter, keeping track of lines that
		 * are executing 
		 */
		int program_counter;

		FRIEND_TEST(DarwinFixture, createCreature_1);
		FRIEND_TEST(DarwinFixture, createCreature_2);
		FRIEND_TEST(DarwinFixture, createCreature_3);
		
	public:

		/**
 		 * this creature Specie, got from the user input
		 */
		Species specie_;

		/**
		 * default constructor, used by RunDarwin to construct
		 * multiples creatures fast, and put them in a vector
		 */
		Creature ();

		/**
		 * Creature constructor used on normal cases when users
		 * inputs. It takes the specie and the direction of the
		 * creature as arguments
		 */
		Creature (Species&, string const);

		/**
		 * Creature constructor used when a creature is infested
		 * by this creature, this constructor allow the 
		 * metamorphosis
		 */
		Creature (Creature&, string const, int const pc = 0);

		/**
		 * overloaded operator used to compare 2 different class
		 * objects and get the direction is true the comparision 
		 * Creature and strings
		 */
		bool operator== (string direction);

		/**
		 * another arrows showing the direction of the data flows
		 */
		template<typename Cl>
		auto operator>> (Cl c) -> decltype(specie_ >> this);

		/**
		 * execute the part of the program this class is 
		 * responsable of, for what it is not responsable, it
		 * then delegates to others
		 */
		int execute (const bool wall, const bool empty, const bool enemy);
		
};

/**
 * Class Darwin is the World, when every action start and finish
 * contains a two-dimensional grid. 
 * Each square in the world contain at most one creature.
 * keeping and manages the grid, its creatures and the turns.
 * Darwin is iterable with several iterator operarions.
 * Darwin iterares through turns.
 */
class Darwin {
	private:

		typedef vector<string> _turns_;

		/**
		 * two-dimensional vector representing the two-dimensional grid 
		 */
		vector<vector<char>> grid;

		/**
		 * container for turns, to be able to iterate 
		 */
		_turns_ turns;

		/**
		 * current turn result and what is gonna be putting back
		 * on the turns container
		 */
		string currentTurn;

		/**
		 * variables where to store input data and others helpers
		 */
		int width_, height_, index, add;

		/**
		 * to store the status of those conditions and use later
		 */
		bool wall_, empty_, enemy_;

		/**
		 * keep track of the creatures movements of the game
		 * every element is a pointer to a creature object
		 * and moving this pointer through the container on the
		 * same position the creatures are moving on the grid
		 * allow faster and less complex methods 
		 */
		vector<vector<Creature*>> creatures;

		/**
		 * where wall, empty, and enemy are setted
		 */
		template<typename T>
		void managerWallEmptyInfect (Creature&, T, int, int);

		/**
		 * this method did not get the direction directly from 
		 * creatures, it just ask creatures if it has a direction
		 * x and deduce what is the direction from this, the overloaded
		 * == operator is used to compare Creatures and strings
		 */
		string direction (Creature&);

		/**
		 * after all turn data is processed, then here this result is
		 * formated in a showable way, and then outputed, the final
		 * result or an specific turn can be obtained through iteration  
		 */
		void makeTurn(bool display = true);

		FRIEND_TEST(DarwinFixture, addCreature_1);
		FRIEND_TEST(DarwinFixture, addCreature_2);
		FRIEND_TEST(DarwinFixture, addCreature_3);
		FRIEND_TEST(DarwinFixture, runSimulations_1);
		FRIEND_TEST(DarwinFixture, runSimulations_2);
		FRIEND_TEST(DarwinFixture, runSimulations_3);

	public:

		/**
		 * Darwin constructor  
		 */
		Darwin (int, int);

		/**
		 * add a Creature to a vector of creatures and to the grid  
		 */
		const void addCreature (Creature&, int const, int const);


		/**
		 * Darwin iterator definitions, helpers and operations  
		 */
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
		
		/**
		 * Darwin iterator index operations  
		 */
		const string& at(int i) const;
		string& operator[](int);

		/**
		 * used to acces to specific turns of a running  
		 */
		void turn (int, bool display = true);

		/**
		 * used to run averything at a time  
		 */
		void run (int const, bool display = true);

	private:
		/**
		 * pointer iterator  
		 */
		pointer ptr_;

};

#endif // Darwin_h
