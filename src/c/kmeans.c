/*********************************************
 @author: ram elgov
 @id: 20667517
 @author: mohammad daghash
 @id: 314811290
 **********************************************/
#include "stdlib.h"
#include "stdio.h"
#include "errno.h"
#include "math.h"
#include "string.h"
#define NDEBUG ;

/*Constants*/
long const MAX_ITER = 200;
double const EPSILON_SQUARED = 0.000001;

/***************************************************************
   * A data structure that represents a KMEANS algorithm object.
   *************************************************************/
typedef struct kmeans {
  long n, d, k, max_iter;  /* n is the number of data points, d is the dimension of each vector in the algorithm */
  /* k is the number of required clusters. */
  long* sizeof_clusters; /* array to hold the sizes of all clusters */
  double **data_points, **centroids, **old_centroids, **clusters;
  char* input_file_name, *output_file_name;
} kmeans;

/* algorithm components */
long find_closest_cluster_to(double *data_point, kmeans* km);
void assign_to_clusters(kmeans* km);
void update_centroids(kmeans* km);
void output_results(kmeans* km);
void run(kmeans *km);

/* input validations */
void invalid_input();
void general_error();

/******************
 *
 * constructor
 *
 ******************/
/**
* a constructor for initializing the kmeans object.
* @param km
* @param k
* @param max_iter
* @param input_file_name
* @param output_file_name
*/
void construct_kmeans(kmeans* km, int k, int max_iter, char* input_file_name, char* output_file_name);
/**
 * calculates the parameters d - the dimension of each data point and n - the number of data points in the file.
 * @param km
 * @return int[2] array s.t d = array[0] and n = array[1]
 */
int* calculate_d_n(kmeans *km, int *dn);
/*  memory allocation and free */
void allocate(long **arr, int n);
void allocate2d(double *** mat, int rows, int cols);
void free2d(double***mat,int rows){
  int i;
  for(i = 0; i < rows; ++i) {
    free((*mat)[i]);
  }
  free(**mat);
}
void freeAll(kmeans* km){
  /* assumes kmeans object is initialized. */
  free2d(&km->centroids,km->k);
  free2d(&km->old_centroids,km->k);
  free2d(&km->data_points, km->n);
  free2d(&km->clusters, km->k);
  free(km->sizeof_clusters);
  free(km);
}
/* initializations */
/**
 * extract the data points from the input file and saves them to the data_points matrix.
 * @pre: d and n are initialized.
 * @post: data_points is initialized with the data from the input file.
 * @param km
 */
void initialize_data_points(kmeans *km);
void initialize_centroids(kmeans *km);
void empty_clusters(kmeans *km);
void save_old_centroids(kmeans *km);
/* calculations */
/**
 * Calculates the squared Euclidian distance between the two input vectors.
 * @param km the kmeans object
 * @return ||v1-v2||^2
 */
double distance_squared(double *v1, double *v2, int n);
int is_converged(kmeans *km);

/* algorithm components */
long find_closest_cluster_to(double *data_point, kmeans* km){
/**
 * calculates the current closest cluster to the given data point vector,
 * using variance minimization.
 * @return the index of the closest cluster
 */
  double min = 0,sum;
  int i, j;
  long index = 0;
  for (i = 0; i < km->d; ++i) {
    min += pow((data_point[i]) - km->centroids[0][i], 2);
  }
  for (i = 1; i < km->k; ++i) {
    sum = 0;
    for (j = 0; j < km->d; j++) {
      sum += pow(data_point[j] - km->centroids[i][j], 2);
    }
    if (sum < min) {
      min = sum;
      index = i;
    }
  }
  return index;
}
void assign_to_clusters(kmeans* km) {
/**
 * updates the clusters array with the matched data points.
 * @return nothing
 */
  int i, j;
  /* initialize clusters */
  empty_clusters(km);
  for (i = 0; i < km->n; i++) {
    int index = find_closest_cluster_to(km->data_points[i], km);
    for ( j = 0; j < km->d; j++) { /* add to the closest cluster */
      km->clusters[index][j] += km->data_points[i][j];
    }
    km->sizeof_clusters[index]++;
  }
}

