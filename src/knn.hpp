#pragma once

#include <algorithm>
#include <vector>
#include <iostream>
//#include <time.h>
#include <map>
#include <complex>
#include <functional>
#include <cmath>
#include <string>

double distanceEuclidienne(std::vector<std::complex<double>> data_vector, std::vector<std::complex<double>> prototype);
double distanceHamming(std::vector<std::complex<double>> data_vector, std::vector<std::complex<double>> prototype);
double distance(std::vector<std::complex<double>> data_vector, std::vector<std::complex<double>> prototype, double n);
std::vector< std::pair<double, std::string> > kClosest(std::vector<std::complex<double>> data_vector, std::map< std::string, std::vector< std::vector< std::complex<double> > > > database_map, int K, doubles n);
std::string knn (std::vector<std::complex<double>> data_vector, std::map< std::string, std::vector< std::vector< std::complex<double> > > > database_map, int K, double n);
