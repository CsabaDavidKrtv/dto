#include <iostream>
#include "Dependant.h"

int main()
{
	std::cout << "=== dto Template Helper Example ===" << std::endl;
	std::cout << std::endl;

	std::cout << "Creating MyDependant with dependencies injected:" << std::endl;
	Dependants::MyDependant dependant;
	dependant.Function();
	std::cout << std::endl;

	std::cout << "The template helper provides clear, readable syntax:" << std::endl;
	std::cout << "  ::dto::Dependency<dto::Member_t, DefaultType>" << std::endl;

	return 0;
}
