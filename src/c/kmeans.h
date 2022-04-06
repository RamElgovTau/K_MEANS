//
// Created by ram on 04/04/2022.
//
#include <stdio.h>
#include<malloc.h>
#include<math.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char **argv) {
    FILE *ifp, *ofp;
    double vec = 0;
    char c;
    int filelength = 0,
        veclength = 0,
        iteration_num = 0,
        valid = 1,
        i = 0,
        j = 0,
        maxiter,
        K,
        digit_num,
        counter,
    double *vectors,
           **filearr,
           *centroids,
           *oldcentroids,
           *clusters;
    int *sizeofclusters;
    while ((c = fgetc(ifp)) != EOF) {
        if (c == '\n') {
            filelength++;
            veclength++;
        }
        if (c == ',') {
            veclength++;
        }
    }
    veclength = veclength / filelength;
    vectors = calloc(veclength * filelength, sizeof(double));
    filearr = calloc(filelength, sizeof(double *));
    centroids = calloc(K * veclength, sizeof(double));
    oldcentroids = calloc(K * veclength, sizeof(double));
    clusters = calloc(K * veclength, sizeof(double));
    sizeofclusters = calloc(K, sizeof(int));
    rewind(ifp);
    while (fscanf(ifp, "%lf,", &vec) != EOF) {
        vectors[i] = vec;
        i++;
    }
    for (i = 0; i < filelength; i++) {
        filearr[i] = calloc(veclength, sizeof(double));
    }
    for (i = 0; i < filelength; i++) {
        for (j = 0; j < veclength; j++) {
            filearr[i][j] = vectors[i * veclength + j];
        }
    }
    for (i = 0; i < veclength * K; i++) {
        centroids[i] = vectors[i];
    }
    iteration_num = 0;
    valid = 1;
    while (iteration_num < maxiter && valid == 1) {
        for (i = 0; i < K * veclength; i++) {
            oldcentroids[i] = centroids[i];
        }
        for (i = 0; i < filelength; i++) {
            int index = closest_cluster_index(filearr[i], centroids, K, veclength);
            for (j = 0; j < veclength; j++) {
                clusters[index * veclength + j] += filearr[i][j];
            }
            sizeofclusters[index]++;
        }
        for (j = 0; j < K; j++) {
            for (i = 0; i < veclength; i++) {
                centroids[veclength * j + i] = clusters[veclength * j + i] / sizeofclusters[j];
            }
        }
        for (j = 0; j < K * veclength; j++) {
            clusters[j] = 0;
        }
        for (j = 0; j < K; j++) {
            sizeofclusters[j] = 0;
        }
        valid = is_converged(centroids, oldcentroids, K, veclength);
        iteration_num++;
    }
    for (i = 0; i < K; i++) {
        for (j = 0; j < veclength; j++) {
            fprintf(ofp, "%.4f", centroids[i * veclength + j]);
            if (j < veclength - 1) {
                fprintf(ofp, ",");
            } else {
                fprintf(ofp, "\n");
            }
        }
    }
    digit_num=0;
    counter=0 ;
    free(clusters);
    free(sizeofclusters);
    free(centroids);
    free(oldcentroids);
    free(vectors);
    for (i = 0; i < filelength; i++) {
        free(filearr[i]);
    }
    free(filearr);
    fclose(ifp);
    fclose(ofp);
    return 0;
}
typedef enum {false, true} bool;

#ifndef HW1__KMEANS_H_
#define HW1__KMEANS_H_
typedef struct k_means {
  int k;
  int max_iter;
  char input_filename[256];
  char output_filename[256];
  double epsilon;
  double data_points[256];
  double centroids[256];
  double clusters[256][256];
  bool is_converged;
} km;
  typedef struct data_point {
    {
      1 : ((),8)
    }
  } dp;

def __init__(self, K, input_filename, output_filename, max_iter=200, epsilon=0.001):
self.K = K  # number of clusters
    self.max_iter = max_iter  # maximum number of iteration for the algorithm
