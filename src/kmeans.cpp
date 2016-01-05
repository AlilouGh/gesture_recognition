#include "kmeans.hpp"

void update_clusters(std::map<int, int>& database_map, std::map <int, std::vector<std::complex<double>>> prototypes_map, std::vector<std::vector<std::complex<double>>> database){

	int label = 0;

	for(auto& it1 : database_map){

		double distance = 0.0;

		for(auto& it2 : prototypes_map){
			double d = get_distance(database[it1.first], it2.second);
			if (distance > d){
				distance = d;
				label = it2.first;				 
			}
		}

		database_map[it1.first] = label; 
	}

}

double get_distance(std::vector<std::complex<double>> data_vector, std::vector<std::complex<double>> prototype){

  //std::vector<std::complex<double>> difference;
  std::complex<double> diff = 0;
  double distance = 0;

	for(unsigned int i =0; i<data_vector.size(); i++){
		diff = data_vector[i] - prototype[i];
		//difference.push_back(diff);
		distance += std::norm(diff);
	}

	//	double distance = std::norm(difference);

	return distance;
}

std::map <int, std::vector<std::complex<double>>> update_prototypes(int nb_prototypes, std::vector<std::vector<std::complex<double>>> database, std::map <int, int> database_map){

  std::map <int, std::vector<std::complex<double>>> prototypes_map;
  int size_vec = database[0].size();
  std::vector<std::complex<double>> proto_map_init (size_vec, std::complex<double>(0,0));

  for (int i = 0; i < nb_prototypes; i++) {
    prototypes_map[i] = proto_map_init;
  }

	for(int l=0; l<nb_prototypes; l++){
		int divider = 0;
		for(auto& it : database_map){
			if(it.second == l){
			  std::transform(prototypes_map[l].begin(), prototypes_map[l].end(), prototypes_map[l].begin(), database[it.first].begin(), std::plus<std::complex<double>>());
				divider++;
			}
			std::transform(prototypes_map[l].begin(), prototypes_map[l].end(), prototypes_map[l].begin(), bind1st(std::divides<std::complex<double>>(), divider));
		}
	}
	
	return prototypes_map;
}


std::map <int, std::vector<std::complex<double>>> kmeans(std::vector<std::vector<std::complex<double>>> database, int nb_clusters, double epsilon){

	//	std::vector<std::vector<std::complex<double>>> = database;

	int k = nb_clusters;

	std::map <int, std::vector<std::complex<double>>> prototypes_map;
	std::map <int, std::vector<std::complex<double>>> final_prototypes_map;
	std::map <int, int> database_map;

	srand(time(NULL));

	int rand_label;

	for(unsigned int i=0; i<database.size(); i++){
		rand_label = rand() % k;
		database_map[i] = rand_label;
	}

	for(int l=0; l<k; ++l){
		int compt = 0;
		int divider = 0;
		for(auto& it : database){
			if(database_map[compt] == l){
			  std::transform(prototypes_map[l].begin(), prototypes_map[l].end(), prototypes_map[l].begin(), it.begin(), std::plus<std::complex<double>>());
				divider++;
			}
			compt++;
			std::transform(prototypes_map[l].begin(), prototypes_map[l].end(), prototypes_map[l].begin(), bind1st(std::divides<std::complex<double>>(), divider));
		}
	}

	final_prototypes_map = prototypes_map;

	update_clusters(database_map, prototypes_map, database);
	prototypes_map =  update_prototypes(k, database, database_map);
	
	double distance = 0;
	for (int i = 0; i < nb_clusters; i++){
	  distance += get_distance(final_prototypes_map[i], prototypes_map[i]);
	}

	while(distance > epsilon){
		update_clusters(database_map, prototypes_map, database);
		prototypes_map =  update_prototypes(k, database, database_map);
		
		for (int i = 0; i < nb_clusters; i++){
		  distance += get_distance(final_prototypes_map[i], prototypes_map[i]);
		}

		final_prototypes_map = prototypes_map;
	}

	return final_prototypes_map;

}
