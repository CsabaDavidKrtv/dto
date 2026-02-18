#include <iostream>
#include "Dependant.h"

int main()
{
	std::cout << "=== Simplified Syntax Example ===" << std::endl;
	std::cout << std::endl;

	std::cout << "Using SimplifiedDependant (with macros):" << std::endl;
	Dependants::SimplifiedDependant simplified;
	simplified.Function();
	std::cout << std::endl;

	std::cout << "Using TraditionalDependant (old syntax):" << std::endl;
	Dependants::TraditionalDependant traditional;
	traditional.Function();
	std::cout << std::endl;

	std::cout << "Using HelperDependant (with Dependency template):" << std::endl;
	Dependants::HelperDependant helper;
	helper.Function();
	std::cout << std::endl;

	std::cout << "All three approaches work identically!" << std::endl;

	return 0;
}