self.input_filename = input_filename  # an input file with valid format of data points (text file)
self.output_filename = output_filename  # an output file to save the results into (text file)
self.epsilon = epsilon  # the accepted error
    self.data_points = dict()  # holding the data points in a dictionary
    self.initialize_data_points()  # read the given data points from the input file into the dictionary
self.centroids = dict()  # holding the centroids in a dictionary
self.initialize_centroids()  # initializing the centroids dictionary
self.clusters = dict()  # holding the clusters in a dictionary
self.initialize_clusters()  # initialize the clusters dictionary
self.is_converged = False
self.N = len(self.data_points)  # number of given data points in the input file
    self.d = len(self.data_points[1][0])  # the dimension of a data point (valid format of all points is assumed)

def initialize_data_points(self):
"""
parses the data points from the given input file and initialise the data points dictionary.
:return: None
"""
index = 1
with open(self.input_filename, 'r') as file:
for line in file:
self.data_points[index] = (tuple(line.strip().split(",")), 0)  # (x,y,z)
index += 1

def initialize_centroids(self):
"""
initialise centroids as the first k data points.
:return: None
"""
for i in range(1, self.K + 1):
self.centroids[i] = tuple(self.data_points[i][0])

def initialize_clusters(self):
"""
initializes an empty clusters dictionary.
:return: None
"""
for i in range(1, self.K + 1):
self.clusters[i] = set()

def find_closest_cluster(self, dp):
"""
finds the closest cluster to the given datapoint based on the Euclidian norm.
:param dp: the input data point
:return: the index j of the centroid that represent the closest cluster.
"""
dif = self.subtract_data_points(dp, self.centroids[1])
m = self.scalar_mult(dif, dif)
argmin = 1
for j in range(2, self.K + 1):
dif = self.subtract_data_points(dp, self.centroids[j])
f = self.scalar_mult(dif, dif)
if f < m:
argmin = j
m = f
return argmin

    def assign_to_clusters(self):
"""
:return: None
"""
for i in range(1, self.N + 1):
dp = self.data_points[i][0]
argmin = self.find_closest_cluster(dp)
self.data_points[i] = (self.data_points[i][0], argmin)  # saves the index of the closest cluster to the
# data point's dictionary item
    s = self.clusters[argmin]
s.add(dp)
self.clusters[argmin] = s

    def norm(self, dp):
return pow(self.scalar_mult(dp, dp), 0.5)

def distance(self, dp1, dp2):
return self.norm(self.subtract_data_points(dp2, dp1))

def update_centroids(self):
old_centroids = [self.centroids[i] for i in range(1, self.K + 1)]
for i in range(1, self.K + 1):
s = self.clusters[i]
if len(s) != 0:
self.centroids[i] = tuple([float(self.aggregate(s)[i]) / len(s) for i in range(self.d)])
for i in range(1, self.K + 1):
if self.distance(self.centroids[i], old_centroids[i]) >= self.epsilon:
return
self.is_converged = True

void output_centroids();


def aggregate(self, ds):
"""
sums all data points in a given data set
:param ds: data set
:return: aggregated sum of the data set
"""
s = [0 for _ in range(self.d)]
for dp in ds:
s = self.sum_data_points(s, dp)
return tuple(s)

def sum_data_points(self, dp1, dp2):
"""
sums two data points
:param dp2:
:param dp1:
:return: dp1+dp2
"""
return tuple([float(dp1[i]) + float(dp2[i]) for i in range(self.d)])

def subtract_data_points(self, dp1, dp2):
"""
subtract two data points
:param dp1:
:param dp2:
:return: dp1-dp2
"""
return tuple([float(dp1[i]) - float(dp2[i]) for i in range(self.d)])

double scalar_mult(dp1, dp2);


  void run();
#endif //HW1__KMEANS_H_
