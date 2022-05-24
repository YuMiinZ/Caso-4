#ifndef __FUNCTIONS_HEADER__
#define __FUNCTIONS_HEADER__

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
        if (x2 > 900){
            x1 = 180; 
            x2 = 240;
            y1 = y2;
            y2 += 60;
        }
        newArea = new Area(x1, y1, x2, y2, 720, pPercentage);
        newArea->SetMinPercentage(dynamicPercentage); newArea->SetDynamicMinPercentage(dynamicPercentage);
        newArea->SetMaxPercentage(dynamicPercentage + pPercentage); newArea->SetDynamicMaxPercentage(dynamicPercentage + pPercentage);
        //cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << (float)pPercentage << " " << (float)dynamicPercentage << " "  << (float)dynamicPercentage + pPercentage << endl;  
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
void startAnalysis(float pPercentage, int pTotalPoints, std::vector<Area*> &pTable, int pWidth, int pBoxes, unsigned char *pImage){
    int x, y, indexArea, generatedPoints = 0, acceptablePointsValue = pTotalPoints*0.7, grayValue, isEmpty;
    float random, min, max;
    Area *currentArea;
    GrayColor newGrayColor;
    const size_t RGB = 3;
    while(generatedPoints != acceptablePointsValue){
        random = 0 + (float)(rand()) / ((float)(RAND_MAX/(1 - 0)));

        indexArea = random / pPercentage; // SE NECESITA ALGUNA FORMULA PARA NO RECORRER TODO EL std::vector, ESTA NO SIRVE
        if (indexArea > 215){indexArea = 215;}
        currentArea = pTable.at(indexArea);
        min = currentArea->GetMinPercentage();
        max = currentArea->GetMaxPercentage();
        while ((min > random || max < random) && indexArea < pBoxes){
            currentArea = pTable.at(indexArea);
            min = currentArea->GetMinPercentage();
            max = currentArea->GetMaxPercentage();
            indexArea++;
            
        }
        isEmpty = currentArea->substract(); 
        if(isEmpty){continue;}

        x = currentArea->GetX1() + (rand() % 60);
        y = currentArea->GetY1() + (rand() % 60);

        size_t index = RGB * (y * pWidth + x);
        int red = pImage[index];
        int green = pImage[index + 1];
        int blue = pImage[index + 2];
        newGrayColor.value = getGrayscaleValue(red, green, blue);
        currentArea->addColor(newGrayColor);
        currentArea->SetPercentage((float)currentArea->GetNumberOfPoints() / (float)pTotalPoints);
        currentArea->SetMinPercentage(min);
        currentArea->SetMaxPercentage(min + ((float)currentArea->GetNumberOfPoints() / (float)pTotalPoints));

        //adjust all the percentages
        for (int i = indexArea; i < pBoxes-1; i++){
            pTable.at(indexArea + 1)->adjustPercentages(pTotalPoints, pTable.at(indexArea)->GetMaxPercentage());
        }

        generatedPoints++;
        
    }
    cout << generatedPoints << endl;
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
    string shape = "", size = "";
    cout << pBoxes << endl;
    for (int i = 0; i < pBoxes; i++){
        currentArea = pTable.at(i);
        density = ((float)pPointsPerBox - (float)currentArea->GetNumberOfPoints()) / (3600*SAMPLE_RATE);
        shape = rand() % 2 == 0 ? "line" : "dot";
        currentArea->SetShape(shape);
        if (shape == "line"){
            if(density < 0.46){size = "S";}
            else if (density < 0.53){size = "M";}
            else{size = "L";}
        }
        else{
            if(density < 0.46){size = "L";}
            else if (density < 0.53){size = "M";}
            else{size = "S";}
        }
        currentArea->SetSize(size);
        currentArea->setDominantGray();

        cout << i << ". ";
        //cout << density << " ";
        std::cout << currentArea->GetX1() << " ";
        std::cout << currentArea->GetY1() << " ";
        std::cout << currentArea->GetX2() << " ";
        std::cout << currentArea->GetY2() << " ";
        std::cout << currentArea->GetMinPercentage() << " ";
        std::cout << currentArea->GetMaxPercentage() << " ";
        std::cout << currentArea->GetNumberOfPoints()<< " ";
        std::cout << currentArea->GetGrayColorValue()<< " ";
        std::cout << currentArea->GetShape() << " ";
        std::cout << currentArea->GetSize() << std::endl;
    }
}



#endif