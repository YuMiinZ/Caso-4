#ifndef __GRAYCOLOR_HEADER__
#define __GRAYCOLOR_HEADER__

/**
 * @brief struct for each gray color
 * 
 */
struct GrayColor{
    int value;
    int appearances;
};

void _initColorVector(std::vector<GrayColor> &vector){
    for (int i = 0; i < 11; i++){
        vector[i].value = i;
    }
}

#endif