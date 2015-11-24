#pragma once

#include <opencv2/opencv.hpp>
#include <algorithm>
#include <vector>
#include <complex>
#include <utility>
#include <iostream>
#include <functional>






// Retourne le point moyen d'une liste de points
inline std::complex<double> z_moyen (std::vector< std::vector<cv::Point> > contour) {
  int length = contour[0].size();
  double x_moy, y_moy;
  for (auto& pt : contour[0]) {
    x_moy += pt.x;
    y_moy += pt.y;
  }
  x_moy = x_moy / (length);
  y_moy = y_moy / (length);
  
  std::complex<double> z_moy(x_moy, y_moy);

  return z_moy;
  }



// Détermine les descripteurs de Fourier d'un contour
inline std::vector<std::complex<double>> descripteur_fourier_normal (std::vector< std::vector<cv::Point> > contour, int c_max) {
  int c_min = -c_max;
  int length = contour[0].size();
  double x_moy, y_moy;

  for (auto& pt : contour[0]) {
    x_moy += pt.x;
    y_moy += pt.y;
  }
  x_moy = x_moy / (length);
  y_moy = y_moy / (length);
  
  std::complex<double> z_moy(x_moy, y_moy);

  std::vector<std::complex<double>> serie;
  std::vector<std::complex<double>> spectre;

  for (auto& pt : contour[0]) {
    std::complex<double> z_temp(pt.x, pt.y);
    z_temp = z_temp - z_moy;
    serie.push_back(z_temp);
  }

  cv::dft(serie, spectre,cv::DFT_SCALE + cv::DFT_COMPLEX_OUTPUT);

  std::vector<std::complex<double>> coeff;

  for (int i = 0; i < c_max; ++i) {
    coeff.push_back(spectre[i + spectre.size() - c_max]);
  }

  for (int i = 0; i < c_max + 1; ++i) {
    coeff.push_back(spectre[i]);
  }

  if (std::abs(coeff[c_max - 1]) > std::abs(coeff[c_max + 1])) {
    std::reverse(coeff.begin(), coeff.end());
  }

  double phi = std::arg(coeff[c_max - 1] * coeff[c_max + 1]) / 2.0;

  for (auto& i : coeff) {
    i = i * std::polar ((double) 1.0, -phi);
    }

  double theta = std::arg(coeff[c_max + 1]);
  std::cout << "Theta : " << theta << std::endl;
  
  for (int k = c_min; k <= c_max; ++k) {
    coeff[k+c_max] = coeff[k+c_max] * std::polar((double) 1.0, (double) (-k) * theta); 
    }

  double module = std::abs(coeff[c_max + 1]);

  // Normalisation
  for (auto& value : coeff) {
    value = value / module;
    }

  return coeff;
}



// Reconstruction d'un contour à partir de ses descripteurs de Fourier
inline std::vector<std::vector<cv::Point>> reconstruction ( std::vector<std::complex<double>> coeff, int N, int c_max, std::complex<double> z_moy, double scale) {
  int c_min = -c_max;
  std::vector<std::complex<double>> TC (N, 0);

  int debut = coeff.size() + c_min - 1;

  for (unsigned int i = debut; i < coeff.size(); ++i) {
    TC[i - debut] = (double) N * coeff[i];
  }

  for (int i = 0; i < c_max; ++i) {
    TC[N + c_min + i] = (double) N * coeff[i];
  }

  std::vector<std::complex<double>> z_fil;
  cv::dft(TC, z_fil, cv::DFT_INVERSE + cv::DFT_SCALE);

  z_fil.push_back(z_fil[0]);
  std::vector<cv::Point> z_fill;

  for (auto& i : z_fil) {
    cv::Point pt(scale * i.real() + z_moy.real(), scale * i.imag() + z_moy.imag());
    z_fill.push_back(pt);
  }

  std::vector<std::vector<cv::Point>> contour;
  contour.push_back(z_fill);

  return contour;
}
