#include "kmeans.hpp"
#include <chrono>
#include <thread>
#include "descripteur_fourier.hpp"
#include "traitement.hpp"
#include "feature_extraction.hpp"

void update_clusters(std::map<int, int>& database_map, std::map <int, std::vector<std::complex<double>>> prototypes_map, std::vector<std::vector<std::complex<double>>> database){

	int label = 0;

	for(auto& it1 : database_map){

		double distance = std::numeric_limits<double>::max();

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
	std::complex<double> diff;
	double distance = 0;

	for(unsigned int i =0; i < data_vector.size(); i++){
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
		int divider = 1;
		for(auto& it : database_map){
			if(it.second == l){
				std::transform(prototypes_map[l].begin(), prototypes_map[l].end(), database[it.first].begin(), prototypes_map[l].begin(), std::plus<std::complex<double>>());
				divider++;
			}
		}

		std::vector<std::complex<double>> div_vector;

		if (divider == 1){
			div_vector = std::vector<std::complex<double>>(prototypes_map[l].size(), std::complex<double>(divider));
		}else{
			div_vector = std::vector<std::complex<double>>(prototypes_map[l].size(), std::complex<double>(divider-1));
		}

		std::transform(prototypes_map[l].begin(), prototypes_map[l].end(), div_vector.begin(), prototypes_map[l].begin(), std::divides<std::complex<double>>());

	}

	return prototypes_map;
}


std::map <int, std::vector<std::complex<double>>> kmeans(std::vector<std::vector<std::complex<double>>> database, int nb_clusters, double epsilon){

	//std::cout << "epsilon = " << epsilon << std::endl;
	//std::cout << "taille database = " << database.size() << std::endl;
	//std::this_thread::sleep_for(std::chrono::milliseconds(500));
	//	std::vector<std::vector<std::complex<double>>> = database;

	int k = nb_clusters;

	std::map <int, std::vector<std::complex<double>>> prototypes_map;
	std::map <int, std::vector<std::complex<double>>> final_prototypes_map;
	std::map <int, int> database_map;

	// *********** Initialization ************//
	std::vector< cv::Mat > vect_frames;
	cv::Mat frame;
	cv::Mat frame_conv;
	std::vector < std::vector< cv::Point > > contours;

	int c_max = 10;

	std::vector < std::vector<std::complex<double> > > vect_coeff;

	frame = cv::imread("/home/ghezali/Documents/supelec/sir/tl_gesture_command/database/2016-01-27-150243_12.jpg");
	vect_frames.push_back(frame);

	frame = cv::imread("/home/ghezali/Documents/supelec/sir/tl_gesture_command/database/2016-01-27-150430_8.jpg");
	vect_frames.push_back(frame);

	frame = cv::imread("/home/ghezali/Documents/supelec/sir/tl_gesture_command/database/2016-01-27-150649_4.jpg");
	vect_frames.push_back(frame);

	frame = cv::imread("/home/ghezali/Documents/supelec/sir/tl_gesture_command/database/2016-01-27-150833_14.jpg");
	vect_frames.push_back(frame);

	for (auto& it : vect_frames){
		segmentation(it);
		cv::cvtColor(it, frame_conv, CV_RGB2GRAY);
		cv::findContours(frame_conv, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		contours = find_longest_contour(contours);
		vect_coeff.push_back(descripteur_fourier_normal(contours, c_max));
	}

	for(unsigned int k = 0; k < vect_coeff.size(); k++){
		prototypes_map[k] = vect_coeff[k];
	}


	for (auto& it1 : prototypes_map){
		std::cout << "prototype" << it1.first << " :" << std::endl;
		for (auto& it2 : it1.second){
			std::cout << it2 << std::endl;
		}
	}

	srand(time(NULL));

	int rand_label;

	for(unsigned int i=0; i<database.size(); i++){
		rand_label = rand() % k;
		database_map[i] = rand_label;
	}

	final_prototypes_map = prototypes_map;

	update_clusters(database_map, prototypes_map, database);
	prototypes_map =  update_prototypes(k, database, database_map);

	double distance = 0;
	for (int i=0; i<k ; i++){
		distance += get_distance(final_prototypes_map[i], prototypes_map[i]);
	}

	int compteur = 1;
	std::cout << "loop 0 : " << distance << std::endl; 

	double last_distance = 100;

	while(std::abs(last_distance - distance) > epsilon){

		std::cout << "loop" << compteur << " : " << distance << std::endl; 

		last_distance = distance;

		distance = 0;

		update_clusters(database_map, prototypes_map, database);

		prototypes_map =  update_prototypes(k, database, database_map);

		for (int i = 0; i < nb_clusters; i++){
			distance += get_distance(final_prototypes_map[i], prototypes_map[i]);
		}

		final_prototypes_map = prototypes_map;
		compteur++;
	}

	std::cout << "last loop : " << distance-last_distance << " < " << epsilon << std::endl; 

	return final_prototypes_map;

}
