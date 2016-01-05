#pragma once

#include <opencv2/opencv.hpp>
#include <algorithm>
#include <vector>
#include <complex>
#include <utility>
#include <iostream>
#include <functional>
#include <string>
#include <boost/filesystem.hpp>
#include <typeinfo>
#include "descripteur_fourier.hpp"
#include "traitement.hpp"
#include <map>



std::vector<std::vector<std::complex<double>>> kmeans_input (int c_max);
