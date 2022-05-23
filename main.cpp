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
    int x, y, indexArea, generatedPoints = 0, acceptablePointsValue = totalPoints*0.7, grayValue;
    float random, min, max;
    Area *currentArea;
    GrayColor newGrayColor;
    while(generatedPoints != acceptablePointsValue){
        random = 0 + (float)(rand()) / ((float)(RAND_MAX/(1 - 0)));

        indexArea = random / percentage; // SE NECESITA ALGUNA FORMULA PARA NO RECORRER TODO EL VECTOR, ESTA NO SIRVE
        //if (indexArea > 215){indexArea = 215;}
        cout << (float)random << "-"; cout << indexArea << endl;
        currentArea = table.at(indexArea);
        cout << "parada 1" << endl;
        min = currentArea->GetMinPercentage();
        max = currentArea->GetMaxPercentage();
        cout << "parada 2" << endl;
        while (min > random || max < random){ //se cicla
            indexArea = 0;
            currentArea = table.at(++indexArea);
            min = currentArea->GetMinPercentage();
            max = currentArea->GetMaxPercentage();
        }

        x = currentArea->GetX1() + (rand() % 60);
        y = currentArea->GetY1() + (rand() % 60);

        size_t index = RGB * (y * width + x);
        int red = image[index];
        int green = image[index + 1];
        int blue = image[index + 2];
        newGrayColor.value = getGrayscaleValue(red, green, blue);
        //quadrant->verifyRange(red, green, blue);
        currentArea->addColor(newGrayColor);
        currentArea->substract();
        currentArea->SetPercentage((float)currentArea->GetNumberOfPoints() / (float)totalPoints);
        currentArea->adjustPercentages(totalPoints, min);

        //adjust all the percentages
        for (int i = indexArea; i < boxes; i++){
            table.at(indexArea + 1)->adjustPercentages(totalPoints, currentArea->GetMaxPercentage());
        }

        generatedPoints++;
        indexArea++;
    }

    cout << generatedPoints << endl;
    cout << "2" << endl;

    float density;
    string shape = "", size = "";
    for (Area *current: table){
        density = (pointsPerBox - current->GetNumberOfPoints()) / (3600*SAMPLE_RATE);
        shape = density < 0.6 ? "line" : "dot";
        cout << shape << endl;
        current->SetShape(shape);
        if (shape == "line"){
            if(density < 0.2){size = "S";}
            else if (density < 0.6){size = "M";}
            else{size = "L";}
        }
        else{
            if(density < 0.2){size = "L";}
            else if (density < 0.6){size = "M";}
            else{size = "S";}
        }
        current->SetSize(size);
        cout << current->GetSize() << endl;
        current->setDominantGray();

        //cout << "done" << endl;

        cout << current->GetX1() << endl;
        cout << current->GetY1() << endl;
        cout << current->GetX2() << endl;
        cout << current->GetY2() << endl;
        cout << current->GetGrayColorValue()<< endl;
        cout << current->GetShape() << endl;
        cout << current->GetSize() << endl;
    }

}
