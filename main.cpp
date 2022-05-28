#define IP_ADDRESS "192.168.0.6"
#define PORT 4000
#define SAMPLE_RATE 0.2
#define DISTRIBUTION_SIZE 3
#define MAX_NUMBER 65536
#define STB_IMAGE_IMPLEMENTATION

#pragma comment(lib, "ws2_l2.lib")
#include <Ws2tcpip.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

#include <vector> 
#include <math.h>
#include <cmath>
#include <time.h> 
#include "socket.hpp"
#include "GrayColor.hpp"
#include "Area.hpp"
#include "functions.hpp"
#include "stb_image.h"
#include "GeneticBase.hpp"

int main(int argc, char const *argv[])
{
    srand(time(0)); 

    int boxes = 0, totalPoints = 777600*SAMPLE_RATE,
    pointsPerBox = totalPoints / 216, populationQuantity = 500,
    generatedPoints = 0;
    float percentage = (float)pointsPerBox/(float)totalPoints;

    vector<Area*> table;

    //Now we load the image

    int width, height, channels;
    unsigned char *image = stbi_load("images/2.jpg", &width, &height, &channels, 0);
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

    //First we fill the dynamic table we'll need for the
    //probabilistic algorithm and initialize the table of the areas of the image
    //with their equiprobable percentages
    fillTable(boxes, percentage, table);


    //Next we start the analysis of the image using random numbers
    //and adjusting the table we previously created.
    generatedPoints = startAnalysis(percentage, totalPoints, table, width, boxes, image);
    cout << table.size() << endl;

    //Then we set the size and shape corresponding to each area
    //according to the density. The density is related to the amount
    //of points generated in each area.
    setAttributes(boxes, pointsPerBox, table);

    //initiating the server
    socketclient client;
    client.init();
    client.clear();

    //Then we start the second part of the program, which is the genetic algorithm
    //that's going to paint generation after generation.

    //This constructor builds the cromosomatic representation
    GeneticBase* genetic=new GeneticBase(table, generatedPoints ,pointsPerBox);

    //We initiate the population
    genetic->initPopulation(populationQuantity); 

    //Then we produce the generations
    genetic->produceGenerations(50, populationQuantity, client);
 
    /*vector<Area*> tabla=genetic->getCombinationTable(); 
    cout<<"Tabla de combinaciones"<<endl; 
    for(Area* currentArea:tabla){  
        std::cout << currentArea->GetX1() << " ";  
        std::cout << currentArea->GetY1() << " "; 
        std::cout << currentArea->GetX2() << " ";
        std::cout << currentArea->GetY2() << " "; 
        std::cout << currentArea->GetMinPercentage() << " ";
        std::cout << currentArea->GetMaxPercentage() << " \n";
        // std::cout << currentArea->GetNumberOfPoints()<< " ";
        //std::cout << currentArea->GetGrayColorValue()<< " ";
        //std::cout << currentArea->GetDensity()<< " ";
        //std::cout << currentArea->getVectorColors().size()<< " ";
        //std::cout << currentArea->GetShape() << "\n"; 
        //std::cout << currentArea->GetSize() << std::endl;
    }*/
 
    //Finally, we close the connection to the server
    client.closeConnection();

    delete genetic;

    return 0;
}
