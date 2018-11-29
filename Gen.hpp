//
//  Gen.hpp
//  Genetic algorythm
//
//  Created by Alexander Fomenko on 20/11/2018.
//  Copyright © 2018 Alexander Fomenko. All rights reserved.
//

#ifndef Gen_hpp
#define Gen_hpp

#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <string>
#include <time.h>
#include <iostream>

using namespace std;

struct Gene
{
    string str;
    int fitness;
};

class Unit
{
public:
    Unit();
    ~Unit();
    void begin();
    
private:
    const string eliteString = "The quick brown fox jumps over the lazy dog";
    vector<Gene> population;
    vector<Gene> parents;
    vector<Gene> elite;
    vector<int>usedIndecies;
    const int MAX_POPULATION = 2048;
    const int MAX_ITERATIONS = 8000;
    const float ELITE_PERCENT = 0.0f;
    const float MUTATION_PROBABILITY = RAND_MAX * 0.25f;
    
    static bool fitnessSort(Gene gene1, Gene gene2);
    void sortByFitness();
    void select();
    void chooseParent();
    void cross();
    void initPopulation();
    void mutate(Gene &gene);
    void calculateFitness(Gene &gene);
};
#endif /* Gen_hpp */
