#include "../sample/RandomGen.hpp"
#include "../sample/LinearGen.hpp"
#include <iostream>

#include "../dct/DCT.hpp"
#include "../gui/Interface.hpp"

int main(int argc, char* argv[]) 
{
	/*srand((unsigned int)time(0));

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
	*/
	//std::vector<unsigned char> vs;
	//vs.push_back(8);
	//vs.push_back(16);
	//vs.push_back(24);
	//vs.push_back(32);
	//vs.push_back(40);
	//vs.push_back(48);
	//vs.push_back(56);
	//vs.push_back(64);
	//
	//using namespace hstefan::dct;

	//std::vector<double> t;
	//t = DiscreteCosineTransform::fdct(vs);

	//for(std::vector<double>::iterator it = t.begin(); it != t.end(); ++it)
	//	std::cout << *it << " ";
	//
	//std::cout << std::endl;

	//std::vector<unsigned char> ret = DiscreteCosineTransform::idct(t);
	//for(std::vector<unsigned char>::iterator it = ret.begin(); it != ret.end(); ++it)
	//	std::cout << (unsigned int)*it << " ";

	//std::cout << std::endl;

	///*delete l;
	//delete r;*/

	//std::cin.get();

	using namespace hstefan::gui;
	Interface inter = Interface();

}