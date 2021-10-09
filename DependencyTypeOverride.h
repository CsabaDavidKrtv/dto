#pragma once

#include<type_traits>


namespace dto
{

/// <summary>
/// It is used for take overriding options for the given class in the t_TargetType.
/// In the template specialisation can you give override options for the t_TargetType class type.
/// This class used by the Override template class.
/// </summary>
template<typename t_TargetType>
struct OptionTracker
{
};

/// <summary>
/// This template class used for give overrides for the t_UnderOverride class.
/// In the template specialisation can you give overrides for the t_UnderOverride class type.
/// </summary>
template<typename t_UnderOverride, typename t_OptionTracker = OptionTracker<t_UnderOverride>, typename t_DefaultDtoDesc = typename t_UnderOverride::dtoDesc>
struct Override : public t_DefaultDtoDesc
{};

/// <summary>
/// Used for give the default type definition.
/// </summary>
/// <typeparam name="t_TargetType"></typeparam>
struct TypeDefault
{
	template<typename t_Default>
	struct Df
	{
		using type = t_Default;
	};

	template<typename t_Default>
	using Df_t = typename Df<t_Default>::type;
};

/// <summary>
/// Used for override the default type which defined by TypeDefault.
/// </summary>
template<typename t_Override>
struct TypeOverride
{
	template<typename t_Default>
	struct Df
	{
		using type = t_Override;
	};

	template<typename t_Default>
	using Df_t = typename Df<t_Default>::type;
};

/// <summary>
/// Used for give mock definition for the given class in the t_OriginalSpec template parameter, via template specialisation.
/// </summary>
/// <typeparam name="t_OriginalSpec"></typeparam>
/// <typeparam name="t_Original"></typeparam>
template<typename t_OriginalSpec, typename t_Original = t_OriginalSpec>
struct Mock
{};

/// <summary>
/// Used for override the default type by its own mock type which defined with Mock template specialisation.
/// </summary>
/// <typeparam name="t_Default"></typeparam>
struct MockOfType
{
	template<typename t_Default>
	struct Df
	{
		using type = Mock<t_Default>;
	};

	template<typename t_Default>
	using Df_t = typename Df<t_Default>::type;
};

template<class t_VariableType, class... t_AcceptableTypes>
class TypeIsAccepted
{
public:
	template<class t_One, class... t_P0toN>
	struct Is_One_Of;

	template<class t_One>
	struct Is_One_Of<t_One> : ::std::false_type
	{};

	template<class t_One, class... t_P1toN>
	struct Is_One_Of<t_One, t_One, t_P1toN...> : ::std::true_type
	{};

	template<class t_One, class t_P0, class... t_P1toN>
	struct Is_One_Of<t_One, t_P0, t_P1toN...> : Is_One_Of<t_One, t_P1toN...>
	{};

public:
	static constexpr bool value = Is_One_Of<t_VariableType, t_AcceptableTypes...>::value;
};

template<class t_VariableType, class... t_AcceptableTypes>
using TypeIsAccepted_t = typename TypeIsAccepted< t_VariableType, t_AcceptableTypes...>::type;

}

#define ACCEPTED_TYPES_FOR(i_Member, ...)					\
static_assert(::dto::TypeIsAccepted<decltype(i_Member), __VA_ARGS__>::value,"The currently type of \"" #i_Member "\" isn't allowed for this member.")
