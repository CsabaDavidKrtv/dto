#pragma once

#include <string>

namespace Dependencies
{

struct A_Dpcy
{
	std::string Function();
	static std::string StaticFunction();
};

struct B_Dpcy
{
	std::string Function();
	static std::string StaticFunction();
};

}