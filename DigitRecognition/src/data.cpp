#include "../include/Data.h"

Data::Data() : x_size(0), y_size(0)
{
    feature_vector = new std::vector<uint8_t>();
}

Data::Data(int x, int y) : x_size(x), y_size(y) 
{
    feature_vector = new std::vector<uint8_t>();
}

Data::~Data()
{
    delete feature_vector;
}

void Data::setFeatureVector(std::vector<uint8_t>* v)
{
    delete feature_vector;
    feature_vector = v;
}

void Data::appendToFeatureVector(uint8_t val)
{
   feature_vector->push_back(val); 
}

void Data::setLabel(uint8_t label)
{
    this->label = label;
}

void Data::setEnumeratedLabel(int enum_label)
{
    this->enum_label = enum_label;
}

void Data::setDistance(double val)
{
    distance = val;
}

void Data::display()
{
    std::string ascii_chars = ".,-~:;=!*#$@";
    int range_size = 256 / ascii_chars.length() + 1;
    for(int i = 0; i < y_size; ++i)
    {
        for(int j = 0; j < x_size; ++j)
        {
            int brightness = this->getFeatureVector()->at(y_size * i + j);
            std::cout << ascii_chars[brightness / range_size] << " ";
        }
        std::cout << std::endl;
    }
}

int Data::getFeatureVectorSize() const
{
    return feature_vector == nullptr ? 0 : feature_vector->size();
}

uint8_t Data::getLabel() const
{
    return label;
}

uint8_t Data::getEnumeratedLabel() const
{
    return enum_label;
}

const std::vector<uint8_t>* Data::getFeatureVector() const
{
    return feature_vector;
}