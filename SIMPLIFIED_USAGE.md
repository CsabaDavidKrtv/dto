# Simplified Usage Guide

This guide shows simplified approaches to using the dto (Dependency Type Override) library.

## Overview

The dto library has been enhanced with helper macros and templates to reduce boilerplate code and make the syntax more concise and readable.

## Simplified Approaches

### 1. Using Helper Macros (Recommended)

**Before (Traditional):**
```cpp
struct MyClass
{
    struct dtoDesc
    {
        using Member0_t = ::dto::TypeDefault;
        using Member1_t = ::dto::TypeDefault;
    };
    using dto = ::dto::Override<MyClass>;

protected:
    dto::Member0_t::Df_t<SomeDependency> member0;
    dto::Member1_t::Df_t<OtherDependency> member1;
};
```

**After (Simplified with Macros):**
```cpp
struct MyClass
{
    DTO_DESC_BEGIN()
        DTO_TYPE(Member0);
        DTO_TYPE(Member1);
    DTO_DESC_END(MyClass);

protected:
    DTO_DEP(dto::Member0_t, SomeDependency) member0;
    DTO_DEP(dto::Member1_t, OtherDependency) member1;
};
```

**Benefits:**
- Less verbose: `DTO_DEP(dto::Member0_t, DefaultType)` vs `dto::Member0_t::Df_t<DefaultType>`
- Clearer intent with descriptive macro names
- Automatic dto alias generation with `DTO_DESC_END(ClassName)`
- Reduced chance of syntax errors

### 2. Using the Dependency Helper Template

**Alternative simplified syntax:**
```cpp
struct MyClass
{
    DTO_DESC_BEGIN()
        DTO_TYPE(Dep);
    DTO_DESC_END(MyClass);

protected:
    ::dto::Dependency<dto::Dep_t, SomeDependency> dep;
};
```

This uses the `::dto::Dependency<DtoType, DefaultType>` template helper which is equivalent to `DtoType::Df_t<DefaultType>` but more readable.

## Available Macros

### `DTO_DESC_BEGIN()`
Starts a dtoDesc definition. Use at the beginning of your dependency description block.

### `DTO_DESC_END(ClassName)`
Ends the dtoDesc definition and automatically creates the `using dto = ::dto::Override<ClassName>` alias.
Requires the class name to be passed as an argument.

### `DTO_TYPE(MemberName)`
Defines a type member in dtoDesc using TypeDefault. Equivalent to:
```cpp
using MemberName_t = ::dto::TypeDefault;
```

### `DTO_DEP(DtoType, DefaultType)`
Creates a dependency member with the specified default type. Equivalent to:
```cpp
typename DtoType::template Df_t<DefaultType>
```

### `DTO_ENABLE(ClassName)`
Creates the dto type alias. Usually called automatically by `DTO_DESC_END()`, but can be used standalone if you need custom dtoDesc structure.

## Complete Example

See the `Examples/3_SimplifiedSyntax` directory for a complete working example that demonstrates:
- Simplified syntax with macros
- Traditional syntax (for comparison)
- Helper template usage
- How to override dependency types

### Building the Example

```bash
cd Examples
mkdir build && cd build
cmake ..
make
./3_SimplifiedSyntax/Default/3_SimplifiedSyntax_Default    # Run with default dependencies
./3_SimplifiedSyntax/Override/3_SimplifiedSyntax_Override  # Run with overridden dependencies
```

## Overriding Dependencies

The override syntax remains the same regardless of which approach you use:

```cpp
// In your project's dto/TypeOverrides.h
template<typename t_OptionTracker, typename t_DefaultDtoDesc>
struct dto::Override<MyClass, t_OptionTracker, t_DefaultDtoDesc> : t_DefaultDtoDesc
{
    using Member0_t = ::dto::TypeOverride<DifferentDependency>;
};
```

## Backward Compatibility

All traditional syntax remains fully supported. You can:
- Mix old and new syntax in the same codebase
- Gradually migrate to the simplified syntax
- Choose the approach that best fits your use case

## When to Use Which Approach

- **Use macros**: When you want the most concise syntax and standard patterns
- **Use Dependency template**: When you prefer explicit template syntax over macros
- **Use traditional syntax**: When you need maximum control or have complex custom scenarios
