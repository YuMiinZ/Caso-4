// #define IP_ADDRESS "192.168.0.6"
// #define PORT 4000
// #define SAMPLE_RATE 0.2
// #define DISTRIBUTION_SIZE 3
// #define MAX_NUMBER 65536
// #define STB_IMAGE_IMPLEMENTATION

// #pragma comment(lib, "ws2_l2.lib")
// #include <Ws2tcpip.h>
// #include <iostream>
// #include <stdlib.h>
// #include <Windows.h>

// #include <vector>
// #include <math.h>
// #include <cmath>
// #include "socket.hpp"
// #include "GrayColor.hpp"
// #include "Area.hpp"
// #include "functions.hpp"
// #include "stb_image.h"
// #include "GeneticBase.hpp"

// //#include <unistd.h>



// using namespace std;

// int main(int argc, char const *argv[])
// {

//     int boxes = 0, totalPoints = 777600*SAMPLE_RATE,
//     pointsPerBox = totalPoints / 216, populationQuantity = 200;
//     float percentage = (float)pointsPerBox/(float)totalPoints;

//     vector<Area*> table;

//     //Now we load the image

//     int width, height, channels;
//     unsigned char *image = stbi_load("images/1.jpg", &width, &height, &channels, 0);
//     size_t imageSize = width * height * channels;
//     int area = width * height;
//     if(image!=NULL) {
//         cout << "Image loaded successfully" << endl;
//         cout << "Width: " << width << endl;
//         cout << "Height: " << height << endl;
//         cout << "Channels: " << channels << endl;
//         cout << "Image size: " << imageSize << endl;
//     } else {
//         cout << "Image not loaded" << endl;
//     }

//     //First we fill the dynamic table we'll need for the
//     //probabilistic algorithm and initialize the table of the areas of the image
//     //with their equiprobable percentages
//     fillTable(boxes, percentage, table);


//     //Next we start the analysis of the image using random numbers
//     //and adjusting the table we previously created.
//     startAnalysis(percentage, totalPoints, table, width, boxes, image);
//     cout << table.size() << endl;

//     //Then we set the size and shape corresponding to each area
//     //according to the density. The density is related to the amount
//     //of points generated in each area.
//     setAttributes(boxes, pointsPerBox, table);

//     cout << "Iniciando genetico" << endl;
//     socketclient client;
//     client.init();
//     client.clear();

//     GeneticBase* genetic=new GeneticBase(table);
//     genetic->initPopulation(populationQuantity);
//     genetic->produceGenerations(50, populationQuantity, client);

//     vector<individual*> population = genetic->getPopulation();
//     vector<Area*> cromosomaticRepresentation = genetic->getCombinationTable();

    
    

    

//     client.closeConnection();

//     return 0;
// }
