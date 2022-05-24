/*
    Caso 4

    Elaborado por Ericka Yu Min Guo y Fiorella Zelaya Coto
    
*/
#define SAMPLE_RATE 0.2
#define DISTRIBUTION_SIZE 3
#define MAX_NUMBER 65536
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <vector>
#include <math.h>
//#include <string.h>
#include "Area.hpp"
#include "functions.hpp"
//#include "Point.hpp"
// #include <bits/stdc++.h>
#include "stb_image.h"
// #include "quadrant.hpp"


using namespace std;

int main(){
    
    //First we fill the dynamic table we'll need for the
    //probabilistic algorithm

    int x1 = 180, x2 = 240, y1 = 0, y2 = 60, boxes = 0, totalPoints = 777600*SAMPLE_RATE,
    pointsPerBox = totalPoints / 216;
    float percentage = (float)pointsPerBox/(float)totalPoints, dynamicPercentage = 0;
    Area *newArea;
    vector<Area*> table;

    //Now we load the image

    int width, height, channels;
    unsigned char *image = stbi_load("images/1.jpg", &width, &height, &channels, 0);
    size_t imageSize = width * height * channels;
    int area = width * height;
    if(image!=NULL) { 
        cout << "Image loaded successfully" << endl;
        cout << "Width: " << width << endl;
        cout << "Height: " << height << endl;
        cout << "Channels: " << channels << endl;
        cout << "Image size: " << imageSize << endl;
    } else {
        cout << "Image not loaded" << endl;
    }
    const size_t RGB = 3;

    //Next we initialize the table of the areas of the image
    //with their equiprobable percentages

    while (boxes != 216){
        if (x2 > 900){
            x1 = 180; 
            x2 = 240;
            y1 = y2;
            y2 += 60;
        }
        newArea = new Area(x1, y1, x2, y2, 720, percentage);
        newArea->SetMinPercentage(dynamicPercentage); newArea->SetDynamicMinPercentage(dynamicPercentage);
        newArea->SetMaxPercentage(dynamicPercentage + percentage); newArea->SetDynamicMaxPercentage(dynamicPercentage + percentage);
        //cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << (float)percentage << " " << (float)dynamicPercentage << " "  << (float)dynamicPercentage + percentage << endl;  
        dynamicPercentage += percentage;
        table.push_back(newArea);
        x1 = x2;
        x2 += 60;
        boxes++;
    }

    cout << "1" << endl;
    //Next we start the analysis of the image using random numbers
    //and adjusting the table we previously created. 
    int x, y, indexArea, generatedPoints = 0, acceptablePointsValue = totalPoints*0.7, grayValue, isEmpty;
    float random, min, max;
    Area *currentArea;
    GrayColor newGrayColor;
    while(generatedPoints != acceptablePointsValue){
        //cout << "0 Y 1: " << table.at(215)->GetMinPercentage() << " " << table.at(215)->GetMaxPercentage() << endl;
        //cout << "0 Y 1: " << table.at(1)->GetMinPercentage() << " " << table.at(0)->GetMaxPercentage() << endl;
        random = 0 + (float)(rand()) / ((float)(RAND_MAX/(1 - 0)));

        indexArea = random / percentage; // SE NECESITA ALGUNA FORMULA PARA NO RECORRER TODO EL VECTOR, ESTA NO SIRVE
        if (indexArea > 215){indexArea = 215;}
        //cout << (float)random << "-"; cout << indexArea << endl;
        currentArea = table.at(indexArea);
        //if (currentArea->GetNumberOfPoints() <= 0){continue;}
        //cout << "parada 1" << endl;
        min = currentArea->GetMinPercentage();
        max = currentArea->GetMaxPercentage();
        //cout << "parada 2 " << random << " "<< indexArea << endl;
        while ((min > random || max < random) && indexArea < boxes){
            
            currentArea = table.at(indexArea);
            //cout << "ciclo: " << min << " " << max << " " << indexArea << endl;
            min = currentArea->GetMinPercentage();
            max = currentArea->GetMaxPercentage();
            indexArea++;
            
        }
        isEmpty = currentArea->substract(); 
        if(isEmpty){continue;}

        x = currentArea->GetX1() + (rand() % 60);
        y = currentArea->GetY1() + (rand() % 60);

        size_t index = RGB * (y * width + x);
        int red = image[index];
        int green = image[index + 1];
        int blue = image[index + 2];
        newGrayColor.value = getGrayscaleValue(red, green, blue);
        //quadrant->verifyRange(red, green, blue);
        currentArea->addColor(newGrayColor);
        currentArea->SetPercentage((float)currentArea->GetNumberOfPoints() / (float)totalPoints);
        currentArea->SetMinPercentage(min);
        currentArea->SetMaxPercentage(min + ((float)currentArea->GetNumberOfPoints() / (float)totalPoints));

        //adjust all the percentages
        for (int i = indexArea; i < boxes-1; i++){
            //cout << "In: " << currentArea->GetMaxPercentage() << endl;
            //cout << i + 1 << " ";
            table.at(indexArea + 1)->adjustPercentages(totalPoints, table.at(indexArea)->GetMaxPercentage());
        }

        generatedPoints++;
        
    }

    cout << generatedPoints << endl;
    cout << table.size() << endl;

    float density;
    string shape = "", size = "";
    for (int i = 0; i < boxes; i++){
        currentArea = table.at(i);
        density = ((float)pointsPerBox - (float)currentArea->GetNumberOfPoints()) / (3600*SAMPLE_RATE);
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
        cout << currentArea->GetX1() << " ";
        cout << currentArea->GetY1() << " ";
        cout << currentArea->GetX2() << " ";
        cout << currentArea->GetY2() << " ";
        cout << currentArea->GetMinPercentage() << " ";
        cout << currentArea->GetMaxPercentage() << " ";
        cout << currentArea->GetNumberOfPoints()<< " ";
        cout << currentArea->GetGrayColorValue()<< " ";
        cout << currentArea->GetShape() << " ";
        cout << currentArea->GetSize() << endl;
    }

}
