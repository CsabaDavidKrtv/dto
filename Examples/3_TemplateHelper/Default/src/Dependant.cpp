#include "Dependant.h"
#include <iostream>

namespace Dependants
{

void HelperDependant::Function()
{
	std::cout << "HelperDependant::Function() - member0.Data: " << member0.Data 
	          << ", member1.Data: " << member1.Data << std::endl;
}

void TraditionalDependant::Function()
{
	std::cout << "TraditionalDependant::Function() - member0.Data: " << member0.Data 
	          << ", member1.Data: " << member1.Data << std::endl;
}

}
