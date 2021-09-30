#pragma once

#include "Dependant.h"
#include <iostream>
#include <string>

namespace Dependants
{

void ParameterDependant::Function(FunctionParameter0_t& i_Param0, FunctionParameter1_t& i_Param1)
{
	std::cout << "Implementation of Paramter0=" << i_Param0.Function() << "; Parameter1=" << i_Param1.Function() << std::endl;
}

void MemberDependant::Function()
{
	std::cout << "Implementation of Member0=" << this->member0.Function() << "; Member1=" << this->member1.Function() << std::endl;
}

void StaticDependant::StaticFunction()
{
	//Define default dependencies here.
	std::cout << "Implementation of Class0=" << dto::Class0_t::Df_t<Dependencies::A_Dpcy>::StaticFunction() << "; Class1=" << dto::Class1_t::Df_t<Dependencies::B_Dpcy>::StaticFunction() << std::endl;
}

}