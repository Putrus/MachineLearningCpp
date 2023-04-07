#include "../include/Coheir.h"

void Coheir::setTrainingData(std::vector<Data*>* v)
{
    training_data = v;
}

void Coheir::setTestData(std::vector<Data*>* v)
{
    test_data = v;
}

void Coheir::setValidationData(std::vector<Data*>* v)
{
    validation_data = v;
}