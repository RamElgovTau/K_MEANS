//
// Created by ram on 10/04/2022.
//

#ifndef C__KMEANS_DS_H_
#define C__KMEANS_DS_H_
typedef enum {false, true} bool; // boolean type
typedef struct k_means {
  /**
   * a data structure for a Kmeans object relevant data.
   * @field: k
   * @field: max_iter
   * @field: input_filename
   * @field: output_filename
   * @field: epsilon
   * @field: data_points
   * @field: centroids
   * @field: clusters
   * @field: is_converged
   */
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
  double * vector;
  int cci; // closest centroid index
} dp;
#endif //C__KMEANS_DS_H_
