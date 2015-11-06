// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Darwin.h"

using namespace std;

bool notDisplay = false;

vector<string> result;

// -----------
// TestDarwin
// -----------

// Rover without random
Species rover () {
    Species Rover("rover");
    Rover.addInstruction("if_enemy", 9);
    Rover.addInstruction("if_empty", 7);
    Rover.addInstruction("go", 5);
    Rover.addInstruction("left");
    Rover.addInstruction("go", 0);
    Rover.addInstruction("right");
    Rover.addInstruction("go", 0);
    Rover.addInstruction("hop");
    Rover.addInstruction("go", 0);
    Rover.addInstruction("infect");
    Rover.addInstruction("go", 0);
    return Rover;
}

// Best without random
Species best () {
    Species Best;
    Best.addInstruction("if_enemy", 9);
    Best.addInstruction("if_empty", 7);
    Best.addInstruction("go", 5);
    Best.addInstruction("right");
    Best.addInstruction("go", 0);
    Best.addInstruction("left");
    Best.addInstruction("go", 0);
    Best.addInstruction("hop");
    Best.addInstruction("go", 0);
    Best.addInstruction("infect");
    Best.addInstruction("go", 0);
    return Best;
}

Species trap () {
    Species Trap("trap");
    Trap.addInstruction("if_enemy", 3);
    Trap.addInstruction("left");
    Trap.addInstruction("go", 0);
    Trap.addInstruction("infect");
    Trap.addInstruction("go", 0);
    return Trap;
}

Species hopper () {
    Species Hopper("hopper");
    Hopper.addInstruction("hop");
    Hopper.addInstruction("go", 0);
    return Hopper;
}

Species food () {
    Species Food("food");
    Food.addInstruction("left");
    Food.addInstruction("go", 0);
    return Food;
}

Darwin darwin_a () {
    Species Rover = rover();
    Darwin a(3, 5);
    Creature r10(Rover, "south");
    Creature r20(Rover, "east");
    Creature r30(Rover, "north");
    Creature r40(Rover, "west");
    a.addCreature(r10, 0, 0);
    a.addCreature(r20, 1, 2);
    a.addCreature(r30, 2, 3);
    a.addCreature(r40, 2, 4);
    a.run(3, notDisplay);
    
    result = {"Turn = 0.\n  01234\n0 r....\n1 ..r..\n2 ...rr\n\n",
              "Turn = 1.\n  01234\n0 .....\n1 r..r.\n2 ...rr\n\n",
              "Turn = 2.\n  01234\n0 .....\n1 ...rr\n2 r.r..\n\n",
              "Turn = 3.\n  01234\n0 ....r\n1 .....\n2 r.rr.\n\n"};

    return a;
}

Darwin darwin_b () {
    Species Best = best();
    Darwin b(5, 4);
    Creature b10(Best, "west");
    Creature b20(Best, "north");
    Creature b30(Best, "south");
    b.addCreature(b10, 0, 0);
    b.addCreature(b20, 1, 1);
    b.addCreature(b30, 2, 3);

    b.run(5, notDisplay);
    
    result = {"Turn = 0.\n  0123\n0 b...\n1 .b..\n2 ...b\n3 ....\n4 ....\n\n",
              "Turn = 1.\n  0123\n0 bb..\n1 ....\n2 ....\n3 ...b\n4 ....\n\n",
              "Turn = 2.\n  0123\n0 bb..\n1 ....\n2 ....\n3 ....\n4 ...b\n\n",
              "Turn = 3.\n  0123\n0 bb..\n1 ....\n2 ....\n3 ....\n4 ...b\n\n",
              "Turn = 4.\n  0123\n0 bb..\n1 ....\n2 ....\n3 ...b\n4 ....\n\n",
              "Turn = 5.\n  0123\n0 bb..\n1 ....\n2 ...b\n3 ....\n4 ....\n\n"};

    return b;
}

