#include <iostream>
#include "Dependant.h"

int main()
{
    Dependants::ParameterDependant parameterDependant;
    auto parameter0 = Dependants::ParameterDependant::FunctionParameter0_t();
    auto parameter1 = Dependants::ParameterDependant::FunctionParameter1_t();
    parameterDependant.Function(parameter0, parameter1);

    Dependants::MemberDependant memberDependant;
    memberDependant.Function();

    Dependants::StaticDependant::StaticFunction();
}