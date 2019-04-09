
#include <iostream>
#include "List.h"


int main()
{
	try
	{
		List<long long int> smtg;

		std::cout << smtg.empty() << std::endl;
		smtg.insert(5, 1);
		smtg.print();
		smtg.insert(32, 2);
		smtg.insert(9, 2);
		smtg.insert(6, 2);
		smtg.print();
		std::cout << smtg.size() << std::endl << smtg.empty();
		smtg.clear();
		smtg.print();
		std::cout << smtg.size() << std::endl << smtg.empty();

	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
