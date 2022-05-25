#ifndef __AREA_HEADER__
#define __AREA_HEADER__

//  #include <std::vector>
//  #include <string.h>

using namespace std;

/**
 * @brief class Area
 *
 */
class Area{
    private:
        int x1;
        int y1;
        int x2;
        int y2;
        int density;
        int numberOfPoints;
        int GrayColorValue = 255;
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

<<<<<<< HEAD
        vector<GrayColor> getVectorColors(){
            return colors;
=======
        std::vector<GrayColor> GetColors() const {
                return colors;
        }

        void SetColors(std::vector<GrayColor> colors) {
                colors = colors;
>>>>>>> 736f06608ddf1e893b5d6f08a660862ce3bc100c
        }

        /**
         * @brief adds the color to the vector of colors or counts the appearances
         *        of that color if it already exits in the vector.
         *
         * @param pNewColor
         */
        void addColor(GrayColor pNewColor){
                // for (GrayColor current: colors){
                //         if(current.value == pNewColor.value){
                //                 current.appearances += 1;
                //                 return;
                //         }
                // }
                colors.push_back(pNewColor);
        }

        /**
         * @brief substracts 1 from the number of points the area has left.
         *
         * @return true
         * @return false
         */
        bool substract(){
                if (numberOfPoints <= 0){
                        return true;
                }
                numberOfPoints--;
                return false;
        }

        /**
         * @brief adjusts the percentages of the areas when a new point is found.
         *
         * @param pTotalPoints
         * @param pLastMin
         */
        void adjustPercentages(int pTotalPoints, float pLastMin){
                //std::cout << "current: " << minPercentage << " " << maxPercentage << std::endl;
                //std::cout << pTotalPoints << " " << numberOfPoints << std::endl;
                minPercentage = pLastMin;
                maxPercentage = minPercentage + ((float)numberOfPoints / (float)pTotalPoints);
                //std::cout << "ADJUST: " << minPercentage << " " << maxPercentage << std::endl;
        }

        /**
         * @brief Set the Dominant Gray color of the area
         *
         */
        void setDominantGray(){
               GrayColor dominant = colors.at(0);
<<<<<<< HEAD
               for (GrayColor current: colors){
                        if(current.appearances > dominant.appearances){
                                dominant = current;
                        }
                }
                GrayColorValue = dominant.value;
=======
               vector<GrayColor> newColorsVector(11);
               _initColorVector(newColorsVector);
               int newColor;
                for (GrayColor current: colors){
                        // if(current.appearances > dominant.appearances){ //determines dominant rgb gray color
                        //         dominant = current;
                        // }
                        //gets the gray category based on the gray intesity. if it approaches 255 the value approaches 10
                        //if it approaches 0 the value approaches 0
                        newColor = round(current.value * 10 / 255);
                        newColorsVector[newColor].appearances += 1; //increases the appereances to know how many points of that category exist

                }
                colors = newColorsVector;
                // GrayColorValue = dominant.value;
>>>>>>> 736f06608ddf1e893b5d6f08a660862ce3bc100c
        }
};



#endif
