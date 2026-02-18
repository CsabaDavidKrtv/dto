#include "Dependant.h"
#include <iostream>

namespace Dependants
{

void MyDependant::Function()
{
	std::cout << "MyDependant::Function() - member0.Data: " << member0.Data 
	          << ", member1.Data: " << member1.Data << std::endl;
}

}
