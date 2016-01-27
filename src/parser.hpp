#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <complex>
#include <cstring>
#include <stdlib.h>

double strict_str2double(char* str);
std::vector<char> str2char_star (std::string str);
std::map< std::string, std::vector< std::vector< std::complex<double> > > > parser(std::string filename);
