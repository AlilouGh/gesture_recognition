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
#include "parser.hpp"


int main(int, char**)
{

	std::map < std::string, std::vector< std::vector<std::complex<double> > > > data_map = parser("database_kmeans.txt");


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

	for (auto& it : vect_frames){
		segmentation(it);
		cv::cvtColor(it, frame_conv, CV_RGB2GRAY);
		cv::findContours(frame_conv, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
		contours = find_longest_contour(contours);
		vect_coeff.push_back(descripteur_fourier_normal(contours, c_max));
	}

	for (auto& it1 : data_map){
		std::cout <<  it1.first << std::endl; 
		for (auto& it2 : it1.second[0]){
			std::cout << it2 << std::endl;
		}		
	}


	std::vector <std::string> final_class_vect;

	std::string classe = "7";
	double min_dist = std::numeric_limits<double>::max();
	double  dist = 0;
	int compt = 1;

	for (auto& it1 : vect_coeff){

		std::cout << "frame " << compt << std::endl;
		compt++;

		for (auto& it : data_map){
			dist = get_distance(it1, it.second[0]);
			std::cout << "distance = " << dist << std::endl;
			if( dist < min_dist){
				min_dist =  dist;
				classe = it.first;
			}
		}
		
	
		final_class_vect.push_back(classe); 
		classe = "7";
		min_dist = std::numeric_limits<int>::max();
		dist = 0;

	}

	for (auto& it3 : final_class_vect){
		std::cout << "final class : " << it3 << std::endl; 
	}
}
