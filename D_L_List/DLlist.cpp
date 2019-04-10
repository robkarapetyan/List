#include "List.h"
#include <iostream>

int main() {

	try
	{
		DLList<int> ctc;

		ctc.insert(4, 1);
		ctc.insert(5, 1);
		ctc.insert(8, 3);

		ctc.print();
		DLList<int>::Iterator it = ctc.end();
		--it;	
		std::cout << *it << std::endl << "-------" << std::endl;
		it = it + 1;           
		std::cout << *it << std::endl << "-------" << std::endl;
		
		std::cout << ctc.getValue(1);

		/*
		ctc.push_back(6);
		ctc.push_front(10);
		ctc.pop_back();
		ctc.pop_front();
		ctc.print();*/
	}

	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}