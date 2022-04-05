//
// Created by ram on 04/04/2022.
//
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
