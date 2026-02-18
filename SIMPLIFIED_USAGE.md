# Simplified Usage Guide

This guide shows how to use the `Dependency<>` template helper to simplify dto (Dependency Type Override) library usage.

## Overview

The dto library has been enhanced with a template helper to reduce verbosity and make the syntax more readable, without introducing macros.

## The Dependency Template Helper

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

**After (With Template Helper):**
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
    ::dto::Dependency<dto::Member0_t, SomeDependency> member0;
    ::dto::Dependency<dto::Member1_t, OtherDependency> member1;
};
```

**Benefits:**
- More readable: `::dto::Dependency<dto::Member0_t, DefaultType>` vs `dto::Member0_t::Df_t<DefaultType>`
- Clearer intent - explicitly shows this is a dependency
- No macros - pure template-based solution
- Works with all C++ tools and IDEs

## Complete Example

See the `Examples/3_TemplateHelper` directory for a complete working example that demonstrates:
- Template helper usage
- Traditional syntax (for comparison)
- How to override dependency types

### Building the Example

```bash
cd Examples/3_TemplateHelper/Default
mkdir build && cd build
cmake ..
make
./3_TemplateHelper_Default    # Run with default dependencies

cd ../../Override
mkdir build && cd build
cmake ..
make
./3_TemplateHelper_Override  # Run with overridden dependencies
```

## Overriding Dependencies

The override syntax remains the same:

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
- Gradually migrate to the template helper
- Use whichever approach you prefer

## When to Use the Template Helper

- **Use template helper**: When you want clearer, more readable syntax
- **Use traditional syntax**: When you need to match existing code style or have other preferences

Both approaches are equivalent and work identically.
