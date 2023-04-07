#ifndef __KNN_H
#define __KNN_H

#include "../../include/Coheir.h"

#include <vector>

class KNN : public Coheir
{
public:
    KNN();
    KNN(int k);
    ~KNN();

    void findKNearest(Data* query_point);
    void setK(int val);

    int predict();

    double calculateDistance(Data* query_point, Data* input);
    double validatePerformance();
    double testPerformance();

private:
    int k;
    std::vector<Data*>* neighbors;
};

#endif