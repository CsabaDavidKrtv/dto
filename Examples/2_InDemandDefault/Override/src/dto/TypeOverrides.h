#pragma once
#include <DependencyTypeOverride.h>

namespace Dependants
{

struct ParameterDependant;
struct MemberDependant;
struct StaticDependant;

}


template<typename t_OptionTracker, typename t_DefaultDtoDesc>
struct dto::Override<Dependants::ParameterDependant, t_OptionTracker, t_DefaultDtoDesc> : t_DefaultDtoDesc
{
	using Parameter1_t = ::dto::TypeOverride<typename t_DefaultDtoDesc::DependencyOptions::OptionA_t>;
};

template<typename t_OptionTracker, typename t_DefaultDtoDesc>
struct dto::Override<Dependants::MemberDependant, t_OptionTracker, t_DefaultDtoDesc> : t_DefaultDtoDesc
{
	using Member1_t = ::dto::TypeOverride<typename t_OptionTracker::OptionA_t>;
};

template<typename t_OptionTracker, typename t_DefaultDtoDesc>
struct dto::Override<Dependants::StaticDependant, t_OptionTracker, t_DefaultDtoDesc> : t_DefaultDtoDesc
{
	using Class1_t = ::dto::TypeOverride<typename t_DefaultDtoDesc::DependencyOptions::OptionA_t>;
};

//#include "../../2_InDemandDefaultType/Dependencies.h"

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
