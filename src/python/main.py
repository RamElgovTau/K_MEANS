import sys


class KMeans:
    """
    a simple implementation of the K-Means algorithm.
    @authors: Mohammad Daghash & Ram Elgov.
    """

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

    def output_centroids(self):
        with open(self.output_filename, 'w') as file:
            line = str()
            for centroid in self.centroids.values():
                for coordinate in centroid:
                    line += str("%.4f" % float(coordinate))
                    line += ","
                file.write(line[:-1] + "\n")
                line = str()

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

    def scalar_mult(self, dp1, dp2):
        """
        preforms a scalar multiplication of two data points
        :param dp1:
        :param dp2:
        :return: the scalar multiplication of x and y
        """
        return sum([float(str(dp1[i])) * float(str(dp2[i])) for i in range(self.d)])

    def run(self):  # apply the algorithm and save the result in the output file given
        self.initialize_centroids()
        iteration = 0
        while not self.is_converged and iteration < self.max_iter:
            iteration += 1
            self.assign_to_clusters()
            self.update_centroids()
        self.output_centroids()


def main():
    def run():
        try:
            kmeans.run()
        except (Exception,):
            print("An Error Has Occurred")

    args = sys.argv[1:]  # need to add argument format validation
    if len(args) == 4:
        if (not args[0].isdigit()) or (not args[1].isdigit()) or \
                int(args[0]) <= 1 or int(args[1]) <= 0:
            print("Invalid Input!")
            sys.exit()
        kmeans = KMeans(int(args[0]), args[2], args[3], int(args[1]))
        run()
    elif len(args) == 3:
        if (not args[0].isdigit()) or int(args[0]) <= 1:
            print("Invalid Input!")
            sys.exit()
        kmeans = KMeans(int(args[0]), args[1], args[2])
        run()
    else:
        print("Invalid Input!")
        sys.exit()

    # K - need to check that it is valid integer
    # max_iter - # need to check that it is valid integer
    # input_filename = args[2]  # need to check that it is valid file name that is openable
    # output_filename = args[3]  # need to check that it is valid file name that is openable


if __name__ == "__main__":
    main()
