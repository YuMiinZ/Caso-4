#ifndef _INDIVIDUAL_
#define _INDIVIDUAL_ 1

#define MIN_GENOTYPE_SIZE_BY_PARENT 2

class individual {
    private:
        // any important related info
        // decide the size of your nibble for your problem
        float fitnessValue;
        unsigned short xValue, yValue, cromosomaValue;

    public:

        individual(short pCromosoma) {
            this->cromosomaValue = pCromosoma;
        }

        void setFitnessValue(float pValue) {
            this->fitnessValue = pValue;
        }

        float getFitnessValue() {
            return this->fitnessValue;
        }

        void setXValue(short pXValue){
            xValue=pXValue;
        }

        unsigned getXValue(){
            return xValue;
        }

        void setYValue(short pYValue){
            yValue=pYValue;
        }

        unsigned getYValue(){
            return yValue;
        }

        unsigned getCromosoma(){
            return cromosomaValue;
        }

        void setCromosoma(unsigned short pCromosoma){
            cromosomaValue=pCromosoma;
        }
};


#endif
