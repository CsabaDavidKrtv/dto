#pragma once

#include <DependencyTypeOverride.h>

namespace Dependants
{

struct ParameterDependant;
struct MemberDependant;
struct StaticDependant;

}


template<typename t_OptionTarcker, typename t_DefaultDtoDesc>
struct dto::Override<Dependants::ParameterDependant, t_OptionTarcker, t_DefaultDtoDesc> : t_DefaultDtoDesc
{
	using Parameter1_t = typename t_DefaultDtoDesc::DependencyOptions::OptionA_t;
};

template<typename t_OptionTarcker, typename t_DefaultDtoDesc>
struct dto::Override<Dependants::MemberDependant, t_OptionTarcker, t_DefaultDtoDesc> : t_DefaultDtoDesc
{
	using Member1_t = typename t_DefaultDtoDesc::DependencyOptions::OptionA_t;
};

template<typename t_OptionTarcker, typename t_DefaultDtoDesc>
struct dto::Override<Dependants::StaticDependant, t_OptionTarcker, t_DefaultDtoDesc> : t_DefaultDtoDesc
{
	using Class1_t = typename t_DefaultDtoDesc::DependencyOptions::OptionA_t;
};
