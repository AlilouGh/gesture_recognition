#include <opencv2/opencv.hpp>
#include <algorithm>
#include <vector>
#include <complex>
#include <utility>
#include <iostream>
#include <functional>
#include "feature_extraction.hpp"
#include "kmeans.hpp"
#include "kmeans_input.hpp"
#include <random>

int main(int, char**)
{
  /*std::complex<double> comp(1, 1);
  std::vector<std::vector<std::complex<double>>> vec_test;
  std::vector<std::complex<double>> vec1 (50, comp);
  std::vector<std::complex<double>> vec2 (50, comp);

  vec_test.push_back(vec1);
  vec_test.push_back(vec2);

  std::map <int, std::vector<std::complex<double>>> map_test = kmeans(vec_test, 2, 0.1);*/

  std::vector<std::vector<std::complex<double>>> database = kmeans_input(10);
  auto engine = std::default_random_engine{};
  std::shuffle(std::begin(database), std::end(database), engine);

  std::map <int, std::vector<std::complex<double>>> data_map = kmeans(database, 4, 50);
  }
