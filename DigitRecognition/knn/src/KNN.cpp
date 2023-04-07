#include "../include/KNN.h"

#include "../../include/DataHandler.h"

#include <cmath>
#include <limits>
#include <map>
#include <iostream>

KNN::KNN()
{
}

KNN::KNN(int k) : k(k)
{
}

KNN::~KNN()
{

}

void KNN::findKNearest(Data* query_point)
{
    neighbors = new std::vector<Data*>();
    double min = std::numeric_limits<double>::max();
    double previous_min = min;

    int index = 0;
    for(int i = 0; i < k; ++i)
    {
        for(int j = 0; j < training_data->size(); ++j)
        {
            double distance = calculateDistance(query_point, training_data->at(j));
            training_data->at(j)->setDistance(distance);
            //i == 0 because at the beginning previous_min is DOUBLE_MAX so distance never be bigger than previous_min
            if((i == 0 || distance > previous_min) && distance < min)
            {
                min = distance;
                index = j;
            }
        }
        neighbors->push_back(training_data->at(index));
        previous_min = min;
        min = std::numeric_limits<double>::max();
    }
}

void KNN::setK(int val)
{
    k = val;
}

int KNN::predict()
{
    std::map<uint8_t, int> class_freq;
    for(int i = 0; i < neighbors->size(); ++i)
    {
        if(class_freq.find(neighbors->at(i)->getLabel()) == class_freq.end())
        {
            class_freq[neighbors->at(i)->getLabel()] = 1;
        }
        else
        {
            ++class_freq[neighbors->at(i)->getLabel()];
        }
    }

    int best = 0;
    int max = 0;
    for(const auto& kv : class_freq)
    {
        if(kv.second > max)
        {
            max = kv.second;
            best = kv.first;
        }
    }
    delete neighbors;
    return best;
}

double KNN::calculateDistance(Data* query_point, Data* input)
{
    double distance = 0.0;
    if(query_point->getFeatureVectorSize() != input->getFeatureVectorSize())
    {
        std::cout << "Error vector size mismatch!" << std::endl;
        exit(1);
    }

    //#ifdef EUCLID
    for(unsigned i = 0; i < query_point->getFeatureVectorSize(); ++i)
    {
        distance += std::pow(query_point->getFeatureVector()->at(i) - input->getFeatureVector()->at(i), 2);
    }
    return std::sqrt(distance);
    //#elif defined MANHATTAN
    //to do
    //#endif
}

double KNN::validatePerformance()
{
    double current_performance = 0.0;
    double count = 0;
    double data_index = 0;

    for(Data* query_point : *validation_data)
    {
        findKNearest(query_point);
        int prediction = predict();
        if(prediction == query_point->getLabel())
        {
            ++count;
        }
        ++data_index;

        if(prediction != query_point->getLabel())
        {
            query_point->display();
            std::cout << prediction << " -> " << (int)query_point->getLabel() << std::endl;
            std::cout << "Current performance = " << count * 100.0 / data_index << std::endl;
        }
        std::cout << data_index << "/" << validation_data->size() << " " << data_index * 100.0 / (double)validation_data->size() << "%" << std::endl;
    }
    current_performance = count * 100.0 / (double)validation_data->size();
    std::cout << "Validation performance for each k = " << k << " : " << current_performance << std::endl;
    return current_performance;
}

double KNN::testPerformance()
{
    double current_performance = 0.0;
    double count = 0;
    double data_index = 0;

    for(Data* query_point : *test_data)
    {
        findKNearest(query_point);
        int prediction = predict();
        if(prediction == query_point->getLabel())
        {
            ++count;
        }
        ++data_index;
    }
    current_performance = count * 100.0 / (double)test_data->size();
    std::cout << "Current performance for each k = " << k << " : " << current_performance << std::endl;
    return current_performance;
}