Darwin darwin_c () {
    Species Rover = rover();
    Species Food = food();
    Species Best = best();
    Darwin c(10, 10);
    Creature c10(Rover, "west");
    Creature c20(Rover, "north");
    Creature c30(Rover, "south");
    Creature c40(Food, "west");
    Creature c50(Food, "north");
    Creature c60(Food, "south");
    Creature c70(Best, "west");
    Creature c80(Best, "west");
    Creature c90(Best, "east");
    c.addCreature(c10, 9, 9);
    c.addCreature(c20, 9, 0);
    c.addCreature(c30, 0, 9);
    c.addCreature(c40, 4, 4);
    c.addCreature(c50, 5, 5);
    c.addCreature(c60, 6, 6);
    c.addCreature(c70, 4, 5);
    c.addCreature(c80, 5, 6);
    c.addCreature(c90, 6, 5);

    c.run(10, notDisplay);
    
    result = {"Turn = 0.\n  0123456789\n0 .........r\n1 ..........\n2 ..........\n3 ..........\n4 ....fb....\n5 .....fb...\n6 .....bf...\n7 ..........\n8 ..........\n9 r........r\n\n",
              "Turn = 1.\n  0123456789\n0 ..........\n1 .........r\n2 ..........\n3 ..........\n4 ....bb....\n5 .....bb...\n6 .....bb...\n7 ..........\n8 r.........\n9 ........r.\n\n",
              "Turn = 2.\n  0123456789\n0 ..........\n1 ..........\n2 .........r\n3 ....b.....\n4 ....bb....\n5 .....b....\n6 .....b....\n7 r.....b...\n8 ..........\n9 .......r..\n\n",
              "Turn = 3.\n  0123456789\n0 ..........\n1 ..........\n2 ..........\n3 ....bb...r\n4 ...b......\n5 ....bb....\n6 r.........\n7 ..........\n8 ......b...\n9 ......r...\n\n",
              "Turn = 4.\n  0123456789\n0 ..........\n1 ..........\n2 ....bb....\n3 ..........\n4 ...b.b...r\n5 r..b......\n6 ..........\n7 ..........\n8 ......b...\n9 ......b...\n\n",
              "Turn = 5.\n  0123456789\n0 ..........\n1 ....bb....\n2 ..........\n3 .....b....\n4 ..b.......\n5 r..b.....r\n6 ..........\n7 ..........\n8 ......b...\n9 .....b....\n\n",
              "Turn = 6.\n  0123456789\n0 ....bb....\n1 ..........\n2 .....b....\n3 ..........\n4 rb........\n5 ..b.......\n6 .........r\n7 ......b...\n8 ..........\n9 ....b.....\n\n",
              "Turn = 7.\n  0123456789\n0 ....bb....\n1 .....b....\n2 ..........\n3 r.........\n4 b.........\n5 .b........\n6 ..........\n7 ......b..r\n8 ..........\n9 ...b......\n\n",
              "Turn = 8.\n  0123456789\n0 ....bb....\n1 .....b....\n2 r.........\n3 ..........\n4 b.........\n5 b.........\n6 ......b...\n7 ..........\n8 .........r\n9 ..b.......\n\n",
              "Turn = 9.\n  0123456789\n0 ....bb....\n1 r....b....\n2 ..........\n3 b.........\n4 ..........\n5 b.....b...\n6 ..........\n7 ..........\n8 ..........\n9 ..b......r\n\n",
              "Turn = 10.\n  0123456789\n0 r...bb....\n1 .....b....\n2 b.........\n3 ..........\n4 b.....b...\n5 ..........\n6 ..........\n7 ..........\n8 ..........\n9 .b.......r\n\n"};

    return c;
}



// ----
// iterable
// ----

TEST(DarwinFixture, iterable_1) {
    result.resize(0);

    Darwin a = darwin_a();

    int j = 0;

    Darwin::Iterator first = a.begin();

    Darwin::Iterator last = a.end();

    while (first != last) {
        ASSERT_EQ(*first, result[j]);
        ++j;
        ++first;
    }
}

TEST(DarwinFixture, iterable_2) {
    result.resize(0);

    Darwin b = darwin_b();

    int j = 0;

    Darwin::Iterator first = b.begin();

    Darwin::Iterator last = b.end();
    
    while (first != last) {
        ASSERT_EQ(*first, result[j]);
        ++j;
        ++first;
    }
}

TEST(DarwinFixture, iterable_3) {
    result.resize(0);

    Darwin c = darwin_c();

    int j = 0;

    Darwin::Iterator first = c.begin();

    Darwin::Iterator last = c.end();
    
    while (first != last) {
        ASSERT_EQ(*first, result[j]);
        ++j;
        ++first;
    }
}


// ----
// indexable
// ----

TEST(DarwinFixture, indexable_1) {
    result.resize(0);

    Darwin a = darwin_a();

    for (int j = 0; j < a.size(); j++) {
        ASSERT_EQ(a.at(j), result[j]);
        ASSERT_EQ(a[j], result[j]);
    }
}

TEST(DarwinFixture, indexable_2) {
    result.resize(0);

    Darwin b = darwin_b();

    for (int j = 0; j < b.size(); j++) {
        ASSERT_EQ(b.at(j), result[j]);
        ASSERT_EQ(b[j], result[j]);
    }
}

TEST(DarwinFixture, indexable_3) {
    result.resize(0);

    Darwin c = darwin_c();

    for (int j = 0; j < c.size(); j++) {
        ASSERT_EQ(c.at(j), result[j]);
        ASSERT_EQ(c[j], result[j]);
    }
}


