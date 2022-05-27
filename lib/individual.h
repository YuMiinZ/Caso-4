#ifndef _INDIVIDUAL_
#define _INDIVIDUAL_ 1

#define MIN_GENOTYPE_SIZE_BY_PARENT 2

class individual {
    private:
        // any important related info
        // decide the size of your nibble for your problem
        float fitnessValue;
        unsigned char cromosoma;
        short xValue, yValue, cromosomaValue;

    public:
        /*individual(unsigned char pValue) {
            this->cromosoma = pValue;
        }*/

        individual(short pCromosoma) {
            this->cromosomaValue = pCromosoma;
        }

       /* unsigned char getCromosoma() {
            return this->cromosoma;
        }*/

        void setFitnessValue(float pValue) {
            this->fitnessValue = pValue;
        }

        float getFitnessValue() {
            return this->fitnessValue;
        }

        void setXValue(short pXValue){
            xValue=pXValue;
        }

        short getXValue(){
            return xValue;
        }

        void setYValue(short pYValue){
            yValue=pYValue;
        }

        short getYValue(){
            return yValue;
        }

        short getCromosoma(){
            return cromosomaValue;
        }
};


#endif
