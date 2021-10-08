# *Dependency Type Overriding*

This description gives some practical tips and tricks for using dependency injection without calling any virtual function. 
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



