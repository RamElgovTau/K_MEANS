from unittest import TestCase
from main import KMeans


class TestKMeans(TestCase):
    kmeans = KMeans(3, "input_1.txt", "output.txt")

    def test_initialize_data_points(self):
        self.assertEqual(len(self.kmeans.data_points), 500)

    def test_initialize_centroids(self):
        self.kmeans.initialize_data_points()
        self.kmeans.initialize_centroids()
        for c in self.kmeans.centroids.values():
            print(c)

    def test_initialize_clusters(self):
        self.fail()

    def test_find_closest_cluster(self):
        self.fail()

    def test_assign_to_clusters(self):
        self.fail()

    def test_norm(self):
        self.assertEqual(norm([0, 0, 0]), 0.0)
        self.assertEqual(norm([1, 1, 1]), pow(3, 0.5))
        self.assertEqual(norm([0, 3, 4]), 5.0)

    def test_distance(self):
        self.fail()

    def test_update_centroids(self):
        self.fail()

    def test_output_centroids(self):
        self.fail()

    def test_aggregate(self):
        self.assertEqual(self.kmeans.aggregate({(0, 0, 0), (1, 1, 1), (2, 2, 2)}), (3.0, 3.0, 3.0))
        self.assertEqual(self.kmeans.aggregate({(0, 0, 0), (0, 0, 0), (0, 0, 0)}), (0.0, 0.0, 0.0))
        self.assertEqual(self.kmeans.aggregate({(-1.0, -1.0, -1.0), (0.0, 0.0, 0.0), (2, 2, 2)}), (1.0, 1.0, 1.0))

    def test_sum_data_points(self):
        self.fail()

    def test_subtract_data_points(self):
        self.fail()

    def test_scalar_mult(self):
        self.fail()

    def test_run(self):
        self.fail()
