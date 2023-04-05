#include "../include/DataHandler.h"

constexpr unsigned int IMAGE_HEADERS = 4;
constexpr unsigned int LABEL_HEADERS = 2;
constexpr unsigned int BYTES_OFFSET = 4;

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
    FILE* file = fopen(path.c_str(), "rb");
    if(file)
    {
        uint32_t header[IMAGE_HEADERS]; //magic, num images, row size, col size
        unsigned char bytes[BYTES_OFFSET];
        for(int i = 0; i < IMAGE_HEADERS; ++i)
        {
            if (fread(bytes, sizeof(bytes), 1, file))
            {
                header[i] = convertToLittleEndian(bytes);
            }
        }
        std::cout << "Getting input file header is done." << std::endl;

        int image_size = header[2] * header[3];
        for(int i = 0; i < header[1]; ++i)
        { 
            Data* data = new Data();
            uint8_t element;
            for(int j = 0; j < image_size; ++j)
            {
                if(fread(&element, sizeof(element), 1, file))
                {
                    data->appendToFeatureVector(element);
                }
                else
                {
                    std::cout << "Error reading from file " << path << std::endl;
                    exit(1);
                }
            }
            data_array->push_back(data);
        }
        std::cout << "Successfully read and stored " << data_array->size() << " feature vectors." << std::endl;
    }
    else
    {
        std::cout << "Could not find the file " << path << std::endl;
        exit(1);
    }
}

void DataHandler::readFeatureLabels(const std::string& path)
{
    uint32_t header[LABEL_HEADERS]; //magic number, images
    unsigned char bytes[BYTES_OFFSET];

    FILE* file = fopen(path.c_str(), "rb");
    if(file)
    {
        for(int i = 0; i < LABEL_HEADERS; ++i)
        {
            if(fread(bytes, sizeof(bytes), 1, file))
            {
                header[i] = convertToLittleEndian(bytes);
            }
        }
        std::cout << "Getting label file header is done." << std::endl;
        for(int i = 0; i < header[1]; ++i)
        {
            uint8_t element;
            if(fread(&element, sizeof(element), 1, file))
            {
                data_array->at(i)->setLabel(element);
            }
            else
            {
                std::cout << "Error reading from file " << path << std::endl;
                exit(1);
            }
        }
        std::cout << "Succesfully read and stored " << data_array->size() << " label vector." << std::endl;
    }
    else
    {
        std::cout << "Could not find the file " << path << std::endl;
        exit(1);
    }
}

void DataHandler::splitData()
{
    std::unordered_set<int> used_indexes;

    int train_size = data_array->size() * TRAIN_SET_PERCENT;
    fillRandomly(used_indexes, training_data, train_size);
    std::cout << "Training data size: " << training_data->size() << std::endl;

    int test_size = data_array->size() * TEST_SET_PERCENT;
    fillRandomly(used_indexes, test_data, test_size);
    std::cout << "Test data size: " << test_data->size() << std::endl;

    int validation_size = data_array->size() * VALIDATION_SET_PERCENT;
    fillRandomly(used_indexes, validation_data, validation_size);
    std::cout << "Validation data size: " << validation_data->size() << std::endl;
}

void DataHandler::countClasses()
{
    int count = 0;
    for(unsigned i = 0; i < data_array->size(); ++i)
    {
        if(class_map.find(data_array->at(i)->getLabel()) == class_map.end())
        {
            class_map[data_array->at(i)->getLabel()] = count;
            data_array->at(i)->setEnumeratedLabel(count);
            ++count;
        }
    }
    num_classes = count;
    std::cout << "Successfully extracted " << num_classes << " unique classes." << std::endl;
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
    return training_data;
}

std::vector<Data*>* DataHandler::getTestData()
{
    return test_data;
}

std::vector<Data*>* DataHandler::getValidationData()
{
    return validation_data;
}

void DataHandler::fillRandomly(std::unordered_set<int>& used_indexes, std::vector<Data*>* data, int size)
{
    while(data->size() < size)
    {
        int rand_index = rand() % data_array->size();
        if(used_indexes.find(rand_index) == used_indexes.end())
        {
            data->push_back(data_array->at(rand_index));
            used_indexes.insert(rand_index);
        }
    }
}