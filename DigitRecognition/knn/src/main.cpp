#include "../include/KNN.h"

#include "../../include/DataHandler.h"

#include <cmath>
#include <limits>
#include <map>
#include <iostream>
#include <algorithm>

int main()
{
    DataHandler* data_handler = new DataHandler();
    data_handler->readFeatureVector("../dataset/train-images.idx3-ubyte");
    data_handler->readFeatureLabels("../dataset/train-labels.idx1-ubyte");
    data_handler->splitData();
    data_handler->countClasses();

    KNN* knn = new KNN();
    knn->setTrainingData(data_handler->getTrainingData());
    knn->setTestData(data_handler->getTestData());
    knn->setValidationData(data_handler->getValidationData());

    double performance = 0.0;
    double best_performance = 0.0;
    int best_k = 1;

    for(int k = 1; k <= 4; ++k)
    {
        knn->setK(k);
        performance = knn->validatePerformance();
        if(performance > best_performance)
        {
            best_performance = performance;
            best_k = k;
        }
    }

    knn->setK(best_k);
    knn->testPerformance();
    return 0;
}