// ----
// addInstructions
// ----

TEST(DarwinFixture, addIntructions_1) {
    Species Test_1;

    Test_1.addInstruction("if_enemy", 4);
    ASSERT_EQ(Test_1.program[0].first, "if_enemy");
    ASSERT_EQ(Test_1.program[0].second, 4);

    Test_1.addInstruction("hop");
    ASSERT_EQ(Test_1.program[1].first, "hop");
    ASSERT_EQ(Test_1.program[1].second, -1);

}

TEST(DarwinFixture, addIntructions_2) {
    Species Test_2;

    Test_2.addInstruction("if_empty", 5);
    ASSERT_EQ(Test_2.program[0].first, "if_empty");
    ASSERT_EQ(Test_2.program[0].second, 5);

    Test_2.addInstruction("left");
    ASSERT_EQ(Test_2.program[1].first, "left");
    ASSERT_EQ(Test_2.program[1].second, -1);
}

TEST(DarwinFixture, addIntructions_3) {
    Species Test_3;

    Test_3.addInstruction("infect");
    ASSERT_EQ(Test_3.program[0].first, "infect");
    ASSERT_EQ(Test_3.program[0].second, -1);

    Test_3.addInstruction("right");
    ASSERT_EQ(Test_3.program[1].first, "right");
    ASSERT_EQ(Test_3.program[1].second, -1);

    Test_3.addInstruction("go", 0);
    ASSERT_EQ(Test_3.program[2].first, "go");
    ASSERT_EQ(Test_3.program[2].second, 0);
}


// ----
// createCreature
// ----

TEST(DarwinFixture, createCreature_1) {
    Species Rover = rover();
    Species Food = food();
    Darwin d(5, 5);
    Creature d1(Rover, "south");
    Creature d2(Food, "west");
    Creature d3(d1, "south");
    Creature d4(d2, "west");

    ASSERT_EQ(d1.specie_.name_.compare("rover"), 0);
    ASSERT_EQ(d2.specie_.name_.compare("food"), 0);
    ASSERT_EQ(d3.specie_.name_.compare("rover"), 0);
    ASSERT_EQ(d2.specie_.name_.compare("food"), 0);
}

TEST(DarwinFixture, createCreature_2) {
    Species Trap = trap();
    Species Best = best();
    Darwin e(3, 3);
    Creature e1(Trap, "south");
    Creature e2(Best, "west");
    Creature e3(e1, "south");
    Creature e4(e2, "west");

    ASSERT_EQ(e1.specie_.name_.compare("trap"), 0);
    ASSERT_EQ(e2.specie_.name_.compare("best"), 0);
    ASSERT_EQ(e3.specie_.name_.compare("trap"), 0);
    ASSERT_EQ(e4.specie_.name_.compare("best"), 0);

}

TEST(DarwinFixture, createCreature_3) {
    Species Hopper = hopper();
    Darwin f(4, 4);
    Creature f1(Hopper, "south");
    Creature f2(f1, "west");

    ASSERT_EQ(f1.specie_.name_.compare("hopper"), 0);
    ASSERT_EQ(f2.specie_.name_.compare("hopper"), 0);
}


// ----
// addCreature
// ----
   
TEST(DarwinFixture, addCreature_1) {
    Species Rover = rover();
    Species Food = food();
    Darwin g(5, 5);
    Creature g1(Rover, "south");
    Creature g2(Food, "west");
    g.addCreature(g1, 0, 0);
    g.addCreature(g2, 4, 4);

    ASSERT_EQ(g.grid[0][0], 'r');
    ASSERT_EQ(g.grid[4][4], 'f');
}
 
TEST(DarwinFixture, addCreature_2) {
    Species Trap = trap();
    Species Best = best();
    Darwin h(5, 2);
    Creature h1(Trap, "south");
    Creature h2(Best, "west");

    h.addCreature(h1, 3, 1);
    h.addCreature(h2, 2, 0);

    ASSERT_EQ(h.grid[3][1], 't');
    ASSERT_EQ(h.grid[2][0], 'b');  
}

TEST(DarwinFixture, addCreature_3) {
    Species Hopper = hopper();
    Darwin i(6, 8);
    Creature i1(Hopper, "south");
    Creature i2(Hopper, "south");
    Creature i3(Hopper, "south");
    Creature i4(Hopper, "south");

    i.addCreature(i1, 0, 0);
    i.addCreature(i2, 1, 2);
    i.addCreature(i3, 3, 4);
    i.addCreature(i4, 5, 7);

    ASSERT_EQ(i.grid[0][0], 'h');
    ASSERT_EQ(i.grid[1][2], 'h');
    ASSERT_EQ(i.grid[3][4], 'h');
    ASSERT_EQ(i.grid[5][7], 'h');   
}


