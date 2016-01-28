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
#include "descripteur_fourier.hpp"
#include "traitement.hpp"
#include <climits>
#include <fstream>

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
	//auto engine = std::default_random_engine{};
	//std::shuffle(std::begin(database), std::end(database), engine);
	//	std::vector<std::vector<std::complex<double>>> test_database (database.begin(), database.begin() + 10);
	std::vector<std::vector<std::complex<double>>> test_database = database;
	/*
	   for(auto& it : test_database){
	   for (auto& it2 : it){
	   std::cout << it2 << std::endl;
	   } 
	   }
	 */

	std::map <int, std::vector<std::complex<double>>> data_map = kmeans(test_database, 4, 1e-5);

	std::ofstream out("database.txt");
	for (auto& it1 : data_map){
   		 for (auto& it2 : it1.second){
             out << it2 << " ";
         } 
		 out << "prototype" << it1.first << std::endl;

     }

	out.close();

	std::vector< cv::Mat > vect_frames;
	cv::Mat frame;
	cv::Mat frame_conv;
	std::vector < std::vector< cv::Point > > contours;

	int c_max = 10;

	std::vector < std::vector<std::complex<double> > > vect_coeff;
/*
	frame = cv::imread("/home/ghezali/Documents/supelec/sir/tl_gesture_command/Base_de_donnees/Vers_la_droite/2015-10-20-094225_138.jpg");
	vect_frames.push_back(frame);

	frame = cv::imread("/home/ghezali/Documents/supelec/sir/tl_gesture_command/Base_de_donnees/Vers_la_droite/2015-10-20-094225_58.jpg");
	vect_frames.push_back(frame);
*/	
	frame = cv::imread("/home/ghezali/Documents/supelec/sir/tl_gesture_command/database/2016-01-27-150243_1.jpg");
	vect_frames.push_back(frame);

	frame = cv::imread("/home/ghezali/Documents/supelec/sir/tl_gesture_command/database/2016-01-27-150430_8.jpg");
	vect_frames.push_back(frame);

	frame = cv::imread("/home/ghezali/Documents/supelec/sir/tl_gesture_command/database/2016-01-27-150649_4.jpg");
	vect_frames.push_back(frame);

	frame = cv::imread("/home/ghezali/Documents/supelec/sir/tl_gesture_command/database/2016-01-27-150833_8.jpg");
	vect_frames.push_back(frame);



	frame = cv::imread("/home/ghezali/Documents/supelec/sir/tl_gesture_command/database/2016-01-27-150243_10.jpg");
	vect_frames.push_back(frame);

	frame = cv::imread("/home/ghezali/Documents/supelec/sir/tl_gesture_command/database/2016-01-27-150243_12.jpg");
	vect_frames.push_back(frame);
	
	frame = cv::imread("/home/ghezali/Documents/supelec/sir/tl_gesture_command/database/2016-01-27-150243_14.jpg");
	vect_frames.push_back(frame);

	frame = cv::imread("/home/ghezali/Documents/supelec/sir/tl_gesture_command/database/2016-01-27-150243_16.jpg");
	vect_frames.push_back(frame);

	frame = cv::imread("/home/ghezali/Documents/supelec/sir/tl_gesture_command/database/2016-01-27-150243_18.jpg");
	vect_frames.push_back(frame);

	frame = cv::imread("/home/ghezali/Documents/supelec/sir/tl_gesture_command/database/2016-01-27-150243_20.jpg");
	vect_frames.push_back(frame);

	frame = vect_frames[1];
	segmentation(frame);
	cv::cvtColor(frame, frame_conv, CV_RGB2GRAY);
	cv::imwrite("/home/ghezali/Documents/supelec/sir/tl_gesture_command/test1.png", frame);
	
	frame = vect_frames[2];
	segmentation(frame);
	cv::cvtColor(frame, frame_conv, CV_RGB2GRAY);
	cv::imwrite("/home/ghezali/Documents/supelec/sir/tl_gesture_command/test2.png", frame);		

	frame = vect_frames[3];
	segmentation(frame);
	cv::cvtColor(frame, frame_conv, CV_RGB2GRAY);
	cv::imwrite("/home/ghezali/Documents/supelec/sir/tl_gesture_command/test3.png", frame);
	
	frame = vect_frames[4];
	segmentation(frame);
	cv::cvtColor(frame, frame_conv, CV_RGB2GRAY);
	cv::imwrite("/home/ghezali/Documents/supelec/sir/tl_gesture_command/test4.png", frame);

	for (auto& it : vect_frames){
		segmentation(it);
		cv::cvtColor(it, frame_conv, CV_RGB2GRAY);
		cv::findContours(frame_conv, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		contours = find_longest_contour(contours);
		vect_coeff.push_back(descripteur_fourier_normal(contours, c_max));
	}

	/*
	   segmentation(frame);
	   std::vector<std::vector<cv::Point>> contours;                                          // variable dans laquelle on récupèrera la liste des contours
	   cv::Mat frame_conv;                                                                    // variable qui va contenir l'image en nuances de gris
	   cv::cvtColor(frame, frame_conv, CV_RGB2GRAY);                                          // conversion de l'image courante en couleur en niveaux de gris
	   cv::findContours(frame_conv, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	   contours = find_longest_contour(contours);

	   std::vector<std::complex<double>> coeff = descripteur_fourier_normal(contours, c_max);
	 */

	for (auto& it1 : data_map){
		std::cout << "prototype" << it1.first << " :" << std::endl; 
		for (auto& it2 : it1.second){
			std::cout << it2 << std::endl;
		}		
	}


	std::vector <int> final_class_vect;

	int classe = 7;
	double min_dist = std::numeric_limits<double>::max();
	double  dist = 0;
	int compt = 1;

	for (auto& it1 : vect_coeff){

		std::cout << "frame " << compt << std::endl;
		compt++;

		for (auto& it : data_map){
			dist = get_distance(it1, it.second);
			std::cout << "distance = " << dist << std::endl;
			if( dist < min_dist){
				min_dist =  dist;
				classe = it.first;
			}
		}
		
	
		final_class_vect.push_back(classe); 
		classe = 7;
		min_dist = std::numeric_limits<int>::max();
		dist = 0;

	}

	for (auto& it3 : final_class_vect){
		std::cout << "final class : " << it3 << std::endl; 
	}
}
