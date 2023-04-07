#include "../include/KMeans.h"
#include "../../include/DataHandler.h"

#include <iostream>

int main()
{
    DataHandler* data_handler = new DataHandler();
    data_handler->readFeatureVector("../dataset/train-images.idx3-ubyte");
    data_handler->readFeatureLabels("../dataset/train-labels.idx1-ubyte");
    data_handler->splitData();
    data_handler->countClasses();

    double performance = 0.0;
    double best_performance = 0.0;
    int best_k = 1;

    for(int k = data_handler->getClassCounts(); k < data_handler->getTrainingData()->size() * 0.1; ++k)
    {
        KMeans* kmeans = new KMeans(k);
        kmeans->setTrainingData(data_handler->getTrainingData());
        kmeans->setTestData(data_handler->getTestData());
        kmeans->setValidationData(data_handler->getValidationData());
        kmeans->initClusters();
        kmeans->train();
        performance = kmeans->validate();
        std::cout << "Current k = " << k << ", performance = " << performance << std::endl;

        if(performance > best_performance)
        {
            best_performance = performance;
            best_k = k;
        }
    }

    KMeans* kmeans = new KMeans(best_k);
    kmeans->setTrainingData(data_handler->getTrainingData());
    kmeans->setTestData(data_handler->getTestData());
    kmeans->setValidationData(data_handler->getValidationData());
    kmeans->initClusters();
    kmeans->train();
    performance = kmeans->test();
    std::cout << "Best k = " << best_k << ", tested performance = " << performance << std::endl;

    return 0;
}