#include "../sample/RandomGen.hpp"
#include "../sample/LinearGen.hpp"
#include <iostream>

int main(int argc, char* argv[]) 
{
	srand((unsigned int)time(0));

	using namespace hstefan::sample;
	LinearGen* l = new LinearGen();
	RandomGen* r = new RandomGen();

	std::vector<SampleGenerator*> gen;
	gen.push_back(l);
	gen.push_back(r);

	for(std::vector<SampleGenerator*>::iterator it = gen.begin(); it != gen.end(); ++it)
	{
		(*it)->generateSample(16);
		for(std::vector<SampleGenerator::signal_type>::iterator ij = (*it)->getSample().begin(); ij != (*it)->getSample().end(); ++ij) 
			std::cout << (unsigned int)*ij << " ";
		std::cout << std::endl;
	}

	delete l;
	delete r;

	std::cin.get();
}