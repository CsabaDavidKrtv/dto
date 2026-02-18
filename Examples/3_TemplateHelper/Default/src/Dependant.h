#pragma once

#include <DependencyTypeOverride.h>
#include <TypeOverrides.h>
#include "Dependencies.h"

namespace Dependants
{

// Using the Dependency template helper
struct MyDependant
{
	struct dtoDesc
	{
		using Member0_t = ::dto::TypeDefault;
		using Member1_t = ::dto::TypeDefault;
	};
	using dto = ::dto::Override<MyDependant>;

	void Function();

protected:
	::dto::Dependency<dto::Member0_t, Dependencies::A_Dpcy> member0;
	::dto::Dependency<dto::Member1_t, Dependencies::B_Dpcy> member1;
};

}
