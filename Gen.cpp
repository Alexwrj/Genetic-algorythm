//
//  Gen.cpp
//  Genetic algorythm
//
//  Created by Alexander Fomenko on 20/11/2018.
//  Copyright © 2018 Alexander Fomenko. All rights reserved.
//

#include "Gen.hpp"

Unit::Unit()
{
}

Unit::~Unit(){}

void Unit::begin()
{
    initPopulation();
    int counter = 1;
    
    for (int i = 0; i < MAX_ITERATIONS; i++)
    {
        cout << "Iteration: " << counter++;
        select();
        if (population[0].fitness == 0) break;
        cross();
    }

}

void Unit::calculateFitness(Gene &gene)
{
    unsigned length = eliteString.size();
    int fitness = 0;
    
    for (unsigned j = 0; j < length; j++)
    {
        fitness += abs(eliteString[j] - gene.str[j]);
    }
    gene.fitness = fitness;
}

void Unit::select()
{
    
    
    for (int i = 0; i < MAX_POPULATION; i++)
    {
        calculateFitness(population[i]);
    }
    
    sortByFitness();
    
    cout << "\nThe best is: " << population[0].str << " (" << population[0].fitness << ")\n\n";
    
    int eliteSampleNumber = ELITE_PERCENT * MAX_POPULATION;
    
    //choose elite
    for (int i = 0; i < eliteSampleNumber; i++)
    {
        elite.push_back(population[i]);
    }
    
    //create parents
    for (int i = eliteSampleNumber; i < MAX_POPULATION; i++)
    {
        int index = rand() % (MAX_POPULATION - eliteSampleNumber) + eliteSampleNumber;
        
        if (i != index
            && (find(usedIndecies.begin(), usedIndecies.end(), index) == usedIndecies.end())
            && (find(usedIndecies.begin(), usedIndecies.end(), i) == usedIndecies.end())
            )
        {
            usedIndecies.push_back(index);
            if (population[i].fitness < population[index].fitness)
            {
                parents.push_back(population[i]);
            }
            else
            {
                parents.push_back(population[index]);
            }
        }
    }
    usedIndecies.clear();
}

void Unit::cross()
{
    int length = eliteString.size();
    population.clear();
    
    //append elite generation
    population.insert(std::end(population), std::begin(elite), std::end(elite));
    
    //generate new units
    while (population.size() != MAX_POPULATION)
    {
        int index1 = rand() % parents.size();
        int index2 = rand() % parents.size();
        
        int div1 = rand() % eliteString.size();
        int div2 = rand() % eliteString.size();
        
        if (div1 > div2) swap(div1, div2);
        Gene crossedGenes;
        
        crossedGenes.str = parents[index1].str;
        
        for (int i = div1; i < div2; i++)
        {
            crossedGenes.str[i] = parents[index2].str[i];
        }
        
        if (rand() < MUTATION_PROBABILITY)
        {
            mutate(crossedGenes);
        }
        
        calculateFitness(crossedGenes);
        population.push_back(crossedGenes);
    }
    
    parents.clear();
    elite.clear();
}

void Unit::initPopulation()
{
    
    
    for (int i = 0; i < MAX_POPULATION; i++)
    {
        Gene gene;
        
        gene.fitness = 0;
        gene.str = "";
        gene.str.resize(eliteString.size());
        
        for (int j = 0; j < eliteString.size(); j++)
        {
            gene.str[j] = rand() % 91 + 32;
        }

        population.push_back(gene);
    }
}

void Unit::mutate(Gene &gene)
{
    
    
    int length = gene.str.size();
    
    gene.str[rand() % length] = rand() % 91 + 32;
}

bool Unit::fitnessSort(Gene gene1, Gene gene2)
{
    return (gene1.fitness < gene2.fitness);
}

void Unit::sortByFitness()
{
    sort(population.begin(), population.end(), fitnessSort);
}
