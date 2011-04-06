#include "../sample/RandomGen.hpp"
#include <iostream>

int main(int argc, char* argv[]) 
{
	using hstefan::sample::RandomGen;
	srand((unsigned int)time(0));
	RandomGen r;
	r.generateSample(16);
	std::vector<RandomGen::signal_type>& vec = r.getSample();
	for(std::vector<RandomGen::signal_type>::iterator it = vec.begin(); it != vec.end(); ++it) 
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cin.get();
}