#pragma once
#include <DependencyTypeOverride.h>

// Forward declaration
namespace Dependants
{
struct MyDependant;
}

// Include Dependencies.h to access the dependency types
#include "../../../Default/src/Dependencies.h"

// Override example for MyDependant - swap member types
template<typename t_OptionTracker, typename t_DefaultDtoDesc>
struct dto::Override<Dependants::MyDependant, t_OptionTracker, t_DefaultDtoDesc> : t_DefaultDtoDesc
{
	// Swap the types - Member0 becomes B_Dpcy, Member1 becomes A_Dpcy
	using Member0_t = ::dto::TypeOverride<Dependencies::B_Dpcy>;
	using Member1_t = ::dto::TypeOverride<Dependencies::A_Dpcy>;
};
