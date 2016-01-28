#include <algorithm>
#include <vector>
#include <complex>
#include <utility>
#include <iostream>
#include <functional>

/*
int main (int, char**)
{

	std::vector<std::complex<double>> v;
	for(int i=0; i<5; i++){
		v.push_back(std::complex<double>(i*10, i));
	}


	std::vector<std::complex<double>> vv;
	for(int i=0; i<5; i++){
		vv.push_back(std::complex<double>(i*10, i));
	}

	std::transform(v.begin(), v.end(), v.begin(), vv.begin(), std::plus<std::complex<double>>());
	

	for (int i=0; i<5; i++){
		std::cout << v[i] << ' '<< std::endl;
	}

	for (int i=0; i<5; i++){
		std::cout << vv[i] << ' '<< std::endl;
	}


	std::vector<std::complex<double>> divider (v.size(), std::complex<double>(5));

	std::transform(v.begin(), v.end(),divider.begin(), v.begin(), std::divides<std::complex<double>>());
	std::transform(v.begin(), v.end(),divider.begin(), vv.begin(), std::divides<std::complex<double>>());


	for (int i=0; i<5; i++){
		std::cout << v[i] << ' '<< std::endl;
	}


	for (int i=0; i<5; i++){
		std::cout << vv[i] << ' '<< std::endl;
	}

}
*/