/**
 * recalculates centroids.
 * @return nothing
 */
void update_centroids(kmeans* km) {
  int i,j;
    for (i = 0; i < km->k; i++) {
      for (j = 0; j < km->d; j++) {
        km->centroids[i][j] = km->clusters[i][j] / km->sizeof_clusters[j];
      }
    }
}
/**
* outputs the final centroids to a given file.
* @return nothing
*/
void output_results(kmeans* km){
  FILE *file;
  int i,j;
  file = fopen(km->output_file_name, "w");
  if(file == NULL || errno != 0) {
    printf("error in output results \n");
    general_error();
  }
  for (i = 0; i < km->k; i++) {
    for (j = 0; j < km->d; j++) {
      fprintf(file, "%.4f", km->centroids[i][j]);
      if (j < km->d - 1) {
        fprintf(file, ",");
      } else {
        fprintf(file, "\n");
      }
    }
  }
  fclose(file);
}

/**
* runs the algorithm on the given kmeans object.
* @return nothing
*/
void run(kmeans* km){
  int i;
  for (i = 0; i < km->max_iter ; ++i) {
    if(is_converged(km)){
      output_results(km);
      return;
    }
    assign_to_clusters(km);
    save_old_centroids(km);
    update_centroids(km);
  }
  output_results(km);
}


/* input validations */
void invalid_input(){
  printf("Invalid Input!");
  exit(1);
}
void general_error() {
  printf("An Error Has Occurred");
  exit(1);
}

