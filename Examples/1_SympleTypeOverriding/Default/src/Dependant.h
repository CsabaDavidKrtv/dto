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

		//Define type definition sequence and default type.
		using Parameter0_t = DependencyOptions::OptionA_t;
		using Parameter1_t = DependencyOptions::OptionB_t;
	};
	using dto = ::dto::Override<ParameterDependant>;

	using FunctionParameter0_t = dto::Parameter0_t;
	using FunctionParameter1_t = dto::Parameter1_t;
	void Function(FunctionParameter0_t& i_Param0, FunctionParameter1_t& i_Param1);
};

struct MemberDependant
{
	struct dtoDesc
	{
		struct DependencyOptions
		{
			using OptionA_t = Dependencies::A_Dpcy;
			using OptionB_t = Dependencies::B_Dpcy;
		};

		//Define type definition sequence and default type.
		using Member0_t = DependencyOptions::OptionA_t;
		using Member1_t = DependencyOptions::OptionB_t;
	};
	using dto = ::dto::Override<MemberDependant>;

	void Function();

protected:
	dto::Member0_t member0;
	dto::Member1_t member1;
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

		//Define type definition sequence and default type.
		using Class0_t = DependencyOptions::OptionA_t;
		using Class1_t = DependencyOptions::OptionB_t;
	};
	using dto = ::dto::Override<StaticDependant>;

	static void StaticFunction();

};

}