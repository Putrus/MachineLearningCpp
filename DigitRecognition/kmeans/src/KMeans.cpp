#include "../include/KMeans.h"

#include <random>

KMeans::KMeans(int k)
{
    num_clusters = k;
    clusters = new std::vector<Cluster*>();
    used_indexes = new std::unordered_set<int>();
}

KMeans::~KMeans()
{
    for(auto& cluster : *clusters)
    {
        delete cluster;
    }
    delete clusters;
    delete used_indexes;
}

void KMeans::initClusters()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, training_data->size() - 1);

    for(int i = 0; i < num_clusters; ++i)
    {
        int index = dis(gen);
        while(used_indexes->find(index) != used_indexes->end())
        {
            index = dis(gen);
        }
        clusters->push_back(new Cluster(training_data->at(index)));
        used_indexes->insert(index);
    }
}

void KMeans::initClustersForEachClass()
{
    std::unordered_set<int> classes_used;
    for(int i = 0; i < training_data->size(); ++i)
    {
        if(classes_used.find(training_data->at(i)->getLabel()) == classes_used.end())
        {
            clusters->push_back(new Cluster(training_data->at(i)));
            classes_used.insert(training_data->at(i)->getLabel());
            used_indexes->insert(i);
        }
    }
}

void KMeans::train()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, training_data->size() - 1);
    while(used_indexes->size() < training_data->size())
    {
        int index = dis(gen);
        while(used_indexes->find(index) != used_indexes->end())
        {
            index = dis(gen);
        }
        double min_dist = std::numeric_limits<double>::max();
        int best_cluster = 0;
        for(int j = 0; j < clusters->size(); ++j)
        {
            double current_dist = euclidianDistance(clusters->at(j)->centroid, training_data->at(index));
            if(current_dist < min_dist)
            {
                min_dist = current_dist;
                best_cluster = j;
            }
        }
        clusters->at(best_cluster)->addToCluster(training_data->at(index));
        used_indexes->insert(index);
    }
}

double KMeans::euclidianDistance(std::vector<double>* centroid, Data* point)
{
    double dist = 0.0;
    for(int i = 0; i < centroid->size(); ++i)
    {
        dist += std::pow(centroid->at(i) - point->getFeatureVector()->at(i), 2);
    }
    return std::sqrt(dist);
}

double KMeans::validate()
{
    double num_correct = 0.0;
    for(const auto& query_point : *validation_data)
    {
        double min_dist = std::numeric_limits<double>::max();
        int best_cluster = 0;
        for(int j = 0; j < clusters->size(); ++j)
        {
            double current_dist = euclidianDistance(clusters->at(j)->centroid, query_point);
            if(current_dist < min_dist)
            {
                min_dist = current_dist;
                best_cluster = j;
            }
        }
        if(clusters->at(best_cluster)->most_frequent_class == query_point->getLabel())
        {
            ++num_correct;
        }
    }
    return 100.0 * num_correct / (double)validation_data->size();
}

double KMeans::test()
{
    double num_correct = 0.0;
    for(const auto& query_point : *test_data)
    {
        double min_dist = std::numeric_limits<double>::max();
        int best_cluster = 0;
        for(int j = 0; j < clusters->size(); ++j)
        {
            double current_dist = euclidianDistance(clusters->at(j)->centroid, query_point);
            if(current_dist < min_dist)
            {
                min_dist = current_dist;
                best_cluster = j;
            }
        }
        if(clusters->at(best_cluster)->most_frequent_class == query_point->getLabel())
        {
            ++num_correct;
        }
    }
    return 100.0 * num_correct / (double)test_data->size();
}