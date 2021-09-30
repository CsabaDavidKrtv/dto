#include<gtest/gtest.h>
#include<gmock/gmock.h>

#include "../../Default/src/Dependant.h"

struct PUT_MockGet : Dependants::MemberDependant
{
	dto::Member1_t::Df_t<Dependencies::B_Dpcy>& Member1_mock()
	{
		return this->member1;
	}
};

TEST(Dependant, MemberDependant)
{
	PUT_MockGet put;
	EXPECT_CALL(put.Member1_mock(), Function);

	put.Function();
}