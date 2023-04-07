#ifndef __KNN_H
#define __KNN_H

#include "../../include/Data.h"

#include <vector>

class KNN
{
public:
    KNN();
    KNN(int k);
    ~KNN();

    void findKNearest(Data* query_point);
    void setTrainingData(std::vector<Data*>* v);
    void setTestData(std::vector<Data*>* v);
    void setValidationData(std::vector<Data*>* v);
    void setK(int val);

    int predict();

    double calculateDistance(Data* query_point, Data* input);
    double validatePerformance();
    double testPerformance();

private:
    int k;
    std::vector<Data*>* neighbors;
    std::vector<Data*>* training_data;
    std::vector<Data*>* test_data;
    std::vector<Data*>* validation_data;
};

#endif