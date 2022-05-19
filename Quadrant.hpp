#ifndef __QUADRANTE_HEADER__
#define __QUADRANTE_HEADER__

class Range {
protected:
    int NumberOfAppearances;
    int red;
    int green;
    int blue;
    int range;
    friend class Quadrant;
public:
    Range(int red, int green, int blue) {
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->NumberOfAppearances = 1;
        this->range = 25;
    }

    bool isInRange(int red, int green, int blue) {
        if (red >= this->red && red <= this->red + range) {
            if (green >= this->green && green <= this->green + range) {
                if (blue >= this->blue && blue <= this->blue + range) {
                    return true;
                }
            }
        }
        return false;
    }

    int getNumberOfAppearances() {
        return NumberOfAppearances;
    }

    void incrementNumberOfAppearances() {
        NumberOfAppearances++;
    }

    int getRed() {
        return red+range;
    }
    
    int getGreen() {
        return green+range;
    }

    int getBlue() {
        return blue+range;
    }
};


class Quadrant {

private:
    pair<int, int> downLeft;
    pair<int, int> upRight;
    vector<Range*> ranges;

public:
    Quadrant(pair<int, int> downLeft, pair<int, int> upRight){
        this->downLeft = downLeft;
        this->upRight = upRight;
    }

    pair<int, int> getDownLeft(){
        return this->downLeft;
    }
    pair<int, int> getUpRight(){
        return this->upRight;
    }

    void verifyRange(int red, int green, int blue) {
        for (Range* range : ranges) {
            if (range->isInRange(red, green, blue)) {
                range->incrementNumberOfAppearances();
                return;
            }
        }
        Range* newRange = new Range(red, green, blue);
        ranges.push_back(newRange);
    }

    void getPredominantColorRange(){
        int maxAppearances = 0;
        int index = 0;
        for (int i = 0; i < ranges.size(); i++) {
            if (ranges[i]->getNumberOfAppearances() > maxAppearances) {
                maxAppearances = ranges[i]->getNumberOfAppearances();
                index = i;
            }
        }
        cout<<"El color predominante es: "<< ranges[index]->getRed()<<", "<<ranges[index]->getGreen()<<", "<<ranges[index]->getBlue()<<endl;
    }

    void getRanges() {
        for (Range* range : ranges) {
            cout << "Red: " << range->getRed() << " Green: " << range->getGreen() << " Blue: " << range->getBlue() << " Number of appearances: " << range->getNumberOfAppearances() << endl;
        }
    }
};

#endif