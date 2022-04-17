#include <stdio.h>
#include "Kmeans.h"
#include "math.h"
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

