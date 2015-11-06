// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2015
// Glenn P. Downing
// -----------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Darwin.h"

string dir[] = {"west", "north", "east", "south"};

vector<Creature> foods;
vector<Creature> hoppers;
vector<Creature> rovers;
vector<Creature> traps;
vector<Creature> bests;


void addCreatures (Darwin& d, Species& Food, Species& Hopper, Species& Rover, Species& Trap, Species& Best, bool best) {
    int row, col, r, rr;

    foods.resize(0);
    for (int i = 0; i < 10; i++) {
        r = rand() % 4;
        foods.push_back(Creature(Food, dir[r]));
    }

    for (int i = 0; i < int(foods.size()); i++) {
        rr = rand() % 5184;
        row = rr / 72;
        col = rr % 72;
        d.addCreature(foods[i], row, col);
    }

    hoppers.resize(0);
    for (int i = 0; i < 10; i++) {
        r = rand() % 4;
        hoppers.push_back(Creature(Hopper, dir[r]));
    }

    for (int i = 0; i < int(hoppers.size()); i++) {
        rr = rand() % 5184;
        row = rr / 72;
        col = rr % 72;
        d.addCreature(hoppers[i], row, col);
    }

    rovers.resize(0);
    for (int i = 0; i < 10; i++) {
        r = rand() % 4;
        rovers.push_back(Creature(Rover, dir[r]));
    }

    for (int i = 0; i < int(rovers.size()); i++) {
        rr = rand() % 5184;
        row = rr / 72;
        col = rr % 72;
        d.addCreature(rovers[i], row, col);
    }

    traps.resize(0);
    for (int i = 0; i < 10; i++) {
        r = rand() % 4;
        traps.push_back(Creature(Trap, dir[r]));
    }

    for (int i = 0; i < int(traps.size()); i++) {
        rr = rand() % 5184;
        row = rr / 72;
        col = rr % 72;
        d.addCreature(traps[i], row, col);
    }

    if (best) {
        bests.resize(0);
        for (int i = 0; i < 10; i++) {
            r = rand() % 4;
            bests.push_back(Creature(Best, dir[r]));
        }

        for (int i = 0; i < int(bests.size()); i++) {
            rr = rand() % 5184;
            row = rr / 72;
            col = rr % 72;
            d.addCreature(bests[i], row, col);
        }
    }
}


// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */
    Species Food("food");
    Food.addInstruction("left");
    Food.addInstruction("go", 0);


    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
    Species Hopper("hopper");
    Hopper.addInstruction("hop");
    Hopper.addInstruction("go", 0);


    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */
    Species Rover("rover");
    Rover.addInstruction("if_enemy", 9);
    Rover.addInstruction("if_empty", 7);
    Rover.addInstruction("if_random", 5);
    Rover.addInstruction("left");
    Rover.addInstruction("go", 0);
    Rover.addInstruction("right");
    Rover.addInstruction("go", 0);
    Rover.addInstruction("hop");
    Rover.addInstruction("go", 0);
    Rover.addInstruction("infect");
    Rover.addInstruction("go", 0);


    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */

    Species Trap("trap");
    Trap.addInstruction("if_enemy", 3);
    Trap.addInstruction("left");
    Trap.addInstruction("go", 0);
    Trap.addInstruction("infect");
    Trap.addInstruction("go", 0);

    // ----
    // best
    // ----

    /*
     0: if_enemy 2         
     1: go 4
     2: infect
     3: go 0
     4: if_enemy 0         
     5: left
     6: if_enemy 0
     7: left
     8: if_enemy 0
     9: left
     10: if_enemy 0
     11: if_random 33 
     12: left
     13: if_enemy 0
     14: if_random 33  
     15: left
     16: if_enemy 0
     17: if_random 33  
     18: left
     19: if_enemy 0
     20: if_random 33 
     21: if_enemy 0
     22: if_wall 28  
     23: if_random 26  
     24: left
     25: go 20
     26: hop
     27: go 20
     28: left          
     29: if_enemy 0
     30: if_random 33  
     31: left
     32: go 20
     33: if_enemy 0 
     34: if_empty 37
     35: left
     36: go 33
     37: if_random 34
     38: if_random 34
     39: if_random 34
     40: if_random 34
     41: if_random 34
     42: if_random 34
     43: go 0
    */

    Species Best;
    Best.addInstruction("if_enemy", 2);
    Best.addInstruction("go", 4);
    Best.addInstruction("infect");
    Best.addInstruction("go", 0);

    Best.addInstruction("if_enemy", 0);
    Best.addInstruction("left");
    Best.addInstruction("if_enemy", 0);
    Best.addInstruction("left");
    Best.addInstruction("if_enemy", 0);
    Best.addInstruction("left");
    Best.addInstruction("if_enemy", 0);
    Best.addInstruction("if_random", 33); 
    Best.addInstruction("left");
    Best.addInstruction("if_enemy", 0);
    Best.addInstruction("if_random", 33);   
    Best.addInstruction("left");
    Best.addInstruction("if_enemy", 0);
    Best.addInstruction("if_random", 33); 
    Best.addInstruction("left");
    Best.addInstruction("if_enemy", 0);
    Best.addInstruction("if_random", 33);   
    Best.addInstruction("if_enemy", 0);
    Best.addInstruction("if_wall", 28);
    Best.addInstruction("if_random", 26);   
    Best.addInstruction("left");
    Best.addInstruction("go", 20);
    Best.addInstruction("hop");
    Best.addInstruction("go", 20);
    Best.addInstruction("left");          
    Best.addInstruction("if_enemy", 0);
    Best.addInstruction("if_random", 33);  
    Best.addInstruction("left");
    Best.addInstruction("go", 20);
    Best.addInstruction("if_enemy", 0);
    Best.addInstruction("if_empty", 37);
    Best.addInstruction("left");
    Best.addInstruction("go", 20);
    Best.addInstruction("if_random", 33); 
    Best.addInstruction("if_random", 33); 
    Best.addInstruction("if_random", 33); 
    Best.addInstruction("if_random", 33); 
    Best.addInstruction("if_random", 33); 
    Best.addInstruction("if_random", 33); 
    Best.addInstruction("go", 20);

    // ----------
    // darwin 8x8
    // ----------

    cout << "*** Darwin 8x8 ***" << endl;
    /*
    8x8 Darwin
    Food,   facing east,  at (0, 0)
    Hopper, facing north, at (3, 3)
    Hopper, facing east,  at (3, 4)
    Hopper, facing south, at (4, 4)
    Hopper, facing west,  at (4, 3)
    Food,   facing north, at (7, 7)
    Simulate 5 moves.
    Print every grid.
    */
    Darwin x(8, 8);
    Creature f1(Food, "east");
    Creature h1(Hopper, "north");
    Creature h2(Hopper, "east");
    Creature h3(Hopper, "south");
    Creature h4(Hopper, "west");
    Creature f2(Food, "north");
    x.addCreature(f1, 0, 0);
    x.addCreature(h1, 3, 3);
    x.addCreature(h2, 3, 4);
    x.addCreature(h3, 4, 4);
    x.addCreature(h4, 4, 3);
    x.addCreature(f2, 7, 7);
    x.run(5);


    // ----------
    // darwin 7x9
    // ----------

    cout << "*** Darwin 7x9 ***" << endl;
    srand(0);
    /*
    7x9 Darwin
    Trap,   facing south, at (0, 0)
    Hopper, facing east,  at (3, 2)
    Rover,  facing north, at (5, 4)
    Trap,   facing west,  at (6, 8)
    Simulate 5 moves.
    Print every grid.
    */
    Darwin y(7, 9);
    Creature t1(Trap, "south");
    Creature h5(Hopper, "east");
    Creature r1(Rover, "north");
    Creature t2(Trap, "west");
    y.addCreature(t1, 0, 0);
    y.addCreature(h5, 3, 2);
    y.addCreature(r1, 5, 4);
    y.addCreature(t2, 6, 8);
    y.run(5);


    // ------------
    // darwin 72x72
    // without best
    // ------------

    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */
    Darwin z(72, 72);

    addCreatures(z, Food, Hopper, Rover, Trap, Best, false);

    for (int i = 0; i < 1001; ++i) {
        if ((i < 10) || (i % 100 == 0))
            z.turn(i, true);
        else z.turn(i, false);
    }

    // ------------
    // darwin 72x72
    // with best
    // ------------

    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: 0:west, 1:north, 2:east, 3:south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */
    Darwin v(72, 72);
    
    //int row, col, r, rr;

    addCreatures(v, Food, Hopper, Rover, Trap, Best, true);

    for (int i = 0; i < 1001; ++i) {
        if ((i < 10) || (i % 100 == 0))
            v.turn(i, true);
        else v.turn(i, false);
    }

    return 0;}
