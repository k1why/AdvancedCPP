#include <tuple>
#include <iostream>
#include <type_traits>


template <typename tFunction, size_t... tIndex, typename... tArgs>
constexpr auto call_via_tuple_impl(tFunction& function, std::index_sequence<tIndex...>, const std::tuple<tArgs...>& args) {
	return function(std::get<tIndex>(args)...);
}

template <typename tFunction, typename... tArgs>
constexpr auto call_via_tuple(tFunction& function, const std::tuple<tArgs...>& args) {
	return call_via_tuple_impl(function, std::make_index_sequence <sizeof...(tArgs)>(), std::tuple<tArgs...>(args));
}

int main()
{
	auto t = std::make_tuple(3, 5, 78);
	auto func = [](int a, int b, int c) {
		return a + b + c;
	};

	std::cout << call_via_tuple(func, t);
}