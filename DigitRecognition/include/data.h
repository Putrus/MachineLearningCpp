#ifndef __DATA_H
#define __DATA_H

#include <vector>
#include <iostream>

class Data
{
public:
    Data();
    Data(int x, int y);
    ~Data();

    void setFeatureVector(std::vector<uint8_t>* v);
    void appendToFeatureVector(uint8_t val);
    void setLabel(uint8_t label);
    void setEnumeratedLabel(int enum_label);
    void setDistance(double val);
    void display();

    int getFeatureVectorSize() const;
    uint8_t getLabel() const;
    uint8_t getEnumeratedLabel() const;

    const std::vector<uint8_t>* getFeatureVector() const;

private:
    std::vector<uint8_t>* feature_vector;
    uint8_t label;
    int enum_label;
    double distance;
    int x_size;
    int y_size;
};

#endif