#ifndef __DATA_HANDLER_H
#define __DATA_HANDLER_H

#include <string>
#include <fstream>
#include <map>
#include <unordered_set>

#include "Data.h"

constexpr double TRAIN_SET_PERCENT = 0.75;
constexpr double TEST_SET_PERCENT = 0.20;
constexpr double VALIDATION_SET_PERCENT = 0.05; 

class DataHandler
{
public:
    DataHandler();
    ~DataHandler();

    void readFeatureVector(const std::string& path);
    void readFeatureLabels(const std::string& path);
    void splitData();
    void countClasses();
    
    uint32_t convertToLittleEndian(const unsigned char* bytes);

    std::vector<Data*>* getTrainingData();
    std::vector<Data*>* getTestData();
    std::vector<Data*>* getValidationData();

private:
    std::vector<Data*>* dataArray; //all of the data (pre-split)
    std::vector<Data*>* trainingData;
    std::vector<Data*>* testData;
    std::vector<Data*>* validationData;

    int numClasses;
    int featureVectorSize;
    std::map<uint8_t, int> classMap;
};  

#endif