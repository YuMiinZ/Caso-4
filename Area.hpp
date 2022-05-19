#ifndef __AREA_HEADER__
#define __AREA_HEADER__

class Area{
    private:
        int x1;
        int y1;
        int x2;
        int y2;
        int numberOfPoints;
        double percentage;
        

    public:
        Area() = default;
        Area(int pNewX1, int pNewY1, int pNewX2, int pNewY2, int pNewNumberOfPoints, int pNewPercentage){
            x1 = pNewX1; y1 = pNewY1; x2 = pNewX2; y2 = pNewY2;
            numberOfPoints = pNewNumberOfPoints;
            percentage = pNewPercentage;
        }
        int GetX1() const {
        return x1;
        }

        void SetX1(int x1) {
        x1 = x1;
        }

        int GetY1() const {
                return y1;
        }

        void SetY1(int y1) {
                y1 = y1;
        }

        int GetX2() const {
                return x2;
        }

        void SetX2(int x2) {
                x2 = x2;
        }

        int GetY2() const {
                return y2;
        }

        void SetY2(int y2) {
                y2 = y2;
        }

        int GetNumberOfPoints() const {
                return numberOfPoints;
        }

        void SetNumberOfPoints(int numberOfPoints) {
                numberOfPoints = numberOfPoints;
        }

        int GetPercentage() const {
                return percentage;
        }

        void SetPercentage(int percentage) {
                percentage = percentage;
        }
};



#endif