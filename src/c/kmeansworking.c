#include <stdio.h>
#include<malloc.h>
#include<math.h>
#include <stdlib.h>
#include <string.h>
int norm(double *centroids, double *oldcentroids, int K, int veclength) {
    int i = 0;
    int c = 0;
    int j = 0;
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

int min(double *x, double *centroids, int K, int veclength) {
    double min = 0;
    double sum;
    int j = 0;
    int i = 0;
    int index = 0;
    for (i = 0; i < veclength; i++) {
        min += pow(x[i] - centroids[i], 2);
    }
    for (j = 0; j < K; j++) {
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
    int filelength = 0;
    int veclength = 0;
    int iterationnum = 0;
    int valid = 1;
    int i = 0;
    int j = 0;
    int maxiter;
    int K;
    int digitnum;
    int counter;
    double *vectors;
    double **filearr;
    double *centroids;
    double *oldcentroids;
    double *clusters;
    int *sizeofclusters;
    if (argc == 5) {
        K = atoi(argv[1]);
        maxiter = atoi(argv[2]);
        ifp = fopen(argv[3], "r");
        ofp = fopen(argv[4], "w");
    } else {
        K = atoi(argv[1]);
        maxiter = 200;
        ifp = fopen(argv[2], "r");
        ofp = fopen(argv[3], "w");
    }
    if(K<=1 || maxiter<=0){
        printf("Invalid Input!");
        return 1;
    }
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
    if(K>=filelength){
        printf("Invalid Input!");
        return 1;
    }
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
    iterationnum = 0;
    valid = 1;
    while (iterationnum < maxiter && valid == 1) {
        for (i = 0; i < K * veclength; i++) {
            oldcentroids[i] = centroids[i];
        }
        for (i = 0; i < filelength; i++) {
            int index = min(filearr[i], centroids, K, veclength);
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
        valid = norm(centroids, oldcentroids, K, veclength);
        iterationnum++;
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
    digitnum=0;
    counter=0 ;
    digitnum=strlen(argv[1]);
    for(i=0;i<digitnum;i++){
        if((((int)(argv[1][i])-48)<=9) && (((int)(argv[1][i])-48)>=0)){
            counter++;
        }
    }
    if(digitnum!=counter){
        printf("Invalid Input!");
        return 1;
    }
    digitnum=0;
    counter=0 ;
    if(argc==5){
        digitnum=strlen(argv[2]);
        for(i=0;i<digitnum;i++){
            if((((int)(argv[2][i])-48)<=9) && (((int)(argv[2][i])-48)>=0)){
                counter++;
            }
        }
        if(digitnum!=counter){
            printf("Invalid Input!");
            return 1;
        }
    }
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