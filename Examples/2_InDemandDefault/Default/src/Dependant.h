#pragma once

#include <DependencyTypeOverride.h>
#include <TypeOverrides.h>
#include "Dependencies.h"

namespace Dependants
{

struct ParameterDependant
{
	struct dtoDesc
	{
		struct DependencyOptions
		{
			using OptionA_t = Dependencies::A_Dpcy;
			using OptionB_t = Dependencies::B_Dpcy;
		};

		//Define type definition sequence without default type.
		using Parameter0_t = ::dto::TypeDefault;
		using Parameter1_t = ::dto::TypeDefault;
	};
	using dto = ::dto::Override<ParameterDependant>;

	//Define default dependencies
	using FunctionParameter0_t = dto::Parameter0_t::Df_t<Dependencies::A_Dpcy>;
	using FunctionParameter1_t = dto::Parameter1_t::Df_t<Dependencies::B_Dpcy>;

	void Function(FunctionParameter0_t& i_Param0, FunctionParameter1_t& i_Param1);
};

struct MemberDependant
{
	struct dtoDesc
	{
		//Define type definition sequence without default type.
		using Member0_t = ::dto::TypeDefault;
		using Member1_t = ::dto::TypeDefault;
	};
	using dto = ::dto::Override<MemberDependant>;

	void Function();

protected:
	//Define default dependencies
	dto::Member0_t::Df_t<Dependencies::A_Dpcy> member0;
	dto::Member1_t::Df_t<Dependencies::B_Dpcy> member1;
};

struct StaticDependant
{
	struct dtoDesc
	{
		struct DependencyOptions
		{
			using OptionA_t = Dependencies::A_Dpcy;
			using OptionB_t = Dependencies::B_Dpcy;
		};

		//Define type definition sequence without default type.
		using Class0_t = ::dto::TypeDefault;
		using Class1_t = ::dto::TypeDefault;
	};
	using dto = ::dto::Override<StaticDependant>;

	static void StaticFunction();
};

}