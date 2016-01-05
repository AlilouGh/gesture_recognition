#include "traitement.hpp"
#include "descripteur_fourier.hpp"
#include "feature_extraction.hpp"
#include "kmeans.hpp"




/*int main(int, char**)
{
  /*cv::VideoCapture cap(0);                                                                                           // open the default camera

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
      }*/

/* int c_max = 10;

  std::map< std::string, std::vector< std::vector< std::complex<double> > > > database = fourier_descriptor_extraction(c_max);
  
  for (auto& it : database) {
    std::cout << it.first << " : " << std::endl;;
    for (auto& it2 : it.second[0]) {
      std::cout << it2 << ", ";
    }
    std::cout << std::endl;
  }
  
  return 0;
}*/
