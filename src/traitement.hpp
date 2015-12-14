#pragma once

#include <opencv2/opencv.hpp>
#include <algorithm>
#include <vector>
#include <iostream>
#include "descripteur_fourier.hpp"

#define GLOBAL_THRESHOLD 30
#define RED_THRESHOLD    220
#define GREEN_THRESHOLD  160
#define BLUE_THRESHOLD   150


//Segmentation de l'image (on veut extraire la main du fond)
void segmentation(cv::Mat& frame);

//On retourne le contour le plus long de la liste de contours extraite par findContours()
std::vector<std::vector<cv::Point>> find_longest_contour(std::vector<std::vector<cv::Point>>& contours);

