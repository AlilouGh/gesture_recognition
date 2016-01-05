#include "traitement.hpp"


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
