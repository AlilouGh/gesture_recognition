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



std::map< std::string, std::vector< std::vector< std::complex<double> > > > fourier_descriptor_extraction (int c_max);
