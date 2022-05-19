#ifndef __POINT_HEADER__
#define __POINT_HEADER__

class Point{
    private:
        int x;
        int y;
        string greyColor;
        int shape;
        int size;
        

    public:
        Point() = default;
        Point(int pNewX, int pNewY, string pNewGreyColor, int pNewShape, int pNewSize){
            x = pNewX; y = pNewY;
            greyColor = pNewGreyColor;
            shape = pNewShape;
            size = pNewSize;
        }
        int GetX() const {
        return x;
        }

        void SetX(int x) {
        x = x;
        }

        int GetY() const {
                return y;
        }

        void SetY(int y) {
                y = y;
        }

        string GetGreyColor() const {
                return greyColor;
        }

        void SetGreyColor(string greyColor) {
                greyColor = greyColor;
        }

        int GetShape() const {
                return shape;
        }

        void SetShape(int shape) {
                shape = shape;
        }

        int GetSize() const {
                return size;
        }

        void SetSize(int size) {
                size = size;
        }
};

#endif