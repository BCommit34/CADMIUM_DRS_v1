#ifndef COLLECTION_PT_HPP
#define COLLECTION_PT_HPP

#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <new>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;
using namespace std;

struct collection_pt {
    int index;
    int num_street;
    std::string name_street;
    double xCoordinate;
    double yCoordinate;
    bool bool_intersection;
    int* index_closest_pt;
};

struct Tuple_update{
    int coordinate;
    double weight;
};

struct Tuple_active{
    int truck_id;
    bool active;
};

static double calculate_distance_points(collection_pt next_pt, collection_pt current_pt){
    return sqrt(pow(next_pt.xCoordinate - current_pt.xCoordinate,2)+pow(next_pt.yCoordinate - current_pt.yCoordinate,2));
}

static int* find_index(std::vector<std::vector<collection_pt>> map, int cmp_index){
    int* rt = (int*)malloc(sizeof(int));
    for (int i = 0; i<map.size() ; i++){
        for(int j=0; j<map[i].size() ; j++){
            if(map[i][j].index==cmp_index){
                rt[0] = i;
                rt[1] = j;
                return rt;
            }
        }
    }
    rt[0] = -1;
    rt[1] = -1;
    return rt;
}

#endif