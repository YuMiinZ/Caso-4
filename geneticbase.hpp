#ifndef _GENETICBASE_
#define _GENETICBASE_ 1
#include <vector>
#include "lib/cromodistribution.h"
#include "lib/individual.h"
#include <algorithm>


using namespace std;

class GeneticBase {
    private:
        vector<cromodistribution*> *representation;
        vector<individual*> *population;
        vector<individual*> *fitnessPopulation;
        vector<individual*> *unfitnessPopulation;
        vector<Area*> combinationTable;
        int populationQuantity;
        int targetGenerations;


        void evaluateFitness() {
            fitnessPopulation->clear();
            unfitnessPopulation->clear();
            //formula para fitness float resultado=(1/((sqrt(pow((x2-x1),2)+pow((y2-y1),2)))/10800)); //FORMULA

            for(int i=0;i<population->size(); i++) {
               population->at(i)->setFitnessValue(fitness(population->at(i)));

                if (population->at(i)->getFitnessValue()>50) {  // fitness criteria of selection never will be an absolute value always is relative to the population
                    fitnessPopulation->push_back(population->at(i));
                } else {
                    unfitnessPopulation->push_back(population->at(i));
                }
            }
        }

        float fitness(individual *pIndividual) {
            return rand()%100;
        }

        void reproduce(int pAmountOfChildrens) {
            // previous population will be cleared, full saved, partial saved depending on the problem
            population->clear();

            for(int i=0; i<pAmountOfChildrens; i++) {
                // select any two fitness parents
                int parent_a_index = rand()%fitnessPopulation->size();
                individual* parent_a = fitnessPopulation->at(parent_a_index);

                int parent_b_index = rand()%fitnessPopulation->size();
                individual* parent_b = fitnessPopulation->at(parent_b_index);

                population->push_back(cross(parent_a, parent_b));
            }
        }

        individual* cross(individual *pParent_a, individual *pParent_b) {
            // this operation will depends on: nibble size, fixed o variable point

            int cut_position = (rand() % (NIBBLE_SIZE-MIN_GENOTYPE_SIZE_BY_PARENT*2)) + MIN_GENOTYPE_SIZE_BY_PARENT;

            unsigned char mask_a = CROMO_MAX_VALUE - 1; // 255 -> 11111111
            mask_a <<= cut_position;

            unsigned char mask_b = CROMO_MAX_VALUE - 1; // 255 -> 11111111
            mask_b >>= NIBBLE_SIZE - cut_position;

            unsigned char kid = (pParent_a->getCromosoma() & mask_a) | (pParent_b->getCromosoma() & mask_b);

            individual *children = new individual((pParent_a->getCromosoma() & mask_a) | (pParent_b->getCromosoma() & mask_b));
            return children;
        }

        struct more_than_quantity
        {
            inline bool operator() ( Area* struct1,  Area* struct2)
            {
                return (struct1->GetNumberOfPoints() > struct2->GetNumberOfPoints());
            }
        };

    public:
        GeneticBase() {
            this->population = new vector<individual*>();
            this->fitnessPopulation = new vector<individual*>();
            this->unfitnessPopulation = new vector<individual*>();
            this->representation = new vector<cromodistribution*>();
            this->populationQuantity = 0;
            this->targetGenerations = 20;
        }

        GeneticBase(vector<Area*> pTable) {
            this->population = new vector<individual*>();
            this->fitnessPopulation = new vector<individual*>();
            this->unfitnessPopulation = new vector<individual*>();
            this->representation = new vector<cromodistribution*>();
            this->populationQuantity = 0;
            this->targetGenerations = 20;
            createCombinationTable(pTable, 23328);
            sortingTable(combinationTable);
        }

        void addDistribution(cromodistribution* pDistribution) {
            representation->push_back(pDistribution);
        }

        void initPopulation(int pAmountOfIndividuals) {
            population->clear();

            /*for(int i=0; i<pAmountOfIndividuals; i++) {
                individual* p = new individual((unsigned char) rand()%CROMO_MAX_VALUE);
                population->push_back(p);
            }*/

            for(int quantity=0; quantity<200; quantity++) {
                individual* newIndividual = new individual(rand()%65537); //Random number between 0 and 65536
                population->push_back(newIndividual);
            }
        }

        void produceGenerations(int ptargetGenerations, int pChildrensPerGenerations) {
            /*for(int i=0; i<ptargetGenerations; i++) {
                evaluateFitness();
                reproduce(pChildrensPerGenerations);
            }*/

            for(int i=0; i<50; i++) {
                evaluateFitness();
                reproduce(pChildrensPerGenerations);
            }
        }

        vector<individual*> getPopulation() {
            return *this->population;
        }

        void sortingTable(vector<Area*> &pTable){
            sort(pTable.begin(), pTable.end(), more_than_quantity());
        }

        void setCombinationTable(vector<Area*> pNewTable){
            combinationTable=pNewTable;
        }

        vector<Area*> getCombinationTable(){
            return combinationTable;
        }


        void createCombinationTable(vector<Area*> pTable, int pTotalPoints){
            Area *currentArea;
            int min=0, max=0;
            float density;
            string shape = "", size = "";
            for (int i = 0; i < pTable.size(); i++){
                currentArea = pTable.at(i);
                for (GrayColor current: currentArea->getVectorColors()){
                    if(current.appearances!=0){
                        max=min+(65536*(float)current.appearances/(float)pTotalPoints);
                        Area* newArea=new Area(currentArea->GetX1(),currentArea->GetY1(),currentArea->GetX2(),currentArea->GetY2(),current.appearances,
                                                (float)current.appearances/(float)pTotalPoints,current.value, min,max);
                        min=(min+65536*newArea->GetPercentage())+1;

                        density = ((float)current.appearances) / (120*SAMPLE_RATE);
                        shape = rand() % 2 == 0 ? "line" : "dot";
                        newArea->SetShape(shape);

                        if (shape == "line"){
                            if(density < 0.46){size = "S";}
                            else if (density < 0.6){size = "M";}
                            else{size = "L";}
                        }
                        else{
                            if(density < 0.46){size = "L";}
                            else if (density < 0.6){size = "M";}
                            else{size = "S";}
                        }
                        newArea->SetDensity(density);
                        newArea->SetSize(size);

                        combinationTable.push_back(newArea);
                    }
                }
            }
        }

};

#endif
