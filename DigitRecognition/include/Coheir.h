#ifndef __COHEIR_H
#define __COHEIR_H

#include "Data.h"

#include <vector>

class Coheir
{
public:
    void setTrainingData(std::vector<Data*>* v);
    void setTestData(std::vector<Data*>* v);
    void setValidationData(std::vector<Data*>* v);

protected:
    std::vector<Data*>* training_data;
    std::vector<Data*>* test_data;
    std::vector<Data*>* validation_data;
};

#endif