#ifndef __AREA_HEADER__
#define __AREA_HEADER__

//  #include <std::vector>
//  #include <string.h>
#include "functions.hpp"

class Area{
    private:
        int x1;
        int y1;
        int x2;
        int y2;
        int density;
        int numberOfPoints;
        int GrayColorValue;
        float percentage;
        float minPercentage;
        float maxPercentage;     
        float dynamicMinPercentage;
        float dynamicMaxPercentage; 
        std::string shape;
        std::string size;
        std::vector<GrayColor> colors;
        
    public:
        Area() = default;
        Area(int pNewX1, int pNewY1, int pNewX2, int pNewY2, int pNewNumberOfPoints, int pNewPercentage){
            x1 = pNewX1; y1 = pNewY1; x2 = pNewX2; y2 = pNewY2;
            numberOfPoints = pNewNumberOfPoints;
            percentage = pNewPercentage;
            minPercentage = 0;
            maxPercentage = 0;
        }
        int GetX1() const {
                return x1;
        }

        void SetX1(int pX1) {
                x1 = pX1;
        }

        int GetY1() const {
                return y1;
        }

        void SetY1(int pY1) {
                y1 = pY1;
        }

        int GetX2() const {
                return x2;
        }

        void SetX2(int pX2) {
                x2 = pX2;
        }

        int GetY2() const {
                return y2;
        }

        void SetY2(int pY2) {
                y2 = pY2;
        }

        int GetNumberOfPoints() const {
                return numberOfPoints;
        }

        void SetNumberOfPoints(int pNumberOfPoints) {
                numberOfPoints = pNumberOfPoints;
        }

        int GetPercentage() const {
                return percentage;
        }

        void SetPercentage(int pPercentage) {
                percentage = pPercentage;
        }

        float GetMinPercentage() const {
        return minPercentage;
        }

        void SetMinPercentage(float pMinPercentage) {
                minPercentage = pMinPercentage;
        }

        float GetMaxPercentage() const {
                return maxPercentage;
        }

        void SetMaxPercentage(float pMaxPercentage) {
                maxPercentage = pMaxPercentage;
        }

        float GetDynamicMinPercentage() const {
                return dynamicMinPercentage;
        }

        void SetDynamicMinPercentage(float pDynamicMinPercentage) {
                dynamicMinPercentage = pDynamicMinPercentage;
        }

        float GetDynamicMaxPercentage() const {
                return dynamicMaxPercentage;
        }

        void SetDynamicMaxPercentage(float pDynamicMaxPercentage) {
                dynamicMaxPercentage = pDynamicMaxPercentage;
        }

        std::string GetShape() const {
                return shape;
        }

        void SetShape(std::string pShape) {
                shape = pShape;
        }

        std::string GetSize() const {
                return size;
        }

        void SetSize(std::string pSize) {
                size = pSize;
        }
  
        int GetDensity() const {
                return density;
        }

        void SetDensity(int pDensity) {
                density = pDensity;
        } 

        int GetGrayColorValue() const {
                return GrayColorValue;
        }

        void SetGrayColorValue(int pGrayColorValue) {
                GrayColorValue = pGrayColorValue;
        }

        void addColor(GrayColor pNewColor){
                for (GrayColor current: colors){
                        if(current.value == pNewColor.value){
                                current.appearances += 1;
                                return;
                        }
                }
                colors.push_back(pNewColor);
        }

        void substract(){
                numberOfPoints--;
        }

        void adjustPercentages(int pTotalPoints, float pLastMin){
                minPercentage += pLastMin;
                maxPercentage = minPercentage + (numberOfPoints / pTotalPoints);
        }

        void setDominantGray(){
                int dominant = colors.at(0).value;
               for (GrayColor current: colors){
                        if(current.value > dominant){
                                dominant = current.value;
                        }
                } 
                GrayColorValue = dominant;
        }
};



#endif