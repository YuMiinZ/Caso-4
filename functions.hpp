#ifndef __FUNCTIONS_HEADER__
#define __FUNCTIONS_HEADER__
#include "lib/individual.h"

using namespace std;

/**
 * @brief Get the Grayscale Value of a color with the RGB values
 *
 * @param red
 * @param blue
 * @param green
 * @return float gray value
 */
float getGrayscaleValue(int red, int blue, int green){
    return (0.299 * red) + (0.587 * green) + (0.114 * blue);
}

/**
 * @brief fills the table with the 216 areas needed.
 *        this function sets the coordinates of the area's range
 *
 * @param pBoxes
 * @param pPercentage
 * @param pTable
 */
void fillTable(int &pBoxes, float pPercentage, std::vector<Area*> &pTable){
    int x1 = 180, x2 = 240, y1 = 0, y2 = 60;
    Area *newArea;
    float dynamicPercentage = 0;
    while (pBoxes != 216){
        if (x2 > 900){ //if it reaches a limit
            x1 = 180;
            x2 = 240;
            y1 = y2;
            y2 += 60;
        }

        //creates new area
        newArea = new Area(x1, y1, x2, y2, 720, pPercentage);
        newArea->SetMinPercentage(dynamicPercentage); newArea->SetDynamicMinPercentage(dynamicPercentage);
        newArea->SetMaxPercentage(dynamicPercentage + pPercentage); newArea->SetDynamicMaxPercentage(dynamicPercentage + pPercentage);
        dynamicPercentage += pPercentage;
        pTable.push_back(newArea);

        x1 = x2;
        x2 += 60;
        pBoxes++;
    }

}

/**
 * @brief starts the analysis of the image. this function uses a probabilistic
 *        algorithm, which generates random (x,y) points following a dynamic
 *        statistics.
 *
 * @param pPercentage
 * @param pTotalPoints
 * @param pTable
 * @param pWidth
 * @param pBoxes
 * @param pImage
 */
int startAnalysis(float pPercentage, int pTotalPoints, std::vector<Area*> &pTable, int pWidth, int pBoxes, unsigned char *pImage){
    int x, y, indexArea, generatedPoints = 0, acceptablePointsValue = pTotalPoints*0.7, grayValue, isEmpty;
    float random, min, max;
    Area *currentArea;
    GrayColor newGrayColor;
    const size_t RGB = 3;
    while(generatedPoints != acceptablePointsValue){
        random = 0 + (float)(rand()) / ((float)(RAND_MAX/(1 - 0)));

        //gets the approximate index of the area based on the random
        indexArea = random / pPercentage; // SE NECESITA ALGUNA FORMULA PARA NO RECORRER TODO EL std::vector, ESTA NO SIRVE
        if (indexArea > 215){continue;} //if it's out of range

        //sets the current area
        currentArea = pTable.at(indexArea);
        min = currentArea->GetMinPercentage();
        max = currentArea->GetMaxPercentage();

        //validates that the current area is the one that matches with the random, if not, it looks for the
        //area that does
        while ((min > random || max < random) && indexArea < pBoxes){ //recorre con el pivot para encontrar el % adecuado
            currentArea = pTable.at(indexArea);
            min = currentArea->GetMinPercentage();
            max = currentArea->GetMaxPercentage();
            indexArea++;

        }

        //if the current area has 0 elements left it tries again (shouldn't happen)
        isEmpty = currentArea->substract();
        if(isEmpty){continue;}

        //gets randoms (x,y)
        x = currentArea->GetX1() + (rand() % 60);
        y = currentArea->GetY1() + (rand() % 60);

        //gets the rgb color and converts it into gray rgb
        size_t index = RGB * (y * pWidth + x);
        int red = pImage[index];
        int green = pImage[index + 1];
        int blue = pImage[index + 2];
        newGrayColor.value = getGrayscaleValue(red, green, blue);
        currentArea->addColor(newGrayColor);

        //adjust the percentage of the current area
        currentArea->SetPercentage((float)currentArea->GetNumberOfPoints() / (float)pTotalPoints);
        currentArea->SetMinPercentage(min);
        currentArea->SetMaxPercentage(min + ((float)currentArea->GetNumberOfPoints() / (float)pTotalPoints));

        //adjust all the percentages
        for (int i = indexArea; i < pBoxes-1; i++){
            pTable.at(indexArea + 1)->adjustPercentages(pTotalPoints, pTable.at(indexArea)->GetMaxPercentage());
        }

        generatedPoints++;

    }

    return generatedPoints;
}

/**
 * @brief Set the Attributes such as size and shape of each area based on
 *        a calculation of the density of the area, that is, the amount of
 *        points that certain area has.
 *
 * @param pBoxes
 * @param pPointsPerBox
 * @param pTable
 */
void setAttributes(int pBoxes, int pPointsPerBox, std::vector<Area*> &pTable){
    float density;
    Area *currentArea;

    for (int i = 0; i < pBoxes; i++){
        currentArea = pTable.at(i);
        currentArea->setDominantGray();

        /*std::cout << "\n" << i << ". ";
        //cout << density << " ";
        std::cout << currentArea->GetX1() << " ";
        std::cout << currentArea->GetY1() << " ";
        std::cout << currentArea->GetX2() << " ";
        std::cout << currentArea->GetY2() << " ";
        std::cout << currentArea->GetMinPercentage() << " ";
        std::cout << currentArea->GetMaxPercentage() << " ";
        std::cout << currentArea->GetNumberOfPoints()<< " ";
        std::cout << currentArea->GetGrayColorValue()<< " ";
        //std::cout << currentArea->GetShape() << " ";
        //std::cout << currentArea->GetSize() << std::endl;*/
    }
}

int randomNumberBetween(int pMin, int pMax){
        return pMin + (rand() % (pMax-pMin));
}

void paintGeneration(socketclient client, vector<individual*> population, vector<Area*> cromosomaticRepresentation){
    int grayValue, x1, y1, x2, y2, radius;
    for(individual* current: population){
        for(Area* currentArea: cromosomaticRepresentation){
            if (currentArea->GetMinPercentage() < current->getCromosoma() && currentArea->GetMaxPercentage() > current->getCromosoma()){
                //grayValue = (currentArea->GetGrayColorValue()*255 / 11);
                grayValue = currentArea->GetGrayColorValue();
                x1 = randomNumberBetween(currentArea->GetX1(), currentArea->GetX2());
                y1 = randomNumberBetween(currentArea->GetY1(), currentArea->GetY2());

                if (currentArea->GetShape() == "line"){
                    if (currentArea->GetSize() == "S"){
                        x2 = x1 + 10;
                        y2 = y1 + 10;
                    }
                    else if (currentArea->GetShape() == "M"){
                        x2 = x1 + 10;
                        y2 = y1 + 10;
                    }
                    else{
                        x2 = x1 + 10;
                        y2 = y1 + 10;
                    }
                    client.paintLine(grayValue, grayValue, grayValue, 255, x1, y1, x2, y2);
                }
                else{
                    if (currentArea->GetSize() == "S"){
                        radius = 5;
                    }
                    else if (currentArea->GetShape() == "M"){
                        radius = 5;
                    }
                    else{
                        radius = 5;
                    }
                    client.paintDot(grayValue, grayValue, grayValue, 255, x1, y1, radius);
                }
                break;
            }
        }
    }
}



#endif
