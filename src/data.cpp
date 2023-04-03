#include "..\include\Data.h"

Data::Data()
{
    feature_vector = new std::vector<uint8_t>();
}

~Data::Data()
{
    delete feature_vector;
}

void Data::setFeatureVector(std::vector<uint8_t>* v);
{
    delete feature_vector;
    feature_vector = v;
}

void Data::appendToFeatureVector(uint8_t val);
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