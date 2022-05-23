#ifndef __FUNCTIONS_HEADER__
#define __FUNCTIONS_HEADER__

struct GrayColor{
    int value;
    int appearances;
};

void fillTable(){

}

void generatePoints(){}

float getGrayscaleValue(int red, int blue, int green){
    return (0.299 * red) + (0.587 * green) + (0.114 * blue);
}

#endif