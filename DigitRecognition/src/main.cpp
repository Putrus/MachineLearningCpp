#include "../include/Data.h"
#include "../include/DataHandler.h"

int main()
{
    DataHandler* data_handler = new DataHandler();
    data_handler->readFeatureVector("../dataset/train-images.idx3-ubyte");
    data_handler->readFeatureLabels("../dataset/train-labels.idx1-ubyte");
    data_handler->splitData();
    data_handler->countClasses();
    return 0;
}