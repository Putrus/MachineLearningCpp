#ifndef __DATA_H
#define __DATA_H

#include <vector>
#include <iostream>

class Data
{
public:
    Data();
    ~Data();

    void setFeatureVector(std::unique_ptr<std::vector<uint8_t>> v);
    void appendToFeatureVector(uint8_t val);
    void setLabel(uint8_t label);
    void setEnumeratedLabel(int enum_label);
    void setDistance(double val);

    int getFeatureVectorSize() const;
    uint8_t getLabel() const;
    uint8_t getEnumeratedLabel() const;

    std::unique_ptr<std::vector<uint8_t>> getFeatureVector() const;

private:
    std::unique_ptr<std::vector<uint8_t>> featureVector;
    uint8_t label;
    int enumLabel;
};

#endif