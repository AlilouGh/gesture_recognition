#include "knn.hpp"
#include <iostream>


using namespace std;

double distanceEuclidienne(std::vector<std::complex<double>> data_vector, std::vector<std::complex<double>> prototype) {
  std::complex<double> diff;
  double distance = 0;

  for(unsigned int i =0; i < data_vector.size(); i++){
    //std::cout << "Avant" << std::endl;
    //std::cout << data_vector[i] << std::endl;
    //std::cout << prototype[i] << std::endl;
    diff = data_vector[i] - prototype[i];
    //std::cout << "Après" << std::endl;
    distance += std::norm(diff);
  }
  distance = sqrt(distance);
  return distance;
}




double distanceHamming(std::vector<std::complex<double>> data_vector, std::vector<std::complex<double>> prototype) {
  std::complex<double> diff;
  double distance = 0;

  for(unsigned int i =0; i < data_vector.size(); i++){
    //std::cout << "Avant" << std::endl;
    //std::cout << data_vector[i] << std::endl;
    //std::cout << prototype[i] << std::endl;
    diff = data_vector[i] - prototype[i];
    //std::cout << "Après" << std::endl;
    distance += std::abs(diff);
  }
  return distance;
}




double distance(std::vector<std::complex<double>> data_vector, std::vector<std::complex<double>> prototype, double n) {
  std::complex<double> diff;
  double distanc = 0;

  for(unsigned int i =0; i < data_vector.size(); i++){

    diff = data_vector[i] - prototype[i];

    distanc += pow(std::abs(diff), n);
  }

  distanc = pow(distanc, 1.0/n);
  return distanc;
}




std::vector< std::pair<double, std::string> > kClosest(std::vector<std::complex<double>> data_vector, std::map< std::string, std::vector< std::vector< std::complex<double> > > > database_map, int K, double n) {
  std::vector< std::pair<double, std::string> > dist;
  for (auto& classe : database_map) {
    for (auto& vec : classe.second) {
     double distanc = distance(data_vector, vec, n);
     dist.push_back(std::make_pair(distanc, classe.first));     
    }
  }
  std::sort(dist.begin(), dist.end());
  std::vector< std::pair<double, std::string> > result (dist.begin(), dist.begin() + K);

  return result;
}




std::string knn (std::vector<std::complex<double>> data_vector, std::map< std::string, std::vector< std::vector< std::complex<double> > > > database_map, int K, double n) {
  std::vector< std::pair<double, std::string> > closests = kClosest(data_vector, database_map, K, n);
  std::map< std::string, int> comparison;
  for (auto& it : closests) {
    if (comparison.count(it.second) > 0) {
      comparison[it.second] += 1;
    }
    else {
      comparison[it.second] = 1;
    }
  }

  std::string classe;
  int max_voisins = 0;
  for (auto& it : comparison) {
    if (it.second > max_voisins) {
      max_voisins = it.second;
      classe = it.first;
    }
  }

  return classe;
}
