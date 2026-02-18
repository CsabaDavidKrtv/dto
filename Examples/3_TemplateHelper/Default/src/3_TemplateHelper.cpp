#include <iostream>
#include "Dependant.h"

int main()
{
	std::cout << "=== Template Helper Example ===" << std::endl;
	std::cout << std::endl;

	std::cout << "Using HelperDependant (with Dependency template helper):" << std::endl;
	Dependants::HelperDependant helper;
	helper.Function();
	std::cout << std::endl;

	std::cout << "Using TraditionalDependant (traditional syntax):" << std::endl;
	Dependants::TraditionalDependant traditional;
	traditional.Function();
	std::cout << std::endl;

	std::cout << "Both approaches work identically!" << std::endl;
	std::cout << "The template helper provides a more readable syntax:" << std::endl;
	std::cout << "  ::dto::Dependency<dto::Member_t, DefaultType>" << std::endl;
	std::cout << "instead of:" << std::endl;
	std::cout << "  dto::Member_t::Df_t<DefaultType>" << std::endl;

	return 0;
}
