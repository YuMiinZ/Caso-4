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
            /*
            Functioning: This method is responsible for evaluating all the new individuals generated and verifies their fitness, to then obtain a
             percentage of the most fit. Its fitness function consists in that for each individual its distance with all the others is verified
             and the one with more neighbors will be fitter, since its fitness value will be high, compared to an individual with few neighbors,
             the result of the calculations would be a low number.

            Input:
            -pPopulationQuantity

            Output: N/A
            */
            //fitnessPopulation->clear();
            float suma, raiz, fraccion;
            vector<individual*> individuals;

            for(individual* currentIndividual: *population){
                for(individual* currentIndividualCompare: *population){
                    if(currentIndividual->getCromosoma()!=currentIndividualCompare->getCromosoma()){
                        raiz = sqrt(pow((currentIndividualCompare->getXValue()-currentIndividual->getXValue()),2)+pow((currentIndividualCompare->getYValue()-currentIndividual->getYValue()),2));
                        fraccion = raiz / 10800;
                        if (fraccion != 0){
                            suma+=(1/fraccion);
                        }
                    }
                }
                currentIndividual->setFitnessValue(suma);

                individuals.push_back(currentIndividual);
                suma=0;
            }

            sortingPopulation(individuals);
            unsigned short int fitnessParents = pPopulationQuantity*0.5;

            for (int i = 0; i < fitnessParents; i++){
                fitnessPopulation->push_back(individuals.at(i));
            }
        }

        void reproduce(unsigned short pAmountOfChildrens) {
            /*
            Functioning: In this method, two parents will be chosen randomly from the fitness population and the cross between them will be made.
             in order to generate a new child from said crossing.

            Input:
            -pAmountOfChildrens = number of children to be generated.

            Output: N/A

            */
            // previous population will be cleared, full saved, partial saved depending on the problem

            population->clear();

            for(unsigned short i=0; i<pAmountOfChildrens; i++) {
                // select any two fitness parents
                unsigned short parent_a_index = rand()%fitnessPopulation->size();
                individual* parent_a = fitnessPopulation->at(parent_a_index);

                unsigned short parent_b_index = rand()%fitnessPopulation->size();
                individual* parent_b = fitnessPopulation->at(parent_b_index);

                population->push_back(cross(parent_a, parent_b));
            }
        }

        individual* cross(individual *pParent_a, individual *pParent_b) {
             /*
            Functioning: This function is responsible for crossing two fitness parents.

            Input:
            -*pParent_a
            -*pParent_b

            Output:
            children (individual*)

            */
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
             /*
            Functioning: It creates an initial population, for each random individual that it generates, it is sent to verify and thus generate its
             respective corresponding xy values of the range, to finally add them in the population.

            Input:
            -pAmountOfIndividuals

            Output: N/A
            */

            population->clear();
            unsigned short int random;
            for(int quantity=0; quantity<pAmountOfIndividuals; quantity++) {
                random = rand()%MAX_NUMBER + rand()%MAX_NUMBER;
                individual* newIndividual = new individual(random); //Random number between 0 and MAX_NUMBER
                verifyRange(newIndividual);
                population->push_back(newIndividual);
            }

        }

        void produceGenerations(int ptargetGenerations, int pChildrensPerGenerations, socketclient pClient) {
             /*
            Functioning: Method responsible for generating the generations.

            Input:
            -ptargetGenerations
            -pChildrensPerGenerations
            -pClient

            Output: N/A

            */

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
             /*
            Functioning: Creation of the combination table that is used as a reference.

            Input:
            -pTable
            -pTotalPoints
            -pointsPerBox

            Output: N/A

            */
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
                shape = rand() % 3 == 0 ? "line" : "dot";
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
            /*
            Functioning: It verifies to which rank the new individual belongs in order to generate its respective xy value.

            Input:
            -&pNewIndividual

            Output: N/A
            */
            for(Area* currentArea:combinationTable){
                if(pNewIndividual->getCromosoma()>=currentArea->GetMinPercentage()&&pNewIndividual->getCromosoma()<=currentArea->GetMaxPercentage()){
                    pNewIndividual->setXValue((int)currentArea->GetX1()+rand()%abs((int)currentArea->GetX1()-(int)currentArea->GetX2()+1));
                    pNewIndividual->setYValue((int)currentArea->GetY1()+rand()%abs((int)currentArea->GetY1()-(int)currentArea->GetY2()+1));
                    break;
                }

            }
        }

        void mutation(individual* &currentIndividual){
            /*
            Functioning: In this function, it is used with a random if the individual will have a mutation or not.
            If the individual is going to have a mutation, a position will be chosen randomly and that bit will be inverted.

            Input:
            -&currentIndividual

            Output: N/A
            */
            if(rand()%100<=6){
                unsigned short position=rand()%16;
                currentIndividual->setCromosoma(currentIndividual->getCromosoma() ^ (1<<position));
            }
        }

};

#endif
