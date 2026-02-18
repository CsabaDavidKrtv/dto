#pragma once

#include <DependencyTypeOverride.h>
#include <TypeOverrides.h>
#include "Dependencies.h"

namespace Dependants
{

// Example 1: Using new simplified macros
struct SimplifiedDependant
{
	// Use macros to reduce boilerplate
	DTO_DESC_BEGIN()
		DTO_TYPE(Member0);
		DTO_TYPE(Member1);
	DTO_DESC_END(SimplifiedDependant);

	void Function();

protected:
	// Simplified syntax using DTO_DEP macro
	DTO_DEP(dto::Member0_t, Dependencies::A_Dpcy) member0;
	DTO_DEP(dto::Member1_t, Dependencies::B_Dpcy) member1;
};

// Example 2: Traditional approach for comparison (still supported)
struct TraditionalDependant
{
	struct dtoDesc
	{
		using Member0_t = ::dto::TypeDefault;
		using Member1_t = ::dto::TypeDefault;
	};
	using dto = ::dto::Override<TraditionalDependant>;

	void Function();

protected:
	dto::Member0_t::Df_t<Dependencies::A_Dpcy> member0;
	dto::Member1_t::Df_t<Dependencies::B_Dpcy> member1;
};

// Example 3: Using Dependency helper template
struct HelperDependant
{
	DTO_DESC_BEGIN()
		DTO_TYPE(Dep);
	DTO_DESC_END(HelperDependant);

	void Function();

protected:
	// Alternative syntax using Dependency helper
	::dto::Dependency<dto::Dep_t, Dependencies::A_Dpcy> dep;
};

}
