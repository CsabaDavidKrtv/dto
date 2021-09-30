#pragma once
#include <DependencyTypeOverride.h>
#include "../Mocks.h"

namespace Dependants
{

struct ParameterDependant;
struct MemberDependant;
struct StaticDependant;

}


template<typename t_OptionTracker, typename t_DefaultDtoDesc>
struct dto::Override<Dependants::MemberDependant, t_OptionTracker, t_DefaultDtoDesc> : t_DefaultDtoDesc
{
	using Member1_t = ::dto::MockOfType;
};


namespace Dependencies
{
struct A_Dpcy;
struct B_Dpcy;
}

template<>
struct ::dto::OptionTracker<Dependants::MemberDependant>
{
	using OptionA_t = Dependencies::A_Dpcy;
	using OptionB_t = Dependencies::B_Dpcy;
};


