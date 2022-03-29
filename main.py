import sys


class KMeans:

    def __init__(self, K, input_filename, output_filename, max_iter = 200, epsilon=0.001):
        self.K = K
        self.max_iter = max_iter
        self.input_filename = input_filename
        self.output_filename = output_filename
        self.epsilon = epsilon
        self.data_points = dict()
        self.initialize_data_points()  # read the given data points from the input file into a dictionary
        self.centroids = dict()
        self.initialize_centroids()
        self.clusters = dict()
        self.initialize_clusters()
        self.N = len(self.data_points)
        self.d = len(self.data_points[1])

    def initialize_data_points(self):
        index = 1
        with open(self.input_filename, 'r') as file:
            for line in file:
                self.data_points[index] = tuple(line.strip().split(","))  # (x,y,z)
                index += 1

    def initialize_centroids(self):
        for i in range(1, self.K + 1):
            self.centroids[i] = self.data_points[i]

    def initialize_clusters(self):
        for centroid in self.centroids:
            self.clusters[centroid] = set()

    def assign_to_clusters(self):
        argmin = 9223372036854775807
        argmin_i = 0
        for i in range(1, self.N + 1):
            for j in range(1, self.K + 1):
                curr_closest = (self.data_points[i] - self.centroids[j]) ** 2  # need t
                if curr_closest < argmin:
                    argmin = curr_closest
                    argmin_i = self.centroids[j]
            argmin = 9223372036854775807
            self.clusters[argmin_i].add(self.data_points[i])

    def update_centroids(self):
        recently_changed = [0]*self.K
        for i in range(1, self.K + 1):
            length = 0
            for xl in self.clusters[i]:
                sum += xl
                length += 1
            sum = 0
            recently_changed[i] = self.centroids[i]
            self.centroids[i] = sum\length

    def is_converged(self):  # checks the convergence criteria
        for i in range(1, self.K + 1):
            if abs(self.centroids[i] - recently_changed[i]) >= 0.001
                return False
        return True


    def output_centroids(self):
        with open(self.output_filename, 'w') as file:
            line = str()
            for centroid in self.centroids:
                for coordinate in centroid:
                    line = line + str("%.4f" % coordinate) + ","
                file.write(line[:-1])
                line = str()
    def sum_vectors(self, x,y):
        """

        :param x:
        :param y:
        :return: the vector x+y
        """
        pass

    def subtract_vectors(self, x,y):
        """
        :param x:
        :param y:
        :return: the vector x-y
        """
        pass

    def scalar_mult(self,x,y):
        """

        :param x:
        :param y:
        :return: the scalar multiplication of x and y
        """
        pass

    def run(self):  # apply the algorithm and save the result in the output file given
        self.initialize_centroids()
        iteration = 0
        while not self.is_converged() and iteration < self.max_iter:
            iteration += 1
            self.assign_to_clusters()
            self.update_centroids()
            self.output_centroids()


def main():
    args = sys.argv[1:]  # need to add argument format validation
    kmeans = KMeans(int(args[0]), args[2], args[3], int(args[1]))
    # K - need to check that it is valid integer
    # max_iter - # need to check that it is valid integer
    # input_filename = args[2]  # need to check that it is valid file name that is openable
    # output_filename = args[3]  # need to check that it is valid file name that is openable
    kmeans.run()


if __name__ == "__main__":
    main()
