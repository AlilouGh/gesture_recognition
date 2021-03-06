#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

#include "feature_extraction.hpp"
#include "descripteur_fourier.hpp"
#include "traitement.hpp"



std::map< std::string, std::vector< std::vector< std::complex<double> > > > fourier_descriptor_extraction (int c_max) {

std::map< std::string, std::vector< std::vector< std::complex<double> > > > database_map;  // initialisation d'un dictionnaire dont les clés sont les noms des classes et les valeurs sont l'ensemble des descripteurs de Fourier associés

 std::string pathname("/usr/users/promo2016/pierrard_reg/TL/Base_de_donnees");              // chemin du répertoire à parcourir
 const boost::filesystem::path search_here (pathname);
 boost::filesystem::recursive_directory_iterator dir( search_here), end;

 std::string classe;                                                                        // string qui indiquera la classe courante
 std::ofstream out("database.txt");

 while (dir != end)                                                                         // on parcoure le répertoire indiqué par la variable pathname
   {

     std::string filename(dir->path().filename().string());                                 // nom du fichier ou répertoire courant

     if (filename.substr(filename.size() - 3, filename.size() - 1) != "jpg")                // si les 3 derniers caractères de filename ne sont pas "jpg", filename indique un nom de répertoire
       classe = filename;
     else if (classe != "Rejet") {                                                          // on ne considère pas la classe rejet pour notre base de données
       cv::Mat frame;
       frame = cv::imread( pathname + "/" + classe + "/" + filename);

       segmentation(frame);
       std::vector<std::vector<cv::Point>> contours;                                          // variable dans laquelle on récupèrera la liste des contours
       cv::Mat frame_conv;                                                                    // variable qui va contenir l'image en nuances de gris
       cv::cvtColor(frame, frame_conv, CV_RGB2GRAY);                                          // conversion de l'image courante en couleur en niveaux de gris
       cv::findContours(frame_conv, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
      
       contours = find_longest_contour(contours);

       //int c_max = 10;
       std::vector<std::complex<double>> coeff = descripteur_fourier_normal(contours, c_max);
       database_map[classe].push_back(coeff);                                                 // on ajoute les descripteurs de Fourier de l'image courante à la base de données
       for (auto& it : coeff) {
	 out << it << " ";
       }
       out << classe << std::endl;
     }

     ++dir;
   }
 out.close();

 return database_map;

}

