#define STRICT
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "wil/com.h"
#include "wil_unique_something_string_ranges_adl.h"

#include <iostream>
#include <ranges>
#include <algorithm>

int main()
{
	auto s1 = wil::make_cotaskmem_string(L"ABC");
	auto s2 = wil::make_cotaskmem_string(L"DEF");

	auto f = std::ranges::equal(s1, s2);
	std::wcout << std::boolalpha << f << std::endl;

	return 0;
}