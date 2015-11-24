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
void segmentation(cv::Mat& frame)
{
  for (int i = 0; i < frame.rows; ++i) {
    for (int j = 0; j < frame.cols; ++j) {
      int b = frame.at<cv::Vec3b>(i,j)[0];
      int g = frame.at<cv::Vec3b>(i,j)[1];
      int r = frame.at<cv::Vec3b>(i,j)[2];
      int max_frame = std::max({r, g, b});
      int min_frame = std::min({r, g, b});
      
      if (!(((max_frame - min_frame) >= GLOBAL_THRESHOLD) && (r <= RED_THRESHOLD) && (g <= GREEN_THRESHOLD) && (b <= BLUE_THRESHOLD))) {
	frame.at<cv::Vec3b>(i,j)[0] = 0;
	frame.at<cv::Vec3b>(i,j)[1] = 0;
	frame.at<cv::Vec3b>(i,j)[2] = 0;
      }
    }
  }
}




//On retourne le contour le plus long de la liste de contours extraite par findContours()
std::vector<std::vector<cv::Point>> find_longest_contour(std::vector<std::vector<cv::Point>>& contours) {
  unsigned int size_contour = 0;
  int indice_contour = -1;
  for (unsigned int i = 0; i < contours.size(); ++i) {
    if (contours[i].size() > size_contour) {
      size_contour = contours[i].size();
      indice_contour = i;
    }
  }
  std::vector<std::vector<cv::Point>> contours_2;
  contours_2.push_back(contours[indice_contour]);
  return contours_2;
}










int main(int, char**)
{
  cv::VideoCapture cap(0);                                                                                           // open the default camera

  if(!cap.isOpened()){                                                                                               // check if we succeeded
    std::cout << "Cannot open the camera ! " << std::endl;
    return -1;
  }

 
  cv::Mat frame;                                                                                                     // Matrice dans laquelle on va récupérer l'image
  
  while(true)
    {
      cap >> frame;
      segmentation(frame);
      //cv::imwrite("/usr/users/promo2016/pierrard_reg/TL/test.png", frame);


      std::vector<std::vector<cv::Point>> contours;                                                                  // variable dans laquelle on récupèrera la liste des contours
      cv::Mat frame_conv;                                                                                            // variable qui va contenir l'image en nuances de gris
      cv::cvtColor(frame, frame_conv, CV_RGB2GRAY);                                                                  // conversion de l'image courante en couleur en niveaux de gris
      cv::findContours(frame_conv, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
      
      contours = find_longest_contour(contours);

      cv::Scalar color( rand()&255, rand()&255, rand()&255 );                                                        // définition d'une couleur tirée aléatoirement
      cv::Mat dst = cv::Mat::zeros(frame.rows, frame.cols, CV_8UC3);                                                 // Matrice qui va afficher le contour le plus long
      cv::drawContours(dst, contours, -1, color);

      std::vector<std::complex<double>> coeff = descripteur_fourier_normal(contours, 10);

      double scale = 0.25 * std::min(frame.cols, frame.rows);                                                        // coefficient multiplicateur permettant d'obtenir des valeurs plus espacées des coordonnées des points

      std::vector<std::vector<cv::Point>> contfil = reconstruction(coeff, 200, 10, z_moyen(contours), scale);        // on récupère les points du contour reconstruit

      cv::Mat dst2 = cv::Mat::zeros(frame.rows, frame.cols, CV_8UC3);                                                // Matrice dans laquelle on affichera le contour reconstruit
      cv::drawContours(dst2, contfil, -1, color);

      cv::namedWindow("images",CV_WINDOW_AUTOSIZE);
      cv::imshow("images", frame);
      cv::namedWindow("contours",CV_WINDOW_AUTOSIZE);
      cv::imshow("contours", dst);
      cv::namedWindow("reconstruction",CV_WINDOW_AUTOSIZE);
      cv::imshow("reconstruction", dst2);

      if(cv::waitKey(30) >= 0) break;
    }
  
  return 0;
}