/* constructor */
int* calculate_d_n(kmeans *km, int *dn){
  FILE *file = NULL;
  int d = 1, n = 1;
  char c;
  printf("the input file name is: %s\n", km->input_file_name);
  file = fopen(km->input_file_name, "r");
  if(file == NULL || errno != 0){
    printf("error in calculate_d_n: can not open input file.");
    general_error();
  }
  while ((c = fgetc(file)) != '\n') {
    if (c == ',')
      ++d;
  }

  rewind(file);
  while ((c = fgetc(file)) != EOF)
    if(c == '\n')
      ++n;
  fclose(file);
  dn[0] = d;
  dn[1] = n;
  return dn;
}
void allocate2d(double ***mat, int rows, int cols) {
  int i;
  *mat = malloc((rows) * sizeof(double *));
  if(*mat == NULL || errno != 0) {
    printf("error in allocate2d: cannot allocate memory for rows.");
    general_error();
  }
  for (i = 0; i < rows; ++i) {
    (*mat)[i] = malloc(cols * sizeof(double));
    if(((*mat)[i]) == NULL || errno != 0){
      printf("error in allocate2d: cannot allocate memory for cols.");
      general_error();
    }
  }
}
void allocate(long **arr, int n){
  *arr = malloc(n * sizeof(double));
  if(*arr == NULL || errno != 0){
    printf("error in allocate: cannot allocate memory for array.");
    general_error();
  }
}
void initialize_data_points(kmeans *km){
  FILE *file;
  double vec;
  int i, j;
  file = fopen(km->input_file_name, "r");
  if(file == NULL || errno != 0) {
    perror("error: ");
    printf("error in initialize_data_points: cannot open file.");
    general_error();
  }
  for (i = 0; i < km->n; i++) {
    for (j = 0; j < km->d; j++) {
      fscanf(file, "%lf%*c", &vec);
      km->data_points[i][j] = vec;
    }
  }
  fclose(file);
}
void initialize_centroids(kmeans *km){
  int i,j;
  for(i = 0; i < km->k; i++){
    for(j = 0; j < km->d; j++){
      km->centroids[i][j] = km->data_points[i][j];
    }
  }
}
void initialize_sizeof_clusters(kmeans *km){
  int i;
  for (i = 0; i < km->k; ++i) {

  }
}
void construct_kmeans(kmeans* km, int k, int max_iter, char* input_file_name, char* output_file_name){
  int *dn, size_prefix1, size_prefix2;
  char *prefix1, *prefix2;
  km->k = k;
  km->max_iter = max_iter;

  size_prefix1 = strlen(input_file_name);
  size_prefix2 = strlen(output_file_name);
  prefix1 = malloc((size_prefix1 + 4) * sizeof (char));
  /*check that allocation succeed and free memory!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
  prefix2 = malloc((size_prefix2 + 4) * sizeof (char));
  prefix1[0] = '.';
  prefix1[1] = '.';
  prefix1[2] = '/';
  prefix2[0] = '.';
  prefix2[1] = '.';
  prefix2[2] = '/';
  dn = malloc(2 * sizeof (int));
  if(dn == NULL){
    general_error();
  }

//  strcat(prefix1, input_file_name);
//  strcat(prefix2, output_file_name);
  km->input_file_name = prefix1;
  km->output_file_name = prefix2;

  dn = calculate_d_n(km, dn);
  km->d = dn[0];
  km->n = dn[1];
  /* memory allocation */
  allocate2d(&km->data_points, km->n, km->d);
  allocate2d(&km->centroids, km->k, km->d);
  allocate2d(&km->old_centroids, km->k, km->d);
  allocate2d(&km->clusters, km->k, km->d);
  allocate(&km->sizeof_clusters, km->k);

/* initializations */
  initialize_data_points(km);
  initialize_centroids(km);
}
void empty_clusters(kmeans *km){
  int i,j;
  /* empty clusters */
  for (i = 0; i < km->k; ++i) {
    for (j = 0; j < km->d; ++j) {
      km->clusters[i][j] = 0;
    }
  }
  /* empty sizeof_clusters */
  for (j = 0; j < km->k; j++) {
    km->sizeof_clusters[j] = 0;
  }
}
void save_old_centroids(kmeans *km) {
  int i, j;
  for (i = 0; i < km->k; i++) {
    for (j = 0; j < km->d; j++)
      km->old_centroids[i][j] = km->centroids[i][j];
  }
}
/* calculations on vectors */
int is_converged(kmeans *km){
  int i;
  for (i = 0; i < km->k; i++)
    if (distance_squared(km->centroids[i], km->old_centroids[i], km->d) >= EPSILON_SQUARED)
      return 0;
  return 1;
}
double distance_squared(double *v1, double *v2, int d){
  double dist = 0.0;
  int i;
  /* implement scalr multiplication to calculate the norm of the difference. */
  for(i = 0; i < d; ++i)
    dist += pow(v1[i] - v2[i], 2);
  return dist;
}
/* main */
int main(int argc, char* argv[]) {
  char *k_ptr, *max_iter_ptr;
  long max_iter = MAX_ITER, k;
  kmeans *km;
  printf("hello from main!");
  km = malloc(sizeof (kmeans));
  if(km == NULL) {
    printf("error in main: cannot allocate memory for km object.");
    general_error();
  }
  if(!((argc == 4) || (argc == 5)))
    /* input must be of the form (k, max_iter, input_file_name, output_file_name) */
    /* or (k, max_iter, input_file_name, output_file_name) */
    invalid_input();
  /* extract k */
  k = strtol(argv[1], &k_ptr, 10);
  if(k < 1 || errno != 0 || *k_ptr != '\0')
    invalid_input();
  if(argc == 5){
    /* if max_iter argument passed by the user */
    max_iter = strtol(argv[2], &max_iter_ptr, 10);
    if(max_iter < 1 || errno != 0 || *max_iter_ptr != '\0')
      invalid_input();
  }

  construct_kmeans(km,k, max_iter, argv[argc-2], argv[argc-1]);
  run(km);
  freeAll(km); /* check if more * is needed because of call by value */
  km = NULL;
  return 0;
}
