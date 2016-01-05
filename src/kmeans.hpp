#pragma once

#include <algorithm>
#include <vector>
#include <iostream>
#include <time.h>
#include <map>

void update_clusters(std::map<int, int>& database_map, std::map <int, std::vector<std::complex<double>>> prototypes_map, std::vector<std::vector<std::complex<double>>> database);
	

double get_distance(std::vector<std::complex<double>> data_vector, std::vector<std::complex<double>> prototype);


std::map <int, std::vector<std::complex<double>>> update_prototypes(int nb_prototypes, std::vector<std::vector<std::complex<double>>> database, std::map <int, std::vector<std::complex<double>>> database_map);

std::map <int, std::vector<std::complex<double>>> kmeans(std::vector<std::vector<std::complex<double>> database, int nb_clusters, double epsilon);