// -----
// runSimulations
// -----

TEST(DarwinFixture, runSimulations_1) {
    Species Best = best();
    Species Food = food();
    Species Rover = rover();
    Darwin j(3, 5);
    Creature j1(Rover, "south");
    Creature j2(Rover, "north");
    Creature j3(Best, "east");
    Creature j4(Food, "west");
    j.addCreature(j1, 0, 0);
    j.addCreature(j2, 1, 2);
    j.addCreature(j3, 2, 3);
    j.addCreature(j4, 2, 4);

    j.turn(0, notDisplay);
    string simulations = j.currentTurn;
    for (int i = 1; i < 7; i++) {
        j.turn(i, notDisplay);
        simulations = simulations + j.currentTurn;
    }

    ASSERT_EQ(simulations.compare("Turn = 0.\n  01234\n0 r....\n1 ..r..\n2 ...bf\n\n"
                                  "Turn = 1.\n  01234\n0 ..r..\n1 r....\n2 ...bb\n\n"
                                  "Turn = 2.\n  01234\n0 ..r..\n1 .....\n2 r..bb\n\n"
                                  "Turn = 3.\n  01234\n0 .....\n1 r.rbb\n2 .....\n\n"
                                  "Turn = 4.\n  01234\n0 r....\n1 ...bb\n2 ..r..\n\n"
                                  "Turn = 5.\n  01234\n0 r..bb\n1 .....\n2 ..r..\n\n"
                                  "Turn = 6.\n  01234\n0 ...bb\n1 r....\n2 .r...\n\n"), 0);

}

TEST(DarwinFixture, runSimulations_2) {
    Species Best = best();
    Species Hopper = food();
    Species Trap = rover();
    Darwin k(4, 4);
    Creature k1(Best, "south");
    Creature k2(Hopper, "north");
    Creature k3(Trap, "east");
    Creature k4(Best, "west");
    k.addCreature(k1, 0, 0);
    k.addCreature(k2, 1, 2);
    k.addCreature(k3, 2, 3);
    k.addCreature(k4, 3, 2);

    k.turn(0, notDisplay);
    string simulations = k.currentTurn;
    for (int j = 1; j < 9; j++) {
        k.turn(j, notDisplay);
        simulations = simulations + k.currentTurn;
    }

    ASSERT_EQ(simulations.compare("Turn = 0.\n  0123\n0 b...\n1 ..f.\n2 ...r\n3 ..b.\n\n"
                                  "Turn = 1.\n  0123\n0 ....\n1 b.f.\n2 ...r\n3 .b..\n\n"
                                  "Turn = 2.\n  0123\n0 ....\n1 ..f.\n2 b...\n3 .b.r\n\n"
                                  "Turn = 3.\n  0123\n0 ....\n1 ..f.\n2 ....\n3 bb.r\n\n"
                                  "Turn = 4.\n  0123\n0 ....\n1 ..f.\n2 bb..\n3 ..r.\n\n"
                                  "Turn = 5.\n  0123\n0 ....\n1 bbf.\n2 ....\n3 .r..\n\n"
                                  "Turn = 6.\n  0123\n0 bb..\n1 ..f.\n2 ....\n3 r...\n\n"
                                  "Turn = 7.\n  0123\n0 bb..\n1 ..f.\n2 ....\n3 r...\n\n"
                                  "Turn = 8.\n  0123\n0 bb..\n1 ..f.\n2 r...\n3 ....\n\n"), 0);
}

TEST(DarwinFixture, runSimulations_3) {
    Species Best = best();
    Species Food = food();
    Species Hopper = rover();
    Darwin m(2, 6);
    Creature m1(Food, "south");
    Creature m2(Best, "north");
    Creature m3(Best, "east");
    Creature m4(Hopper, "west");
    m.addCreature(m1, 0, 0);
    m.addCreature(m2, 1, 2);
    m.addCreature(m3, 1, 3);
    m.addCreature(m4, 0, 4);

    m.turn(0, notDisplay);
    string simulations = m.currentTurn;
    for (int j = 1; j < 3; j++) {
        m.turn(j, notDisplay);
        simulations = simulations + m.currentTurn;
    }

    ASSERT_EQ(simulations.compare("Turn = 0.\n  012345\n0 f...r.\n1 ..bb..\n\n"
                                  "Turn = 1.\n  012345\n0 f.br..\n1 ....b.\n\n"
                                  "Turn = 2.\n  012345\n0 f.rr..\n1 .....b\n\n"), 0);
}


