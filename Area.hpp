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
        float density;
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
        Area(int pNewX1, int pNewY1, int pNewX2, int pNewY2, int pNewNumberOfPoints, float pNewPercentage){
            x1 = pNewX1; y1 = pNewY1; x2 = pNewX2; y2 = pNewY2;
            numberOfPoints = pNewNumberOfPoints;
            percentage = pNewPercentage;
            minPercentage = 0;
            maxPercentage = 0;
        }
        Area(int pNewX1, int pNewY1, int pNewX2, int pNewY2, int pNewNumberOfPoints, float pNewPercentage, int pNewGrayColor, float pMinPercentage,
             float pMaxPercentage){
            x1 = pNewX1; y1 = pNewY1; x2 = pNewX2; y2 = pNewY2;
            numberOfPoints = pNewNumberOfPoints;
            percentage = pNewPercentage;
            minPercentage = pMinPercentage;
            maxPercentage = pMaxPercentage;
            GrayColorValue=pNewGrayColor;
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

        float GetDensity() const {
                return density;
        }

        void SetDensity(float pDensity) {
                density = pDensity;
        }

        int GetGrayColorValue() const {
                return GrayColorValue;
        }

        void SetGrayColorValue(int pGrayColorValue) {
                GrayColorValue = pGrayColorValue;
        }

        vector<GrayColor> getVectorColors(){
            return colors;
        }

        std::vector<GrayColor> GetColors() const {
                return colors;
        }

        void SetColors(std::vector<GrayColor> colors) {
                colors = colors;        }

        /**
         * @brief adds the color to the vector of colors or counts the appearances
         *        of that color if it already exits in the vector.
         *
         * @param pNewColor
         */
        void addColor(GrayColor pNewColor){
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
                minPercentage = pLastMin;
                maxPercentage = minPercentage + ((float)numberOfPoints / (float)pTotalPoints);
        }

        /**
         * @brief Set the Dominant Gray color of the area
         *
         */
        void setDominantGray(){
               GrayColor dominant = colors.at(0);
               vector<GrayColor> newColorsVector(11);
               _initColorVector(newColorsVector);
               int newColor;
                for (GrayColor current: colors){
                        if(current.appearances > dominant.appearances){ //determines dominant rgb gray color
                                dominant = current;
                        }
                        //gets the gray category based on the gray intesity. if it approaches 255 the value approaches 10
                        //if it approaches 0 the value approaches 0
                        newColor = round(current.value * 10 / 255);
                        newColorsVector[newColor].appearances += 1; //increases the appereances to know how many points of that category exist

                }
                GrayColorValue = dominant.value;
                colors = newColorsVector;
        }
};



#endif
