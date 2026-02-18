#include "Dependant.h"
#include <iostream>

namespace Dependants
{

void SimplifiedDependant::Function()
{
	std::cout << "SimplifiedDependant::Function() - member0.Data: " << member0.Data 
	          << ", member1.Data: " << member1.Data << std::endl;
}

void TraditionalDependant::Function()
{
	std::cout << "TraditionalDependant::Function() - member0.Data: " << member0.Data 
	          << ", member1.Data: " << member1.Data << std::endl;
}

void HelperDependant::Function()
{
	std::cout << "HelperDependant::Function() - dep.Data: " << dep.Data << std::endl;
}

}
