#include "List.h"
#include <iostream>

int main() {

	try
	{
		List<int> ctc;

		ctc.insert(4, 1);
		ctc.insert(5, 1);
		

		ctc.print();
		/*List<int>::Iterator it = ctc.end();
		--it;	
		std::cout << *it << std::endl << std::endl;
		it = it + 1;           
		std::cout << *it << std::endl << std::endl;
		ctc.push_back(6);
		ctc.push_front(10);
		ctc.pop_back();
		ctc.pop_front();
		ctc.print();
		/*List<int>::Iterator itd = ctc.end();
		std::cout << *itd;*/

	}

	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}