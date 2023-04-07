#ifndef __KMEANS_H
#define __KMEANS_H

#include "../../include/Coheir.h"

#include <unordered_set>
#include <limits>
#include <iostream>
#include <cmath>
#include <map>

struct Cluster
{
    Cluster(Data* initial_point)
    {
        centroid = new std::vector<double>();
        cluster_points = new std::vector<Data*>();
        centroid->reserve(initial_point->getFeatureVectorSize());
        for(const auto& value : *(initial_point->getFeatureVector()))
        {
            centroid->push_back(value);
        }
        cluster_points->push_back(initial_point);
        class_counts[initial_point->getLabel()];
        most_frequent_class = initial_point->getLabel();
    }

    void setMostFrequentClass()
    {
        int best_class = -1;
        int freq = 0;
        //kv - key value
        for(const auto& kv : class_counts)
        {
            if(kv.second > freq)
            {
                freq = kv.second;
                best_class = kv.first;
            }
        }
        most_frequent_class = best_class;
    }

    void addToCluster(Data* point)
    {
        int previous_size = cluster_points->size();
        cluster_points->push_back(point);
        for(int i = 0; i < centroid->size() - 1; ++i)
        {
            double value = centroid->at(i);
            value *= previous_size;
            value += point->getFeatureVector()->at(i);
            value /= (double)cluster_points->size();
            centroid->at(i) = value;
        }

        if(class_counts.find(point->getLabel()) == class_counts.end())
        {
            class_counts[point->getLabel()] = 1;
        }
        else
        {
            ++class_counts[point->getLabel()];
        }
        setMostFrequentClass();
    }

    std::vector<double>* centroid;
    std::vector<Data*>* cluster_points;
    std::map<int, int> class_counts;
    int most_frequent_class;
};

class KMeans : public Coheir
{
public:
    KMeans(int k);
    ~KMeans();
    void initClusters();
    void initClustersForEachClass();
    void train();
    double euclidianDistance(std::vector<double>* centroid, Data* point);
    double validate();
    double test();

private:
    int num_clusters;
    std::vector<Cluster*>* clusters;
    std::unordered_set<int>* used_indexes;
};

#endif