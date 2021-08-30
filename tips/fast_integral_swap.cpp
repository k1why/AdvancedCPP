#include <iostream>
#include <type_traits>


template <class T, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
void integral_swap(T& x, T& y)
{
	x ^= y;
	y ^= x;
	x ^= y;
}

int main()
{
	int a = 255;
	int b = 12512;

	integral_swap(a, b);

	std::cout << "a - " << a << "   b - " << b << std::endl;
}