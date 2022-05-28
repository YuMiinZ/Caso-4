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

        void evaluateFitness(int pPopulationQuantity){
            float suma;
            vector<individual*> individuals;

            for(individual* currentIndividual: *population){
                for(individual* currentIndividualCompare: *population){
                    if(currentIndividual->getCromosoma()!=currentIndividualCompare->getCromosoma()){
                        suma+=(1/((sqrt(pow((currentIndividualCompare->getXValue()-currentIndividual->getXValue()),2)+pow((currentIndividualCompare->getYValue()-currentIndividual->getYValue()),2)))/10800));
                    }
                }
                currentIndividual->setFitnessValue(suma);

                individuals.push_back(currentIndividual);
                suma=0;
            }

            sortingPopulation(individuals);
            unsigned short fitnessParents = pPopulationQuantity*0.6;

            for (int i = 0; i < fitnessParents; i++){
                fitnessPopulation->push_back(individuals.at(i));
            }


        }

        void reproduce(unsigned short pAmountOfChildrens) {
            // previous population will be cleared, full saved, partial saved depending on the problem
            population->clear();

            for(unsigned short i=0; i<pAmountOfChildrens; i++) {
                // select any two fitness parents
                unsigned short parent_a_index = rand()%fitnessPopulation->size();
                individual* parent_a = fitnessPopulation->at(parent_a_index);

                unsigned short parent_b_index = rand()%fitnessPopulation->size();
                individual* parent_b = fitnessPopulation->at(parent_b_index);

                population->push_back(parent_a);
                population->push_back(parent_b);
            }
        }

        individual* cross(individual *pParent_a, individual *pParent_b) {
            // this operation will depends on: nibble size, fixed o variable point

            unsigned short cut_position = (rand() % (NIBBLE_SIZE-MIN_GENOTYPE_SIZE_BY_PARENT*2)) + MIN_GENOTYPE_SIZE_BY_PARENT;

            unsigned short mask_a = CROMO_MAX_VALUE - 1; // 255 -> 11111111
            mask_a <<= cut_position;

            unsigned short mask_b = CROMO_MAX_VALUE - 1; // 255 -> 11111111
            mask_b >>= NIBBLE_SIZE - cut_position;

            unsigned short kid = (pParent_a->getCromosoma() & mask_a) | (pParent_b->getCromosoma() & mask_b);

            individual *children = new individual((pParent_a->getCromosoma() & mask_a) | (pParent_b->getCromosoma() & mask_b));
            mutation(children);

            return children;
        }

        struct more_than_quantity
        {
            inline bool operator() ( Area* struct1,  Area* struct2)
            {
                return (struct1->GetNumberOfPoints() > struct2->GetNumberOfPoints());
            }
        };

        struct more_than_quantityPopulation
        {
            inline bool operator() ( individual* struct1,  individual* struct2)
            {
                return (struct1->getFitnessValue() > struct2->getFitnessValue());
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

        GeneticBase(vector<Area*> pTable, int pGeneratedPoints, short pPointsPerBox) {
            this->population = new vector<individual*>();
            this->fitnessPopulation = new vector<individual*>();
            this->unfitnessPopulation = new vector<individual*>();
            this->representation = new vector<cromodistribution*>();
            this->populationQuantity = 0;
            this->targetGenerations = 20;
            createCombinationTable(pTable, pGeneratedPoints, pPointsPerBox);
            //sortingTable(combinationTable);
        }

        void addDistribution(cromodistribution* pDistribution) {
            representation->push_back(pDistribution);
        }

        void initPopulation(int pAmountOfIndividuals) {
            population->clear();
            for(int quantity=0; quantity<pAmountOfIndividuals; quantity++) {
                individual* newIndividual = new individual(rand()%MAX_NUMBER); //Random number between 0 and MAX_NUMBER
                verifyRange(newIndividual);
                population->push_back(newIndividual);
            }

        }

        void produceGenerations(int ptargetGenerations, int pChildrensPerGenerations, socketclient pClient) {
            for(int i=0; i<ptargetGenerations; i++) {
                evaluateFitness(pChildrensPerGenerations);
                reproduce(pChildrensPerGenerations);
                pClient.clear();
                paintGeneration(pClient, *population, combinationTable);
            }
        }

        vector<individual*> getPopulation() {
            return *this->population;
        }

        void sortingTable(vector<Area*> &pTable){
            sort(pTable.begin(), pTable.end(), more_than_quantity());
        }
        void sortingPopulation(vector<individual*> &pPopulation){
            sort(pPopulation.begin(), pPopulation.end(), more_than_quantityPopulation());
        }

        void setCombinationTable(vector<Area*> pNewTable){
            combinationTable=pNewTable;
        }

        vector<Area*> getCombinationTable(){
            return combinationTable;
        }


        // void createCombinationTable(vector<Area*> pTable, int pTotalPoints){
        //     Area *currentArea;
        //     int min=0, max=0;
        //     float density;
        //     int maxOfArea, maxPivote, lastMin = 0;
        //     string shape = "", size = "";
        //     for (int i = 0; i < pTable.size(); i++){
        //         currentArea = pTable.at(i);
        //         maxOfArea = min + (MAX_NUMBER*((float)(720-currentArea->GetNumberOfPoints())/(float)pTotalPoints));
        //         maxPivote = maxOfArea / 11;
        //         //cout << "max area: " << maxOfArea << endl;
        //         for (GrayColor current: currentArea->getVectorColors()){
        //             if(true){
        //                 //max=min+(13925*(float)current.appearances/(float)pTotalPoints);
        //                 min = lastMin;
        //                 max= min+maxPivote;
        //                 Area* newArea=new Area(currentArea->GetX1(),currentArea->GetY1(),currentArea->GetX2(),currentArea->GetY2(),current.appearances,
        //                                         (float)current.appearances/(float)pTotalPoints,currentArea->GetGrayColorValue(), min,max);
        //                 //min = max + 1;
        //                 lastMin = max + 1;
        //                 // cout << "min: " << min << " ";
        //                 // cout << "max: " << max << endl;

        //                 density = ((float)current.appearances) / (120*SAMPLE_RATE);

            

        //                 shape = rand() % 2 == 0 ? "line" : "dot";
        //                 newArea->SetShape(shape);

        //                 if (shape == "line"){
        //                     if(density < 2){size = "S";}
        //                     else if (density < 10){size = "M";}
        //                     else{size = "L";}
        //                 }
        //                 else{
        //                     if(density < 2){size = "L";}
        //                     else if (density < 10){size = "M";}
        //                     else{size = "S";}
        //                 }
        //                 newArea->SetDensity(density);
        //                 newArea->SetSize(size);

        //                 combinationTable.push_back(newArea);

        //                 //cout << "Density: " << density << " Shape: " << shape << " Size: " << size << endl;
        //             }
        //         }
        //         min = 0;
        //     }
        // }

        void createCombinationTable(vector<Area*> pTable, int pTotalPoints, int pointsPerBox){
            Area *currentArea;
            int min=0, max=0;
            float density, distributionPercentage;
            int maxOfArea, maxPivote, lastMin = 0, pointsPerArea;
            string shape = "", size = "";
            for (int i = 0; i < pTable.size(); i++){
                currentArea = pTable.at(i);
                min = lastMin;
                pointsPerArea = pointsPerBox-currentArea->GetNumberOfPoints();
                distributionPercentage = (float)pointsPerArea/(float)pTotalPoints;
                max= min+ (MAX_NUMBER*distributionPercentage);
                Area* newArea=new Area(currentArea->GetX1(),currentArea->GetY1(),currentArea->GetX2(),currentArea->GetY2(),pointsPerArea,
                                        distributionPercentage,currentArea->GetGrayColorValue(), min,max);
                //min = max + 1;
                lastMin = max + 1;

                density = ((float)pointsPerArea) / (120*SAMPLE_RATE);
                shape = rand() % 2 == 0 ? "line" : "dot";
                newArea->SetShape(shape);

                if (shape == "line"){
                    if(density < 20){size = "S";}
                    else if (density < 21){size = "M";}
                    else{size = "L";}
                }
                else{
                    if(density < 20){size = "L";}
                    else if (density < 21){size = "M";}
                    else{size = "S";}
                }
                newArea->SetDensity(density);
                newArea->SetSize(size);

                combinationTable.push_back(newArea);
            }

        }

        void verifyRange(individual* &pNewIndividual){
            for(Area* currentArea:combinationTable){
                if(pNewIndividual->getCromosoma()>=currentArea->GetMinPercentage()&&pNewIndividual->getCromosoma()<=currentArea->GetMaxPercentage()){
                    pNewIndividual->setXValue((int)currentArea->GetX1()+rand()%abs((int)currentArea->GetX1()-(int)currentArea->GetX2()+1));
                    pNewIndividual->setYValue((int)currentArea->GetY1()+rand()%abs((int)currentArea->GetY1()-(int)currentArea->GetY2()+1));
                    break;
                }

            }
        }

        void mutation(individual* &currentIndividual){
        if(rand()%100<=6){
            unsigned short position=rand()%16;
            currentIndividual->setCromosoma(currentIndividual->getCromosoma() ^ (1<<position));
        }

    }

};

#endif
