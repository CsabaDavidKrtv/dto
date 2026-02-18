# Template Helper Usage Guide

This guide shows how to use the `Dependency<>` template helper for dto (Dependency Type Override) library.

## Overview

The dto library uses a template helper to provide clean, readable syntax for dependency injection without virtual functions.

## The Dependency Template Helper

**Usage:**
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
- **Clear and readable**: `::dto::Dependency<dto::Member0_t, DefaultType>`
- **Explicitly shows** this is a dependency
- **No macros** - pure template-based solution
- **Works with all C++ tools and IDEs**

## Complete Example

See the `Examples/3_TemplateHelper` directory for a complete working example that demonstrates:
- Template helper usage
- How to override dependency types in different build configurations

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

Override dependency types for different build configurations:

```cpp
// In your project's dto/TypeOverrides.h
template<typename t_OptionTracker, typename t_DefaultDtoDesc>
struct dto::Override<MyClass, t_OptionTracker, t_DefaultDtoDesc> : t_DefaultDtoDesc
{
    using Member0_t = ::dto::TypeOverride<DifferentDependency>;
};
```

## How It Works

The template helper is a simple type alias:

```cpp
template<typename t_DtoType, typename t_Default>
using Dependency = typename t_DtoType::template Df_t<t_Default>;
```

This provides a clean interface to the underlying type override mechanism.
