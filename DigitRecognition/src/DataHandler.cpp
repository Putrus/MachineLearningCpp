#include "..\include\DataHandler.h"

DataHandler::DataHandler()
{
    data_array = new std::vector<Data*>;
    test_data = new std::vector<Data*>;
    training_data = new std::vector<Data*>;
    validation_data = new std::vector<Data*>;
}

DataHandler::~DataHandler()
{
    auto delete_vector = [](std::vector<Data*>* v)
    {
        for (auto data : *v)
        {
            delete data;
        }
        delete v;
    };
    delete_vector(data_array);
    delete_vector(test_data);
    delete_vector(training_data);
    delete_vector(validation_data);
}

void DataHandler::readFeatureVector(const std::string& path)
{
    uint32_t header[4]; //magic, num images, row size, col size
    unsigned char bytes[4];

    FILE* file = fopen(path.c_str(), "r");
    if (file)
    {
        for (int i = 0; i < 4; ++i)
        {
            if (fread(bytes, sizeof(bytes), 1, file))
            {
                header[i] = convertToLittleEndian(bytes);
            }
            std::cout << "Getting input file header is done." << std::endl; 
        }
    }
}

void DataHandler::readFeatureLabels(const std::string& path)
{

}

void DataHandler::splitData()
{

}

void DataHandler::countClasses()
{

}

uint32_t DataHandler::convertToLittleEndian(const unsigned char* bytes)
{
    if (bytes == nullptr)
    {
        return 0;
    }

    return (uint32_t) ((bytes[0] << 24) |
        (bytes[1] << 16) | (bytes[2 << 8]) | bytes[3]);
}

std::vector<Data*>* DataHandler::getTrainingData()
{

}

std::vector<Data*>* DataHandler::getTestData()
{

}

std::vector<Data*>* DataHandler::getValidationData()
{

}