#pragma once

#include <DependencyTypeOverride.h>
#include <TypeOverrides.h>
#include "Dependencies.h"

namespace Dependants
{

// Example 1: Using the Dependency template helper (simplified)
struct HelperDependant
{
	struct dtoDesc
	{
		using Member0_t = ::dto::TypeDefault;
		using Member1_t = ::dto::TypeDefault;
	};
	using dto = ::dto::Override<HelperDependant>;

	void Function();

protected:
	// Simplified syntax using Dependency helper template
	::dto::Dependency<dto::Member0_t, Dependencies::A_Dpcy> member0;
	::dto::Dependency<dto::Member1_t, Dependencies::B_Dpcy> member1;
};

// Example 2: Traditional approach (still supported)
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

}
