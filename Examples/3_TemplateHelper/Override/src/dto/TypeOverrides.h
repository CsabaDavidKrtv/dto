#pragma once
#include <DependencyTypeOverride.h>

// Forward declarations
namespace Dependants
{
struct HelperDependant;
struct TraditionalDependant;
}

// Need to include Dependencies.h to access the dependency types
// This is included after the forward declarations but before the overrides
#include "../../../Default/src/Dependencies.h"

// Override example for HelperDependant - swap member types
template<typename t_OptionTracker, typename t_DefaultDtoDesc>
struct dto::Override<Dependants::HelperDependant, t_OptionTracker, t_DefaultDtoDesc> : t_DefaultDtoDesc
{
	// Swap the types - Member0 becomes B_Dpcy, Member1 becomes A_Dpcy
	using Member0_t = ::dto::TypeOverride<Dependencies::B_Dpcy>;
	using Member1_t = ::dto::TypeOverride<Dependencies::A_Dpcy>;
};

// Override example for TraditionalDependant - same as HelperDependant
template<typename t_OptionTracker, typename t_DefaultDtoDesc>
struct dto::Override<Dependants::TraditionalDependant, t_OptionTracker, t_DefaultDtoDesc> : t_DefaultDtoDesc
{
	using Member0_t = ::dto::TypeOverride<Dependencies::B_Dpcy>;
	using Member1_t = ::dto::TypeOverride<Dependencies::A_Dpcy>;
};
