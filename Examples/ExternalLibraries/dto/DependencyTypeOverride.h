#pragma once

#include<type_traits>


namespace dto
{

template<typename t_TargetType>
struct OptionTracker
{
};

template<typename t_UnderOverride, typename t_OptionTracker = OptionTracker<t_UnderOverride>, typename t_DefaultDtoDesc = typename t_UnderOverride::dtoDesc>
struct Override : public t_DefaultDtoDesc
{};

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

template<typename t_OriginalSpec, typename t_Original = t_OriginalSpec>
struct Mock
{};

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
