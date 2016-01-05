#pragma once

#include <opencv2/opencv.hpp>
#include <algorithm>
#include <vector>
#include <complex>
#include <utility>
#include <iostream>
#include <functional>



// Retourne le point moyen d'une liste de points
std::complex<double> z_moyen (std::vector< std::vector<cv::Point> > contour);

// Détermine les descripteurs de Fourier d'un contour
std::vector<std::complex<double>> descripteur_fourier_normal (std::vector< std::vector<cv::Point> > contour, int c_max);

// Reconstruction d'un contour à partir de ses descripteurs de Fourier
std::vector<std::vector<cv::Point>> reconstruction ( std::vector<std::complex<double>> coeff, int N, int c_max, std::complex<double> z_moy, double scale);
