#pragma once
#include <DependencyTypeOverride.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>


namespace Dependencies
{
struct B_Dpcy;
}

template<typename t_Original>
struct ::dto::Mock<Dependencies::B_Dpcy, t_Original>
{
	MOCK_METHOD(std::string, Function, ());
};
