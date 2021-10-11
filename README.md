# *Dependency Type Overriding*

This description gives some practical tips and tricks for using dependency replaceing without calling any virtual function. 
You face this situation, especially in the case of mocking objects for testing. But it can be practical in some other cases, especially when you build a system for more target systems.
This description describes tips and tricks allowing: 
- to replace the dependency without significantly modifying the original code and without using virtual functions in product build or make your dependant classes to template class for this purpose;
- to replace dependencies independently from another dependency replacing. So that, it is enough to define only that dependency replace what you want to change, and you don't have to define the default dependencies again;
- to replace a dependency without using macros and precompiler switches;
- to hide the implementation details of your product from users, if you deliver a third-party product.

You can use this programming method only in the C++ language.


With this method, we override dependencies at compile time by replacing the type of dependencies. It follows the requirement that you build the same code with more dependency sets and more build config. In addition, this method has to be easy to use.

Illustrative graph of the relationship between projects:
<pre><code>workspace/soluion root
	|-CMakeLists.txt
	|-DefaultProject			<- This Project made to contain the implementation details and/or build the product application.
	|	|-dto					<- Definitions for dependency replaceing
	|	|-Dependant.h			<- Source files.
	|	|-Dependant.cpp
	|	|-Dependencies.h
	|	|-Dependencies.cpp
	|	|-Main.cpp
	|	|-CMakeLists.txt/*.vcxproj		
	|-OtherProject				<- Other project with different dependency/configuration set, builds another product application.
	|	|-dto					<- Definitions for dependency replaceing
	|	|-...					<- Project specific sources.
	|	|-CMakeLists.txt/...	<- Import source files from the DefaultProject, add source files which related to this project.
	|-UnitTestProject
	|	|-dto					<- Definitions for dependency replaceing
	|	|-Test0.cpp				<- Some sources for test.
	|	|...					
	|	|-Main.cpp
	|	|-CMakeLists.txt/...	<- Import source files (except main.cpp) from the DefaultProject, add the UnitTestProject source files.
	|-IntegrationTestProject
	|	|-dto					<- Definitions for dependency replaceing
	|	|-Test0.cpp
	|	|...					<- Some sources for test.
	|	|-Main.cpp
	|	|-CMakeLists.txt/...	<- Import source files (except main.cpp) from the DefaultProject, add the IntegrationTestProject source files.
	|-...</code></pre>

The product folders/projects do not contain any test-related definitions (mocks, stubs, etc.).

Now, you can solve the initial problem without the knowledge described further on, if you:
- use only precompile switches, 
- use templates for dependants,
- replace the headers of dependencies (It is the hell of headers),
- use macros (It is the hell of macros),
- define the dependencies outside of class definition, especially in a configuration header file, with precompiler switches.

None of the above methods meets the requirement of being easy to use. Although the last one is close to it, there are other methods easier to use. I pass over these methods because it would be too difficult to describe them here, mainly because I have dropped them out.

In this method, we override dependencies at compile-time, so we change the type of dependencies. In the original code, the dependants should be able to receive the dependency type replacing/overriding from outside of dependant headers and sources, and from outside of the default project workspace too.
For example, we have a program to run on a Linux-like system, and we would like to run this also on an MS-like system. Of course, these are different binary from different build configs.
To override dependency type(s) of the dependant class(es)/struct(s) in the given project, we use the 
- class/struct inheritance features
- C++ template specialization features
- C++ template parameter unevaluation features
- C++ compilers include directories feature

in this method. I'll call this programming method "dto" from the "dependency type override" expression.

## Overriding default definitions
I use the class/struct inheritance features for getting the default dependency type from the base class, and we can override these definitions in the derived class definition. Therefore the base class (defaulter) contains the default definitions, and the derived one (overrider) contains the override definitions.

```c++
struct Default
{
	using Data_t = double;
	using Source_t = double;

	static constexpr Data_t InitData = 0.1f;
};

//Nothing overrided
struct Override_0 : Base
{
};

//Something overrided
struct Override_1 : Base
{
	//Data_t definition isn't overrided.	
	using Source_t = short;

	static constexpr Data_t InitData = 2;
};

int main()
{
	Override_0::Data_t source_0(Override_0::InitData);		// The source_0 is double and initialized with 0.1 
									// as the DEFAULT defintion defines it.
	Override_0::Data_t value_0(source_0 + Override_0::InitData);	// The value_0 is double and initialized with 0.2 
									// as the DEFAULT definition defines it.
	std::cout << value_0;
	
	Override_1::Data_t source_1(Override_1::InitData);		// The source_1 is short as the OVERRIDE define it 
									// and initialized with 2 as the OVERRIDE define it.
	Override_1::Data_t value_1(source_1 + Override_1::InitData);	// The value_1 is double as the DEFAULT define it 
									// and initialized with 4 as the OVERRIDE define it.
	std::cout << value_1;
	
	return 0;
}
```

When "something" is defined in the Override, this definition is used instead of Default's definition. But if you don't redefine "something" in the Override, the Default's definition is to use.

## An new approach to giving definitions for classes
I use template specialization features for selecting which type-definition passing relates to the given class/struct.

```c++
template<<typename t_UnderDefintion>>
struct DefintionTracker
{};

class TargetType_0;
class TargetType_1;

//Pass types, definitions for TargetType_0
template<>
struct DefintionTracker<TargetType_0>
{
	using Data_t = int;
	static constexpt Data_t InitData = 0;
};

//Pass types, definitions for TargetType_1
template<>
struct DefintionTracker<TargetType_1>
{
	using Data_t = double;
	static constexpt Data_t InitData = 1.1f;
};


class TargetType_0
{
	using Def_t = DefintionTracker<TargetType_0>;	//Get definitions for TargetType_0

	Def_t::Data_t data;			//The data is int as the DefintionTracker's specialization for TargetType_0 defines it.

public:
	TargetType_0()
		:data(Def_t::InitData)	//The data is initialized to 0 as the DefintionTracker's specialization for TargetType_0 defines it.
	{}
};

class TargetType_1
{
	using Def_t = DefintionTracker<TargetType_1>;	//Get definitions for TargetType_1

	Def_t::Data_t data;			//The data is double as the DefintionTracker's specialization for TargetType_1 defines it.

public:
	TargetType_1()
		:data(Def_t::InitData)	//The data is initialized to 1.1 as the DefintionTracker's specialization for TargetType_1 defines it.
	{}
};
```

## Using of unknown definitions
I use the C++ template parameter non-evaluating features for passing types that aren't defined/declared where you place the override definitions.
In most cases, you have to pass custom types for classes from outside of class definitions. To do this, you have to declare the custom type before type passing. It is inconvenient, especially if we use many namespaces. Therefore we introduce another template parameter for the DefinitionTracker that contains the options for type passing, which doesn't have to be defined/declared at the type passing point because the template parameter is non-evaluated there.


```c++
template<typename t_UnderDefinition, typename t_Types>
struct DefinitionTracker
{};

class TargetType;
//At this point, you don't have to declare any type for the definition.

template<typename t_Types>
struct DefintionTracker<TargetType, t_Types>
{
	using File_t = t_Types::MsFile_t;		//MsFile_t isn't evaluated here.
};
```

In the LinuxSystemIO header
```c++
namespace LinuxSystem
{
namespace IO
{

class File
{
	bool Open();
};

class ...
...
}
}
```

In the MsSystemIO header:
```c++
namespace MsSystem
{
namespace IO
{

class File
{
	bool Open();
};

class ...
...
}
}
```


In the dependant header
```c++
#include "LinuxSystem.h"
#include "MsSystem.h"

class Dependant
{
public:
	struct DefinitionOptions
	{
		using LinuxFile_t = LinuxSystem::IO::File;
		using MsFile_t = MsSystem::IO::File;
	};

	using Def_t = DefintionTracker<Dependant, DefinitonOptions>;	//Get definitions for Dependant and give the defined options for overridings.

	Def_t::File_t file;		//In this case the file is MsSystem::IO::File;
};
```

## Combination of the first three C++ feature mentioned above
The three features again:
- class/struct inheritance and
- C++ template specialization features
- C++ template parameter unevaluation features

in the DependencyTypeOverride.h
```c++
namespce dto	// Dependency Type Override
{

template<typename t_UnderOverride, typename t_DefaultDtoDesc = t_UnderOverride::dtoDesc>	//The t_DefaultDtoDesc template parameter is used to pass the default definitions and pass the overriding options.
struct Override : t_DefaultDtoDesc
{};

... // Other helper classes/structs will be detailed later.
}
```

In the Overrides.h
```c++
#include <DependencyTypeOverride.h>
namespace DummyNs
{
class TargetDependant;
}

template<typename t_DefaultDtoDesc>
struct dto::Override<DummyNs::TargetDependant> : t_DefaultDtoDesc
{
	using File_t = t_DefaultDtoDesc::FileOptions::Ms_t;
};
```

In the TargetDependant header
```c++
#include <Overrides.h>	//The Overrides.h location is added to the include path, in the next chapter the explanation why.
namespace DummyNs
{

class TargetDependant
{
public:
	struct dtoDesc
	{
		struct FileOptions
		{
			using Linux_t = LinuxSystem::IO::File;
			using Ms_t = MsSystem::IO::File;
		};

		using File_t = FileOptions::Linux_t;		// Give the default type of file.
	};

protected:
	using dto = ::dto::Override<TargetDependant>;

	dto::File_t file;								// In the current case the file is MsSystem::IO::File, because the dto::Override<DummyNs::TargetDependant> overrides the default LinuxSystem::IO::File.
};

}
```

If the TargetDependant specialization for the Override or the definition of File_t in this specialization doesn't exist, the file type is the default one (LinuxSystem::IO::File), in any other cases, it's the type defined in the Override specialization, now it is the MsSystem::IO::File.

## Injection of overriding definition
We use the C++ compilers included directories feature to inject the project-specific overrides for implementation details easily. If you separate the headers from implementations, put another way, if you use header and cpp files for classes (as is usually the case), you have to include the Overrides.h in cpp that uses dto. But we have an Overrides.h in our default project, where there are no overrides, so this header is essentially empty.

We wouldn't like to touch the default project and won't include another implementation related to another project. For example, we have a project which contains only production implementation but doesn't contain test-related codes (mocks, stubs), and this shall remain this way.
So we give a system-include file location for the C++ compiler in the default project (for gcc example: -Idto). This folder contains the Overrides.h file. We include the Overrides.h with angle brackets (<>) delimiters as system header. If we would like to make a test project which contains mocks, we can use another dto folder in the build config. This other dto folder contains the Overrides.h with overrides for dependency replacing.

<pre><code>
workspace root
	|-CMakeLists.txt
	|-DefaultProject			<- This Project made to build application to Linux system.
	|	|-dto
	|	|	|-Overrides.h		<- Contains only: #include<DependencyTypeOverrides.h> so there no overrides.
	|	|-Dependant.h
	|	|-Dependant.cpp
	|	|-Dependencies.h
	|	|-Dependencies.cpp
	|	|-Main.cpp
	|	|-CMakelists.txt		<- Add -Idto input flag for C++ compiler.
	|-MsProject
	|	|-dto
	|	|	|-Overrides.h		<- Overrides the linux specific dependencies to MS dependency
	|	|-CMakelists.txt		<- Import source files from the DefaultProject, and give -Idto input flag for C++ compiler.
	|-UnitTestProject
	|	|-dto
	|	|	|-Overrides.h		<- Overrides dependencies for unit testing.
	|	|-Test0.cpp
	|	|...					<- Some sources for test.
	|	|-Main.cpp
	|	|-CMakelists.txt		<- Import source files (except main.cpp) from the DefaultProject, add the UnitTestProject source files, and add -Idto input flag for C++ compiler.
	|-IntegrationTestProject
	|	|-dto
	|	|	|-Overrides.h		<- Overrides dependencies for integration testing.
	|	|-Test0.cpp
	|	|...					<- Some sources for test.
	|	|-Main.cpp
	|	|-CMakelists.txt		<- Import source files (except main.cpp) from the DefaultProject, add the UnitTestProject source files, and add -Idto input flag for C++ compiler. (similar to UnitTestProject)
	|-...
</code></pre>

Because the .cpp file includes the Overrides.h file with angle brackets (#include <Overrides.h>) and give the local "dto" folder as a system-include folder (-Idto is in the C++ input argument set), the compiler always includes the current project-specific dto/Overrides.h file. So when the compiler compiles e.g. the Dependant.cpp in the DefaultProject, it includes the DefaultProject/dto/Overrides.h file; but when it compiles the same source file in the other MsProject, the Dependant.cpp includes MsProject/dto/Overrides.h.
Due to this solution, you can compile the Default ProjectSources with different configurations without modifying the original DefaultProject code or adding the other project-specific definitions to the DefaultProject, especially definitions and implementations of mocks or stubs for dependencies.

## On demand default definition
It is inconvenient to define the default type of a member or a function parameter inside the dtoDesc innerclass, especially if you use the dto only for testing. Thus I introduced two more classes into the dto for defining the default type of the corresponding member, where I define this member to make it easier to read/understand the code.

Here are these definitions:
DependencyTypeOverride.h
```c++
namespace dto
{
... <- Here is the Override template definition already known.

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
...
```

Use of them:
```c++
struct A_Dpcy
{
	...
};

struct B_Dpcy
{
	...
};

struct Dependant
{
	struct dtoDesc
	{
		//Define type definition sequence without default type.
		using Member0_t = ::dto::TypeDefault;
		using Member1_t = ::dto::TypeDefault;
	};
	using dto = ::dto::Override<Dependant>;

	void Function();

protected:
	//Define default dependencies outside of dtoDesc
	dto::Member0_t::Df_t<A_Dpcy> member0;			//The default type of member0 is A_Dpcy it is defined at the place of member0 definition.
	dto::Member1_t::Df_t<B_Dpcy> member1;			//The default type of member1 is B_Dpcy
};
```

You can override the type of Dependant::member0 and member1:
```c++

template<typename t_DefaultDtoDesc>
struct dto::Override<Dependant, t_DefaultDtoDesc> : public t_DefaultDtoDesc
{
	using Member0_t = TypeOverride<B_Dpcy>;		//The new type of the member0 is B_Dpcy. The default is A_Dpcy.
};
```

This override results that the type of member0 is B_Dpcy, the same as the member1, because the member1 type remains default, which is B_Dpcy.

## An overrider pair
If using only the above methods, you have to define the mocks inside or around of overriding section. It isn't as easy as you might think. When you have a dependency class that is also dependant, you have to resolve the definition ordering problem.
Another option is to define the mocks around the mocked definition. I think a programming method should have as few limitations and constraints as it's possible. So we can avoid defining mocks around the original definition. With the solution given in this chapter, you can easily define your own mocks in your test or test-related projects, and not in the product code.

Let's look at the problem. It's not too difficult to imagine that you have some classes which are dependants and also have dependencies. These classes have some innerclass definitions, which are widely used in the code.
See an example:

Class.h:
```c++
#include <Overrides.h> // for 4th method.
class Class_1
{
public:
	struct Data
	{
		...
	};
	using DataCollection_t = ::std::vector<Data>;

	const DataCollection_t& DataCollection() const { return this->pr_DataCollection; }
	DataCollection_t& DataCollection() { return this->pr_DataCollection; }

	void ProcessToGenerateData();
	
protected:
	DataCollection_t pr_DataCollection;
	...
};

class Class_2
{
public:
	struct dtoDesc
	{
		using Dep_t;
	};
	using dto = ::dto::Override<Class_2>;

	dto::Dep_t::Df_t<Class_1>::DataCollection_t ProcessToGenerateData();

protected:
	dto::Dep_t::Df_t<Class_1> dep;
};
```

Class.cpp:
```c++
#inlude"Class.h"

void Class_1::ProcessToGenerateData()
{
...
}

Class_2::dto::Dep_t::Df_t<Class_1>::DataCollection_t ProcessToGenerateData()
{
	this->dep.ProcessToGenerateData();
	return this->dep.DataCollection();
}
```

When you would like to write a test project for your code above, you can mock dependencies to separate the modules from each other. For the dependency overriding of the Class_1 you have to place the overriding definition before the Class_1 definition. It is provided by the 4th method when you include (inject) the project-specific overriding header into the first place of your headers.

TestProject/dto/Overrides.h:
```c++
#include <DependencyTypeOverride.h>

struct Class_2;

template<typename t_DefinitionTracker, typename t_DefaultDtoDesc>
struct Override<Class_2, t_DefinitionTracker, t_DefaultDtoDesc> : t_DefaultDtoDesc
{
	using Dependency_t = ::dto::TypeOverride<Class_1_mock>;
};
```

I think now you can see the problem. The question is, where the Class_1_mock definition should be? If we would like to define the Class_1_mock, first we need the Class_1::Data definition. So the only choice is to define it after the Class_1 definition. But we must define it before the Class_2 definition. We wouldn't like to separate the Class.h header, which would be overhead only for tests.

We can do it like this:

I added some new helpers into DependencyTypeOverride.h
```c++
...
namespace dto
{
...

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
...
}
```

dto/Overrides.h:
```c++
template<typename t_DefinitionTracker, typename t_DefaultDtoDesc>
struct Override<Class_2, t_DefinitionTracker, t_DefaultDtoDesc> : t_DefaultDtoDesc
{
	using Dependency_t = ::dto::MockOfType;
};

namespace dto
{

template<typename t_Original>
struct Mock <Class_1, t_Original>
{
	MOCK_METHOD(t_Original::DataCollection_t, ProcessToGenerateData, ());
};

}
```

You can define your own helpers like Mock and MockOfType if it is necessary for your projects.
