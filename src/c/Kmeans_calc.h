//
// Created by ram on 10/04/2022.
// A set of function to support math operations over the Kmeans related data structures.
//

#ifndef C__KMEANS_CALC_H_
#define C__KMEANS_CALC_H_
#include "Kmeans_ds.h"
double scalar_mult(dp dp1, dp dp2); // return the scalar multiplication of two given data point vectors
dp subtract_data_points(dp dp1, dp dp2); // returns the difference of two data point vectors
dp sum_data_points(dp dp1, dp dp2); // returns the sum of two data point vectors
dp aggregate(dp* ds); // return the sum of a given matrix of data points
double norm(dp x); // return the length of a given data point vector
double distance(dp x, dp y); // returns the distance between two given data points
int find_closest_cluster(dp); // return the index of the closest cluster to the given data point
#endif //C__KMEANS_CALC_H_
