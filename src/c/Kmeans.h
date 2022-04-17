//
// Created by ram on 04/04/2022.
//
#include <stdio.h>
#include<malloc.h>
#include<math.h>
#include <stdlib.h>
#include <string.h>
#include "Kmeans_ds.h"


#ifndef HW1__KMEANS_H_
#define HW1__KMEANS_H_

km Kmeans (int K, const char* input_filename, const char* output_filename, int max_iter, double epsilon);
int is_converged(double *centroids, double *oldcentroids, int K, int veclength);
int closest_cluster_index(double *x, double *centroids, int K, int veclength);
void initialize_data_points();
void initialize_centroids();
void initialize_clusters();
void assign_to_clusters();
void update_centroids();
void output_centroids();
void run();
#endif // HW1__KMEANS_H_
