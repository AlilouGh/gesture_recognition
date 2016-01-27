#include "parser.hpp"


double strict_str2double(char* str) {
  char* endptr;
  double value = strtod(str, &endptr);
  if (*endptr) return 0;
  return value;
}

std::vector<char> str2char_star (std::string str) {
  std::vector<char> writable(str.begin(), str.end());
  writable.push_back('\0');
  return writable;
  // get the char* using &writable[0] or &*writable.begin()
}

std::map< std::string, std::vector< std::vector< std::complex<double> > > > parser(std::string filename) {
  std::map< std::string, std::vector< std::vector< std::complex<double> > > > database;

  std::ifstream in(filename.c_str());

  std::string line, token, classe, st;
  std::vector< std::complex<double> > vec;

  while(std::getline(in,line)) {
    vec.clear();
    std::istringstream iss(line);
    while(std::getline(iss,token,' ')) {
      if (token[0] != '(') {
	classe = token;
      }
      else {
	st = token.substr(1, token.size()-2);

	std::istringstream comp(st);
	std::string c1, c2;

	std::getline(comp,c1,',');
	std::getline(comp,c2);

	std::complex<double> coef(strict_str2double(&str2char_star(c1)[0]), strict_str2double(&str2char_star(c2)[0]));
	vec.push_back(coef);
      }
    }
    database[classe].push_back(vec);
  }
  return database;
}


int main() {
  parser("database.txt");
  return 0;
}
