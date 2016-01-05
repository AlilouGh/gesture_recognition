#include <algorithm>
#include <vector>
#include <iostream>
#include <time.h>
#include <map>

void update_clusters(std::map<int, int>& database_map, std::map <int, std::vector<std::complex<double>>> prototypes_map, std::vector<std::vector<std::complex<double>>> database){

	int label = 0;

	for(auto& it1 : database_map){

		double distance = 0.0;

		for(auto& it2 : prototypes_map){
			double d = get_distance(database[it1.first()], it2.second());
			if (distance > d){
				distance = d;
				label = it2.first();				 
			}
		}

		database_map[it1.first()] = label; 
	}

}

double get_distance(std::vector<std::complex<double>> data_vector, std::vector<std::complex<double>> prototype){

	std::vector<stdcomplex<double>> difference;
	int diff = 0;

	for(int i =0; i<data_vector.size(); i++){
		diff = data_vector[i] - prototype[i];
		difference.pushback(diff);
	}

	double distance = std::norm(difference);

	return distance;
}

std::map <int, std::vector<std::complex<double>>> update_prototypes(int nb_prototypes, std::vector<std::vector<std::complex<double>>> database, std::map <int, std::vector<std::complex<double>>> database_map){

	std::map <int, std::vector<std::complex<double>>> prototypes_map;

	for(int l=0; l<nb_prototypes; l++){
		int divider = 0;
		for(auto& it : database_map){
			if(it.second() == l){
				std::transform(prototype_map[l].second.begin(), prototypes_map[l].second.end(), prototypes_map[l].second.begin(), database[it.first()].begin(), std::plus<std::complex>());
				divider++;
			}
			std::transform(prototypes_map[l].second.begin(), prototypes_map[l].second.end(), prototypes_map[l]second.begin(), bind1st(divides<std::complex>(), divider));
		}
	}
	
	return prototypes_map;
}


std::map <int, std::vector<std::complex<double>>> kmeans(std::vector<std::vector<std::complex<double>> database, int nb_clusters, double epsilon){

	//	std::vector<std::vector<std::complex<double>>> = database;

	int k = nb_clusters;
	double epsilon = epsilon;

	std::map <int, std::vector<std::complex<double>>> prototypes_map;
	std::map <int, std::vector<std::complex<double>>> final_rototypes_map;
	std::map <int, int> database_map;

	srand(time(NULL));

	int rand_label;

	for(int i=0; i<database.size(); i++){
		rand_label = rand() % k;
		database_map[i] = rand_label;
	}

	for(int l=0; l<k; ++l){
		int compt = 0;
		int divider = 0;
		for(auto& it : database){
			if(database_map[compt].second() == l){
				td::transform(prototype_map[l].second.begin(), prototypes_map[l].second.end(), prototypes_map[l].second.begin(), it.begin(), std::plus<std::complex>());
				divider++;
			}
			compt++;
			std::transform(prototypes_map[l].second.begin(), prototypes_map[l].second.end(), prototypes_map[l]second.begin(), bind1st(divides<std::complex>(), divider));
		}
	}

	final_prototypes_map = prototypes_map;

	update_clusters(database_map, prototypes_map, database);
	prototypes_map =  update_prototypes(k, database, database_map);
	finale = f(final_prototypes_map);
	current = f(prototypes_map);

	while(finale - current > epsilon){
		update_clusters(database_map, prototypes_map, database);
		prototypes_map =  update_prototypes(k, database, database_map);
		finale = f(final_prototypes_map);
		current = f(prototypes_map);
		final_prototypes_map = prototypes_map;
	}

	return final_prototypes_map;

}
