import sys
import math

"""
@author: mohammad daghash
@id: 314811290
@author: ram elgov
@id: 206867517
"""


def scalar_mult(dp1, dp2):
    """
    preforms a scalar multiplication of two data points
    :param dp1:
    :param dp2:
    :return: the scalar multiplication of x and y
    """
    return sum(float(dp1[i] * float(dp2[i])) for i in range(len(dp1)))


def norm(dp):
    return math.sqrt(scalar_mult(dp, dp))


def sum_data_points(dp1, dp2):
    """
    sums two data points
    :param dp2:
    :param dp1:
    :return: dp1+dp2
    """
    return tuple([float(dp1[i]) + float(dp2[i]) for i in range(len(dp1))])


def subtract_data_points(dp1, dp2):
    """
    subtract two data points
    :param dp1:
    :param dp2:
    :return: dp1-dp2
    """
    return sum_data_points(dp1, [-float(dp2[i]) for i in range(len(dp1))])


def distance(dp1, dp2):
    return norm(subtract_data_points(dp2, dp1))


def general_error():
    print("An Error Has Occurred")
    sys.exit()


class KMeans:
    """
    a simple implementation of the K-Means algorithm.
    @authors: Mohammad Daghash & Ram Elgov.
    """

    def __init__(self, K, input_filename, output_filename, max_iter=200, epsilon=0.000001):
        self.K = K  # number of clusters
        self.max_iter = max_iter  # maximum number of iteration for the algorithm
        self.input_filename = input_filename  # an input file with valid format of data points (text file)
        self.output_filename = output_filename  # an output file to save the results into (text file)
        self.epsilon = epsilon  # the accepted error
        self.data_points = []  # holding the data points in a dictionary
        self.initialize_data_points()  # read the given data points from the input file into the dictionary
        self.d = len(self.data_points[0])
        self.N = len(self.data_points)
        if self.K > self.N:
            invalid_input()
        self.centroids = []  # holding the centroids in a dictionary
        self.old_centroids = []
        self.initialize_centroids()  # initializing the centroids dictionary
        self.clusters = []  # holding the clusters in a dictionary
        self.initialize_clusters()  # initialize the clusters dictionary
        self.is_converged = False

    def initialize_data_points(self):
        """
        parses the data points from the given input file and initialise the data points dictionary.
        :return: None
        """

        with open(self.input_filename, 'r') as file:
            s = file.readline().strip().split(",")
            file.seek(0, 0)
            self.data_points = [[float(line.strip().split(",")[i]) for i in range(len(s))]
                                for line in file]

    def initialize_centroids(self):
        """
       initialise centroids as the first k data points.
       :return: None
       """
        self.centroids = [self.data_points[i] for i in range(self.K)]

    def initialize_clusters(self):
        """
        initializes an empty clusters dictionary.
        :return: None
        """
        self.clusters = [set() for _ in range(self.K)]

    def aggregate(self, ds):
        """
            sums all data points in a given data set
            :param ds:
            :param self: data set
            :return: aggregated sum of the data set
            """
        s = [0 for _ in range(self.d)]
        for dp in ds:
            s = sum_data_points(s, dp)
        return tuple(s)

    def find_closest_cluster(self, dp):
        """
        finds the closest cluster to the given datapoint based on the Euclidian norm.
        :param: dp the input data point
        :return: the index j of the centroid that represent the closest cluster.
        """
        dif = subtract_data_points(dp, self.centroids[0])
        m = norm(dif)
        argmin = 0
        for j in range(1, self.K):
            dif = subtract_data_points(dp, self.centroids[j])
            f = norm(dif)
            if f < m:
                argmin = j
                m = f
        return argmin

    def assign_to_clusters(self):
        """
        :return: None
        """
        self.initialize_clusters()
        for i in range(self.N):
            dp = tuple(self.data_points[i])
            argmin = self.find_closest_cluster(dp)
            self.clusters[argmin].add(dp)

    def update_centroids(self):
        for i in range(self.K):
            s = self.clusters[i]
            agg = self.aggregate(s)
            self.centroids[i] = tuple([(agg[i] / len(s)) for i in range(self.d)])

    def output_centroids(self):
        with open(self.output_filename, 'w') as file:
            line = str()
            for centroid in self.centroids:
                for coordinate in centroid:
                    line += str("%.4f" % float(coordinate))
                    line += ","
                file.write(line[:-1] + "\n")
                line = str()

    def check_convergence(self):
        for i in range(self.K):
            if distance(self.centroids[i], self.old_centroids[i]) >= self.epsilon:
                self.is_converged = False
                break
            else:
                self.is_converged = True

    def run(self):  # apply the algorithm and save the result in the output file given
        for _ in range(self.max_iter):
            if self.is_converged:
                self.output_centroids()
                return
            self.assign_to_clusters()
            self.old_centroids = [centroid for centroid in self.centroids]
            self.update_centroids()
            self.check_convergence()
        self.output_centroids()


def run(kmeans):
    try:
        kmeans.run()
    except (Exception,):
        general_error()


def invalid_input():
    print("Invalid Input!")
    sys.exit()


def main():
    args = sys.argv[1:]  # need to add argument format validation
    if len(args) == 4:
        if (not args[0].isdigit()) or (not args[1].isdigit()) or \
                int(args[0]) <= 1 or int(args[1]) <= 0:
            invalid_input()
        kmeans = KMeans(int(args[0]), args[2], args[3], int(args[1]))
        run(kmeans)
    elif len(args) == 3:
        if (not args[0].isdigit()) or int(args[0]) <= 1:
            invalid_input()
        kmeans = KMeans(int(args[0]), args[1], args[2])
        run(kmeans)
    else:
        invalid_input()


if __name__ == "__main__":
    main()
