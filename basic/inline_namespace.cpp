#include <iostream>

namespace my_library
{
	inline namespace version_2
	{
		void some_func()
		{
			std::cout << "my_library::version 2" << std::endl;
		}
	}

	namespace version_1
	{
		void some_func()
		{
			std::cout << "my_library::version 1" << std::endl;
		}
	}
}

int main()
{
	my_library::version_1::some_func(); // out - version 1
	my_library::version_2::some_func(); // out - version 2

	my_library::some_func(); // out - version 2
}