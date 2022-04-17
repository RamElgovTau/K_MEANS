//
// Created by ram on 10/04/2022.
//
#include "math.h"

int is_converged(double *centroids, double *oldcentroids, int K, int veclength) {
  int i = 0,
      c = 0,
      j = 0;
  double norm = 0;
  for (i = 0; i < K; i++) {
    norm = 0;
    for (j = 0; j < veclength; j++) {
      norm += pow(centroids[i * veclength + j] - oldcentroids[i * veclength + j], 2);
    }
    norm = pow(norm, 0.5);
    if (norm < 0.001) {
      c++;
    }
  }
  if (c == K) {
    return 0;
  }
  return 1;
}
int closest_cluster_index(double *x, double *centroids, int K, int veclength) {
  double min = 0,
      sum;
  int j = 0,
      i = 0,
      index = 0;
  for (i = 0; i < veclength; i++) {
    min += pow(x[i] - centroids[i], 2);
  }
  for (j = 1; j < K; j++) {
    sum = 0;
    for (i = 0; i < veclength; i++) {
      sum += pow(x[i] - centroids[j * veclength + i], 2);
    }
    if (sum < min) {
      min = sum;
      index = j;
    }
  }
  return index;
}
